#include "CoreResources.h"

void addCoreTextures(std::vector<ResourceID>& resources)
{
	ResourcePriority priority = ResourcePriority::CORE;
	ResourceType type = ResourceType::TEXTURE;

	resources.push_back({ priority, type, "background-image", "media/graphics/core/images/background-image.jpg" });
}

void addCoreFonts(std::vector<ResourceID>& resources)
{
	ResourcePriority priority = ResourcePriority::CORE;
	ResourceType type = ResourceType::FONT;

	resources.push_back({ priority, type, "DejaVuSans", "media/fonts/core/DejaVuSans.ttf" });
	resources.push_back({ priority, type, "DejaVuSans-Bold", "media/fonts/core/DejaVuSans-Bold.ttf" });
	resources.push_back({ priority, type, "DejaVuSansMono", "media/fonts/core/DejaVuSansMono.ttf" });
	resources.push_back({ priority, type, "Lato-Bold", "media/fonts/core/Lato-Bold.ttf" });
	resources.push_back({ priority, type, "Lato-Regular", "media/fonts/core/Lato-Regular.ttf" });
	resources.push_back({ priority, type, "TitilliumWeb-Bold", "media/fonts/core/TitilliumWeb-Bold.ttf" });
	resources.push_back({ priority, type, "TitilliumWeb-Regular", "media/fonts/core/TitilliumWeb-Regular.ttf" });
	resources.push_back({ priority, type, "TitilliumWeb-SemiBold", "media/fonts/core/TitilliumWeb-SemiBold.ttf" });
}

void addCoreResources(std::vector<ResourceID>& resources)
{
	addCoreTextures(resources);
	addCoreFonts(resources);
}
