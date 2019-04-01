#ifndef GAME_H
#define GAME_H
#include <SDL.h>

class Game
{
public:
	Game();
	bool Init();
	void Run();
	void Quit();

private:
	const int WINDOW_WIDTH = 640;
	const int WINDOW_HEIGHT = 480;
	const char* WINDOW_NAME = "Bop the Block";

	void Update();
	void Draw();

	bool is_running;
	SDL_Window *window;
};

#endif