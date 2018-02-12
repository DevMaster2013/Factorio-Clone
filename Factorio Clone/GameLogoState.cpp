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
	_logoTexture = GameResourceManager::getInstance()->getTexture("background-image-logo");
	if (_logoTexture == nullptr)
		return false;

	_textFont = GameResourceManager::getInstance()->getFont("Lato-Semibold");
	if (_textFont == nullptr)
		return false;

	_logoSprite = sf::Sprite(*_logoTexture);		

	// Initialize the logo escape text
	_displayText.setString("Press Escape to start game....");
	_displayText.setFillColor(sf::Color::White);
	_displayText.setFont(*_textFont);
	_displayText.setCharacterSize(16);
	
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
	_game->getRenderWindow().draw(_displayText);
}

void GameLogoState::onExitState()
{	
}

void GameLogoState::adjustLogoSpriteSize()
{
	// Keep the aspect ratio
	auto viewSize = _stateView.getSize();
	float aspectRatio = viewSize.x / (float)viewSize.y;

	// Adjust the image size	
	_logoSprite.setScale(aspectRatio, aspectRatio);
	auto textureSize = _logoTexture->getSize();

	// Adjust the sprite position
	sf::Vector2f spritePos;
	spritePos.x = viewSize.x / 2.0f - _logoSprite.getGlobalBounds().width / 2.0f;
	spritePos.y = viewSize.y / 2.0f - _logoSprite.getGlobalBounds().height / 2.0f;
	_logoSprite.setPosition(spritePos);

	// Adjust the text position
	sf::Vector2f textPos;
	textPos.x = viewSize.x / 2.0f - _displayText.getGlobalBounds().width / 2.0f;
	textPos.y = viewSize.y / 2.0f - _displayText.getGlobalBounds().height / 2.0f + _logoSprite.getGlobalBounds().height;
	_displayText.setPosition(textPos);
}
