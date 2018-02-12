#include <iostream>
#include <fstream>
#include <vector>
#include "IntroductionResources.h"
#include "BaseResources.h"
#include "CoreResources.h"

int main(int argc, char** argv)
{
	std::vector<ResourceID> resources;

	addIntroductionResources(resources);
	addCoreResources(resources);
	addBaseResources(resources);

	std::ofstream outFile("../Factorio Clone/media/ResourcesDictionary.dat", std::ios_base::binary);
	size_t resourcesCount = resources.size();
	outFile.write((const char*)&resourcesCount, sizeof(resourcesCount));
	outFile.write((const char*)resources.data(), sizeof(ResourceID) * resourcesCount);
	outFile.close();
}