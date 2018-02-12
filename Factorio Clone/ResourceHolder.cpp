#include "stdafx.h"
#include "ResourceHolder.h"

template class ResourceHolder<sf::Texture>;
template class ResourceHolder<sf::Font>;

template<typename T>
ResourceHolder<T>::ResourceHolder()
{
}

template<typename T>
ResourceHolder<T>::~ResourceHolder()
{
	for each (auto& res in _resourcesMap)	
		if (res.second != nullptr)
			delete res.second;	
	_resourcesMap.clear();
}

template<typename T>
T * ResourceHolder<T>::get(const std::string & resName, const std::string& resPath)
{
	if (_resourcesMap.find(resName) == _resourcesMap.end())
	{
		_resourcesMap[resName] = new T();
		if (!_resourcesMap[resName]->loadFromFile(resPath))
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
