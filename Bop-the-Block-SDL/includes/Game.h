#ifndef GAME_H
#define GAME_H
#include <SDL.h>
#include <SDL_image.h>
#include "Paddle.h"

class Game
{
public:
	Game();
	bool Init();
	void Run();
	void Quit();

private:
	const int DESIGN_WIDTH = 320;
	const int DESIGN_HEIGHT = 240;
	const char *WINDOW_NAME = "Bop the Block";

	void Update();
	void Draw();
	void HandleControls();

	bool is_running;
	int scale;
	SDL_Window *window;
	SDL_Renderer *renderer;

	float start_ticks, delta_time;

	Paddle player;
};

#endif