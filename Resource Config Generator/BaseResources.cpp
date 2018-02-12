#include "BaseResources.h"

void addBaseTextures(std::vector<ResourceID>& resources)
{
	ResourcePriority priority = ResourcePriority::BASE;
	ResourceType type = ResourceType::TEXTURE;
}

void addBaseFonts(std::vector<ResourceID>& resources)
{
	ResourcePriority priority = ResourcePriority::BASE;
	ResourceType type = ResourceType::FONT;
}

void addBaseResources(std::vector<ResourceID>& resources)
{
	addBaseTextures(resources);
	addBaseFonts(resources);
}
