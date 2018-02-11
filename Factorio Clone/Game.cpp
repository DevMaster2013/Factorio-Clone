#include "stdafx.h"
#include "Game.h"
#include "GameState.h"
#include "GameResourceManager.h"
#include "GameLogoState.h"

Game::Game()
	: _currentGameState(nullptr)
{
}

Game::~Game()
{
}

bool Game::startGame()
{
	if (!initializeGame())
		return false;

	sf::Clock loopClock;
	while (_renderWindow.isOpen())
	{
		sf::Event event;
		while (_renderWindow.pollEvent(event))
			handleEvent(event);
		if (!_renderWindow.isOpen())
			_renderWindow.close();

		updateGame(loopClock.restart().asSeconds());

		_renderWindow.clear();
		renderGame();
		_renderWindow.display();
	}

	releaseGame();

	return true;
}

void Game::switchToGameState(GameState * newState)
{
	if (_currentGameState == newState)
		return;

	if (_currentGameState != nullptr)
	{
		_currentGameState->exitState();
		delete _currentGameState;	
	}

	_currentGameState = newState;
	if (_currentGameState != nullptr)
		_currentGameState->enterState(this);
}

sf::RenderWindow & Game::getRenderWindow()
{
	return _renderWindow;
}

bool Game::initializeGame()
{
	_renderWindow.create(sf::VideoMode(800, 600), "Factorio Clone", sf::Style::Default);

	// Initilize the resource manager
	GameResourceManager::getInstance()->initialize();

	// Run the logo state
	switchToGameState(new GameLogoState());

	return true;
}

void Game::handleEvent(const sf::Event & event)
{	
	switch (event.type)
	{
	case sf::Event::Closed:
		_renderWindow.close();
		break;
	default:
		break;
	}
	
	if (_currentGameState != nullptr)
		_currentGameState->handleEvent(event);
}

void Game::updateGame(float elapsedTime)
{
	if (_currentGameState != nullptr)
		_currentGameState->update(elapsedTime);
}

void Game::renderGame()
{
	if (_currentGameState != nullptr)
		_currentGameState->render();
}

void Game::releaseGame()
{
	switchToGameState(nullptr);

	GameResourceManager::releaseInstance();

	if (_renderWindow.isOpen()) 
		_renderWindow.close();
}
