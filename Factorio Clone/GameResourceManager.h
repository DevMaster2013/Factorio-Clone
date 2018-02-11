#pragma once

#include "ResourceHolder.h"
class GameResourceManager
{
private:
	static GameResourceManager* _instance;
	std::thread texturesThreadLoad;

private:
	ResourceHolder<sf::Texture>* _textures;
	ResourceHolder<sf::Font>* _fonts;
	std::function<void(const std::string&, size_t, size_t)> _callbackFunction;

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
	void loadAllResources();
	void setProgressCallback(std::function<void(const std::string&, size_t, size_t)> callback);

public:
	sf::Texture* getTexture(const std::string& textureName);
	sf::Font* getFont(const std::string& fontName);
};

