#pragma once

#include "ResourceID.h"

class ResourceDictionary
{
public:
	using ResourcesMap = std::unordered_map<std::string, ResourceID>;
	using ResourceTypeCollection = std::unordered_map<ResourceType, ResourcesMap>;
	using ResourcePriorityCollection = std::unordered_map<ResourcePriority, ResourceTypeCollection>;

private:
	ResourcePriorityCollection _resources;

public:
	ResourceDictionary();
	~ResourceDictionary();

public:
	void initialize();

public:
	ResourceID getResource(ResourceType type, const std::string& name);
	ResourceID& getResource(ResourcePriority priority, ResourceType type, const std::string& name);

public:
	ResourcePriorityCollection& getResources();
	ResourceTypeCollection& getResourcesByPriority(ResourcePriority priority);
	ResourcesMap& getResourcesByType(ResourcePriority priority, ResourceType type);
};