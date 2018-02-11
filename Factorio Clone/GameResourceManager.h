#pragma once

#include "ResourceHolder.h"
class GameResourceManager
{
private:
	static GameResourceManager* _instance;

private:
	ResourceHolder<sf::Texture>* _textures;
	ResourceHolder<sf::Font>* _fonts;

private:
	GameResourceManager();
	~GameResourceManager();

public:
	static GameResourceManager* getInstance();
	static void releaseInstance();

public:
	void initialize();
	void release();

public:
	sf::Texture* getTexture(const std::string& textureName);
	sf::Font* getFont(const std::string& fontName);
};

