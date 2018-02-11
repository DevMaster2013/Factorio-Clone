#pragma once

#include "GameState.h"

class GameLogoState : public GameState
{
protected:
	sf::Texture* _logoTexture;
	sf::Font* _textFont;
	sf::Sprite _logoSprite;
	sf::Text _displayText;	

public:
	GameLogoState();
	~GameLogoState();

protected:
	virtual bool onEnterState() override;
	virtual void onHandleEvent(const sf::Event& event) override;
	virtual void onUpdate(float elapsedTime) override;
	virtual void onRender() override;
	virtual void onExitState() override;

protected:
	virtual void adjustLogoSpriteSize();
};

