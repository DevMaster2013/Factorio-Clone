#include "stdafx.h"
#include "ResourceDictionary.h"

ResourceDictionary::ResourceDictionary()
{
}

ResourceDictionary::~ResourceDictionary()
{
}

void ResourceDictionary::initialize()
{
	// Load the resources
	std::vector<ResourceID> resources;
	std::ifstream inFile("media/ResourcesDictionary.dat", std::ios_base::binary);
	size_t resourcesCount = 0;
	inFile.read((char*)&resourcesCount, sizeof(resourcesCount));
	resources.resize(resourcesCount);
	inFile.read((char*)resources.data(), sizeof(ResourceID) * resourcesCount);
	inFile.close();

	// Parse the resources
	for (size_t i = 0; i < resources.size(); i++)
	{
		if (_resources.find(resources[i].priority) == _resources.end())
			_resources[resources[i].priority] = ResourceTypeCollection();
		if (_resources[resources[i].priority].find(resources[i].type) == _resources[resources[i].priority].end())
			_resources[resources[i].priority][resources[i].type] = ResourcesMap();
		_resources[resources[i].priority][resources[i].type][resources[i].resID] = resources[i];
	}
}

ResourceID ResourceDictionary::getResource(ResourceType type, const std::string & name)
{	
	for each (auto& resType in _resources)
	{
		auto resources = getResourcesByPriority(resType.first);
		if (resources[type].find(name) != resources[type].end())
			return resources[type][name];
	}

	return ResourceID({ ResourcePriority::INVALID });
}

ResourceID& ResourceDictionary::getResource(ResourcePriority priority, ResourceType type, const std::string & name)
{
	return _resources[priority][type][name];
}

ResourceDictionary::ResourcePriorityCollection & ResourceDictionary::getResources()
{
	return _resources;
}

ResourceDictionary::ResourceTypeCollection & ResourceDictionary::getResourcesByPriority(ResourcePriority priority)
{
	return _resources[priority];
}

ResourceDictionary::ResourcesMap & ResourceDictionary::getResourcesByType(ResourcePriority priority, ResourceType type)
{
	return _resources[priority][type];
}
