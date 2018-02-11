#pragma once
#include "GameState.h"
class GameLoadingState : public GameState
{
public:
	GameLoadingState();
	~GameLoadingState();

private:
	virtual bool onEnterState() override;
	virtual void onHandleEvent(const sf::Event & event) override;
	virtual void onUpdate(float elapsedTime) override;
	virtual void onRender() override;
	virtual void onExitState() override;
};

