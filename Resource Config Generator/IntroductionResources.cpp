#include "IntroductionResources.h"

void addIntroductionTextures(std::vector<ResourceID>& resources)
{
	ResourcePriority priority = ResourcePriority::INTRODUCTIOIN;
	ResourceType type = ResourceType::TEXTURE;

	resources.push_back({ priority, type, "background-image-logo", "media/graphics/intro/images/background-image-logo.png" });
}

void addIntroductionFonts(std::vector<ResourceID>& resources)
{
	ResourcePriority priority = ResourcePriority::INTRODUCTIOIN;
	ResourceType type = ResourceType::FONT;

	resources.push_back({ priority, type, "Lato-Semibold", "media/fonts/intro/Lato-Semibold.ttf" });
}

void addIntroductionResources(std::vector<ResourceID>& resources)
{
	addIntroductionTextures(resources);
	addIntroductionFonts(resources);
}
