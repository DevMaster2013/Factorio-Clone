#include "stdafx.h"
#include "GameState.h"
#include "Game.h"

GameState::GameState()
	: _game(nullptr)
{
}

GameState::~GameState()
{
}

bool GameState::enterState(Game* game)
{
	_game = game;
	_stateView = _game->getRenderWindow().getDefaultView();
	return onEnterState();
}

void GameState::handleEvent(const sf::Event & event)
{
	switch (event.type)
	{
	case sf::Event::Resized:
		_stateView.setSize((float)event.size.width, (float)event.size.height);
		_stateView.setCenter(event.size.width / 2.0f, event.size.height / 2.0f);
		break;
	default:
		break;
	}

	onHandleEvent(event);
}

void GameState::update(float elapsedTime)
{
	_game->getRenderWindow().setView(_stateView);
	onUpdate(elapsedTime);
}

void GameState::render()
{
	onRender();
}

void GameState::exitState()
{
	onExitState();
}