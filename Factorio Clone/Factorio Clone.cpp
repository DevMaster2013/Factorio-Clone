#include "stdafx.h"
#include "Game.h"

int main(int argc, char** argv)
{
	Game myGame;
	if (!myGame.startGame())
		return -1;
    return 0;
}