#include "stdafx.h"
#include "GameLogoState.h"
#include "GameLoadingState.h"
#include "Game.h"
#include "GameResourceManager.h"

GameLogoState::GameLogoState()
{
}

GameLogoState::~GameLogoState()
{
}

bool GameLogoState::onEnterState()
{
	// Initialize the logo texture
	_logoTexture = GameResourceManager::getInstance()->getTexture("factorio-logo");
	if (_logoTexture == nullptr)
		return false;

	_logoFont = GameResourceManager::getInstance()->getFont("linden_hill");
	if (_logoFont == nullptr)
		return false;

	_logoSprite = sf::Sprite(*_logoTexture);		

	// Initialize the logo escape text
	_logoEscapeText.setString("Press Escape to start game....");
	_logoEscapeText.setFillColor(sf::Color::White);
	_logoEscapeText.setFont(*_logoFont);
	_logoEscapeText.setCharacterSize(16);
	
	adjustLogoSpriteSize();

	return true;
}

void GameLogoState::onHandleEvent(const sf::Event & event)
{
	switch (event.type)
	{
	case sf::Event::KeyPressed:
		switch (event.key.code)
		{
		case sf::Keyboard::Escape:
			_game->switchToGameState(new GameLoadingState());
			break;
		default:
			break;
		}
		break;
	case sf::Event::Resized:
		adjustLogoSpriteSize();
		break;
	default:
		break;
	}	
}

void GameLogoState::onUpdate(float elapsedTime)
{
	static float totalElapsedTime = 0.0f;
	totalElapsedTime += elapsedTime;
	if (totalElapsedTime > 10.0f)	
		_game->switchToGameState(new GameLoadingState());	
}

void GameLogoState::onRender()
{
	_game->getRenderWindow().draw(_logoSprite);
	_game->getRenderWindow().draw(_logoEscapeText);
}

void GameLogoState::onExitState()
{	
}

void GameLogoState::adjustLogoSpriteSize()
{
	// Adjust the image size
	auto viewSize = _stateView.getSize();
	auto textureSize = _logoTexture->getSize();
	_logoSprite.setScale(viewSize.x / textureSize.x, viewSize.y / textureSize.y);

	// Adjust the text position
	sf::Vector2f textPos;
	textPos.x = viewSize.x / 2.0f - _logoEscapeText.getGlobalBounds().width / 2.0f;
	textPos.y = viewSize.y / 2.0f - _logoEscapeText.getGlobalBounds().height / 2.0f + (150.0f * viewSize.y / textureSize.y);
	_logoEscapeText.setPosition(textPos);
}
