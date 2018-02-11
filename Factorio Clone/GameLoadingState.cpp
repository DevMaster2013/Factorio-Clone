#include "stdafx.h"
#include "GameLoadingState.h"
#include "GameResourceManager.h"
#include "Game.h"

GameLoadingState::GameLoadingState()
{
}

GameLoadingState::~GameLoadingState()
{
}

bool GameLoadingState::onEnterState()
{	
	_currentProgress = 0;
	_maxProgressValue = 100;

	// Initialize the logo escape text
	_progressValueText.setString("0.0%");
	_progressValueText.setFillColor(sf::Color::Yellow);
	_progressValueText.setCharacterSize(16);

	// Initialize the progress bar
	_progressBar = sf::RectangleShape();
	_progressBar.setFillColor(sf::Color::Yellow);

	if (!GameLogoState::onEnterState())
		return false;

	_displayText.setString("Loading game resources....");
	_displayText.setFillColor(sf::Color::Yellow);
	_progressValueText.setFont(*_textFont);

	// Set the progress callback function	
	auto func = std::bind(&GameLoadingState::progressCallback, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	GameResourceManager::getInstance()->setProgressCallback(func);
	GameResourceManager::getInstance()->loadAllResources();

	return true;
}

void GameLoadingState::onHandleEvent(const sf::Event & event)
{	
	switch (event.type)
	{
	case sf::Event::Resized:
		adjustLogoSpriteSize();
		break;
	default:
		break;
	}
}

void GameLoadingState::onUpdate(float elapsedTime)
{
	_progressValueText.setString(std::to_string((int)((_currentProgress / (float)_maxProgressValue) * 100.0f)) + "%");
	auto progressSize = _progressBar.getSize();
	progressSize.x = _currentProgress * _logoSprite.getGlobalBounds().width / (float)_maxProgressValue;
	_progressBar.setSize(progressSize);

//	if (_currentProgress >= _maxProgressValue)
//		_game->switchToGameState(new GameLogoState());
}

void GameLoadingState::onRender()
{
	GameLogoState::onRender();
	_game->getRenderWindow().draw(_progressValueText);
	_game->getRenderWindow().draw(_progressBar);
}

void GameLoadingState::onExitState()
{
	GameLogoState::onExitState();
}

void GameLoadingState::adjustLogoSpriteSize()
{
	GameLogoState::adjustLogoSpriteSize();

	// Adjust the text position
	auto spriteBounds = _logoSprite.getGlobalBounds();
	auto viewSize = _stateView.getSize();

	sf::Vector2f textPos;
	textPos.x = spriteBounds.left;
	textPos.y = viewSize.y / 2.0f - _displayText.getGlobalBounds().height / 2.0f + _logoSprite.getGlobalBounds().height + _displayText.getGlobalBounds().height + 10.0f;
	_displayText.setPosition(textPos);

	textPos.x = spriteBounds.left + spriteBounds.width - _progressValueText.getGlobalBounds().width;
	textPos.y = viewSize.y / 2.0f - _progressValueText.getGlobalBounds().height / 2.0f + _logoSprite.getGlobalBounds().height + _displayText.getGlobalBounds().height;
	_progressValueText.setPosition(textPos);

	// Setup the position of the progress bar
	_progressBar.setPosition(spriteBounds.left, textPos.y + _displayText.getGlobalBounds().height + 30.0f);
	_progressBar.setSize(sf::Vector2f((float)_currentProgress, 20.0f));
}

void GameLoadingState::progressCallback(const std::string & currentText, size_t value, size_t maxValue)
{
	_currentProgress = value;
	_displayText.setString(currentText);
	_maxProgressValue = maxValue;
}
