#pragma once
#include "GameLogoState.h"

class GameLoadingState : public GameLogoState
{
private:
	sf::Text _progressValueText;
	sf::RectangleShape _progressBar;
	size_t _currentProgress;
	size_t _maxProgressValue;

public:
	GameLoadingState();
	~GameLoadingState();

private:
	virtual bool onEnterState() override;
	virtual void onHandleEvent(const sf::Event & event) override;
	virtual void onUpdate(float elapsedTime) override;
	virtual void onRender() override;
	virtual void onExitState() override;

private:
	virtual void adjustLogoSpriteSize() override;
	void progressCallback(const std::string& currentText, size_t value, size_t maxValue);
};

