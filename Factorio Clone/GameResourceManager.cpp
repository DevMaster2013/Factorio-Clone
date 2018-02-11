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
	_textures = new	ResourceHolder<sf::Texture>("media/graphics/graphics.ini");
	_fonts = new ResourceHolder<sf::Font>("media/fonts/fonts.ini");
}

void GameResourceManager::release()
{
	if (_textures != nullptr) _textures->releaseAll();
	if (_fonts != nullptr) _fonts->releaseAll();
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
