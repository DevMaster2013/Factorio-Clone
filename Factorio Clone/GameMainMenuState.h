#pragma once
#include "GameState.h"

class GameMainMenuState : public GameState
{
private:
	sf::Texture* _backgroundTexture;
	sf::Sprite _backgroundSprite;

public:
	GameMainMenuState();
	~GameMainMenuState();

private:
	virtual bool onEnterState() override;
	virtual void onHandleEvent(const sf::Event & event) override;
	virtual void onUpdate(float elapsedTime) override;
	virtual void onRender() override;
	virtual void onExitState() override;

private:
	virtual void adjustBackgroundSpriteSize();
};

