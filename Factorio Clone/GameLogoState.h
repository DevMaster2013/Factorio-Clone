#pragma once

#include "GameState.h"

class GameLogoState : public GameState
{
private:
	sf::Texture* _logoTexture;
	sf::Font* _logoFont;
	sf::Sprite _logoSprite;
	sf::Text _logoEscapeText;	

public:
	GameLogoState();
	~GameLogoState();

private:
	virtual bool onEnterState() override;
	virtual void onHandleEvent(const sf::Event& event) override;
	virtual void onUpdate(float elapsedTime) override;
	virtual void onRender() override;
	virtual void onExitState() override;

private:
	void adjustLogoSpriteSize();
};

