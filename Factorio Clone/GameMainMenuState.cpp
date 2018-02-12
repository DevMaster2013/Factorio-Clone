#include "stdafx.h"
#include "GameMainMenuState.h"
#include "GameResourceManager.h"
#include "Game.h"

GameMainMenuState::GameMainMenuState()
{
}

GameMainMenuState::~GameMainMenuState()
{
}

bool GameMainMenuState::onEnterState()
{
	// Initialize the logo texture
	_backgroundTexture = GameResourceManager::getInstance()->getTexture("background-image");
	if (_backgroundTexture == nullptr)
		return false;

	_backgroundSprite = sf::Sprite(*_backgroundTexture);
	adjustBackgroundSpriteSize();

	return true;
}

void GameMainMenuState::onHandleEvent(const sf::Event & event)
{
	switch (event.type)
	{
	case sf::Event::Resized:
		adjustBackgroundSpriteSize();
		break;
	default:
		break;
	}
}

void GameMainMenuState::onUpdate(float elapsedTime)
{
}

void GameMainMenuState::onRender()
{
	_game->getRenderWindow().draw(_backgroundSprite);
}

void GameMainMenuState::onExitState()
{
}

void GameMainMenuState::adjustBackgroundSpriteSize()
{
	auto viewSize = _stateView.getSize();
	auto textureSize = _backgroundTexture->getSize();
	_backgroundSprite.setScale(viewSize.x / textureSize.x, viewSize.x / textureSize.y);
}
