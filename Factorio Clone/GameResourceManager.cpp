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
	_textures = new	ResourceHolder<sf::Texture>("media/graphics");
	_fonts = new ResourceHolder<sf::Font>("media/fonts");
}

void GameResourceManager::release()
{
	if (_textures != nullptr) _textures->releaseAll();
	if (_fonts != nullptr) _fonts->releaseAll();
}

void GameResourceManager::loadAllResources()
{
	size_t maxValue = 0;
	maxValue += _textures->getResourcesCount();
	maxValue += _fonts->getResourcesCount();

	// Set call bck function
	size_t resourcesCount = 0;
	_textures->setProgressCallback(_callbackFunction, "Loading textures...", resourcesCount, maxValue); resourcesCount += _textures->getResourcesCount();
	_fonts->setProgressCallback(_callbackFunction, "Loading fonts...", resourcesCount, maxValue); resourcesCount += _fonts->getResourcesCount();

	// Load all resources
	texturesThreadLoad = std::thread([&]() {_textures->loadAll(); });
//	std::thread fontsThreadLoad([&]() {_fonts->loadAll(); });
//
//	texturesThreadLoad.join();
//	fontsThreadLoad.join();
}

void GameResourceManager::setProgressCallback(std::function<void(const std::string&, size_t, size_t)> callback)
{
	_callbackFunction = callback;
}

sf::Texture* GameResourceManager::getTexture(const std::string & textureName)
{
	if (_textures != nullptr)
		return _textures->get(textureName);
	return nullptr;
}

sf::Font* GameResourceManager::getFont(const std::string & fontName)
{
	if (_fonts != nullptr)
		return _fonts->get(fontName);
	return nullptr;
}
