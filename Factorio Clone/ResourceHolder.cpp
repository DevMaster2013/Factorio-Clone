#include "stdafx.h"
#include "ResourceHolder.h"

template class ResourceHolder<sf::Texture>;
template class ResourceHolder<sf::Font>;

template<typename T>
ResourceHolder<T>::ResourceHolder(const std::string & resourcePath)
{
	_maxValue = 0;
	_oldSize = 0;
	loadConfigFile(resourcePath);
}

template<typename T>
ResourceHolder<T>::~ResourceHolder()
{
}

template<typename T>
void ResourceHolder<T>::loadAll()
{
	size_t count = 0;
	for each (auto& res in _resourcesPathesMap)
	{
		count++;
		get(res.first);
		_callbackFunction(_progressText, count + _oldSize, _maxValue);
	}
}

template<typename T>
void ResourceHolder<T>::releaseAll()
{
	for each (auto& res in _resourcesMap)	
		if (res.second != nullptr)
			delete res.second;
	_resourcesMap.clear();
	_resourcesPathesMap.clear();
}

template<typename T>
size_t ResourceHolder<T>::getResourcesCount()
{
	return _resourcesPathesMap.size();
}

template<typename T>
void ResourceHolder<T>::setProgressCallback(std::function<void(const std::string&, size_t, size_t)> callback, const std::string& progressText, size_t oldSize, size_t maxValue)
{
	_progressText = progressText;
	_oldSize = oldSize;
	_maxValue = maxValue;
	_callbackFunction = callback;
}

template<typename T>
T * ResourceHolder<T>::get(const std::string & resName)
{
	if (_resourcesMap.find(resName) == _resourcesMap.end())
	{
		_resourcesMap[resName] = new T();
		if (!_resourcesMap[resName]->loadFromFile(_resourcesPathesMap[resName]))
			return nullptr;
	}
	return _resourcesMap[resName];
}

template<typename T>
void ResourceHolder<T>::remove(const std::string & resName)
{
	if (_resourcesMap.find(resName) == _resourcesMap.end()) return;

	T* resource = _resourcesMap[resName];
	if (resource != nullptr)
		delete resource;
	_resourcesMap.erase(resName);
}

template<typename T>
void ResourceHolder<T>::parseConfigLine(const std::string & line, std::string & key, std::string & value)
{
	auto found_equal = line.find("=");
	key = line.substr(0, found_equal);
	value = line.substr(found_equal + 1);
}

template<typename T>
void ResourceHolder<T>::loadConfigFile(const std::string & resourcePath)
{	
	for (auto & p : std::experimental::filesystem::directory_iterator(resourcePath))
	{
		if (std::experimental::filesystem::is_directory(p.path()))
			loadConfigFile(p.path().string());
		else
		{
			std::string key = p.path().filename().string();
			const std::string& value = resourcePath + "\\" + key;
			key = key.substr(0, key.find("."));			
			_resourcesPathesMap[key] = value;
		}
	}
}
