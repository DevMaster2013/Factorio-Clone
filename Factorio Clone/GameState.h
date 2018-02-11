#pragma once

class Game;
class GameState
{
protected:
	Game* _game;
	sf::View _stateView;

public:
	GameState();
	virtual ~GameState();

public:
	bool enterState(Game* game);
	void handleEvent(const sf::Event& event);
	void update(float elapsedTime);
	void render();
	void exitState();

protected:
	virtual bool onEnterState() = 0;
	virtual void onHandleEvent(const sf::Event& event) = 0;
	virtual void onUpdate(float elapsedTime) = 0;
	virtual void onRender() = 0;
	virtual void onExitState() = 0;
};

