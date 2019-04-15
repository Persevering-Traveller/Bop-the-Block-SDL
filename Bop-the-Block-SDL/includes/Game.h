#ifndef GAME_H
#define GAME_H
#include <SDL.h>
#include <SDL_image.h>
#include "Paddle.h"
#include "Ball.h"
#include "Block.h"

class Game
{
public:
	Game();
	bool Init();
	bool Setup();
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

	Paddle player{ DESIGN_WIDTH / 2, DESIGN_HEIGHT - 50, 0, DESIGN_WIDTH };
	Ball ball{ DESIGN_WIDTH / 2, DESIGN_HEIGHT - 100, { 0, 0, DESIGN_WIDTH, DESIGN_HEIGHT } };
	Block block{ DESIGN_WIDTH / 2, DESIGN_HEIGHT / 2 };
};

#endif