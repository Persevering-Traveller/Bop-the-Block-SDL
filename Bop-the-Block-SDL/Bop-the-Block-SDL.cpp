// Bop-the-Block-SDL.cpp : Defines the entry point for the console application.
#include <SDL.h>
#include "Game.h"

int main(int argc, char *argv[])
{
	Game game;
	if (game.Init() && game.Setup())
		game.Run();
	game.Quit();
    return 0;
}

