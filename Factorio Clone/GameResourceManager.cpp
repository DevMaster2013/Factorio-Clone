#include "stdafx.h"
#include "GameResourceManager.h"

GameResourceManager* GameResourceManager::_instance = nullptr;

GameResourceManager::GameResourceManager()
	: _textures(nullptr)
	, _fonts(nullptr)
{
}

GameResourceManager::~GameResourceManager()
{
}

GameResourceManager * GameResourceManager::getInstance()
{
	if (_instance == nullptr)
		_instance = new GameResourceManager();
	return _instance;
}

void GameResourceManager::releaseInstance()
{
	if (_instance != nullptr)
		delete _instance;
	_instance = nullptr;
}

void GameResourceManager::initialize()
{
	_resourcesDictionary.initialize();

	_textures = new	ResourceHolder<sf::Texture>();
	_fonts = new ResourceHolder<sf::Font>();
}

void GameResourceManager::release()
{
	if (_textures != nullptr) 
		delete _textures;
	_textures = nullptr;
	if (_fonts != nullptr)
		delete _fonts;
	_fonts = nullptr;
}

void GameResourceManager::loadResources(ResourcePriority priority)
{
	// Get the resources from the dictionary
	auto resourcesList = _resourcesDictionary.getResourcesByPriority(priority);

	// Count the resources
	size_t resourcesCount = 0;
	for each (auto& resType in resourcesList)	
		resourcesCount += resType.second.size();

	// Load the resources
	size_t resourceIndex = 0;
	for each (auto& resType in resourcesList)
	{
		switch (resType.first)
		{
		case ResourceType::TEXTURE:
			for each (auto& resID in resType.second)
			{
				resourceIndex++;
				if (_callbackFunction != nullptr)
					_callbackFunction("Loading Textures...", resourceIndex, resourcesCount);
				_textures->get(resID.second.resID, resID.second.resPath);
			}
			break;
		case ResourceType::FONT:
			for each (auto& resID in resType.second)
			{
				resourceIndex++;
				if (_callbackFunction != nullptr)
					_callbackFunction("Loading Fonts...", resourceIndex, resourcesCount);
				_fonts->get(resID.second.resID, resID.second.resPath);
			}
			break;
		default:
			break;
		}		
	}
}

void GameResourceManager::setProgressCallback(std::function<void(const std::string&, size_t, size_t)> callback)
{
	_callbackFunction = callback;
}

sf::Texture* GameResourceManager::getTexture(const std::string & textureName)
{
	ResourceID& resID = _resourcesDictionary.getResource(ResourceType::TEXTURE, textureName);
	if (resID.priority == ResourcePriority::INVALID)
		return nullptr;

	if (_textures != nullptr)
		return _textures->get(textureName, resID.resPath);
	return nullptr;
}

sf::Font* GameResourceManager::getFont(const std::string & fontName)
{
	ResourceID resID = _resourcesDictionary.getResource(ResourceType::FONT, fontName);
	if (resID.priority == ResourcePriority::INVALID)
		return nullptr;

	if (_fonts != nullptr)
		return _fonts->get(fontName, resID.resPath);
	return nullptr;
}