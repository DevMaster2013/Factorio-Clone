#pragma once

class GameState;
class Game
{
private:
	sf::RenderWindow _renderWindow;
	GameState* _currentGameState;

public:
	Game();
	~Game();

public:
	bool startGame();

public:
	void switchToGameState(GameState* newState);

public:
	sf::RenderWindow& getRenderWindow();

private:
	bool initializeGame();
	void handleEvent(const sf::Event& event);
	void updateGame(float elapsedTime);
	void renderGame();
	void releaseGame();
};

