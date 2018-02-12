#pragma once
#include <string>

enum class ResourcePriority
{
	INTRODUCTIOIN,
	CORE,
	BASE,
	INVALID
};

enum class ResourceType
{
	TEXTURE,
	FONT
};

struct ResourceID
{
public:
	ResourcePriority priority;
	ResourceType type;
	char resID[256];
	char resPath[1024];
};