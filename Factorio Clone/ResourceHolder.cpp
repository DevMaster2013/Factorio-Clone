#include "stdafx.h"
#include "ResourceHolder.h"

template class ResourceHolder<sf::Texture>;
template class ResourceHolder<sf::Font>;

template<typename T>
ResourceHolder<T>::ResourceHolder(const std::string & configFile)
{
	loadConfigFile(configFile);
}

template<typename T>
ResourceHolder<T>::~ResourceHolder()
{
}

template<typename T>
void ResourceHolder<T>::loadAll()
{
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
void ResourceHolder<T>::loadConfigFile(const std::string & configFile)
{
	std::string configFilePath = configFile.substr(0, configFile.find_last_of("/") + 1);
	std::ifstream config(configFile);
	while (!config.eof())
	{
		std::string line, key, value;
		
		std::getline(config, line);
		if (line.empty()) continue;

		parseConfigLine(line, key, value);
		_resourcesPathesMap[key] = configFilePath + value;
	}
}
