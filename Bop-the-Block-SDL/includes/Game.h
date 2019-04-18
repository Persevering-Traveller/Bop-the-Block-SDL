#ifndef GAME_H
#define GAME_H
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Paddle.h"
#include "Ball.h"
#include "Block.h"
#include "GUI.h"

#include<fstream>

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

	const int PLAY_AREA_WIDTH = DESIGN_WIDTH - 100;

	void Update();
	void Draw();
	void HandleControls();

	bool is_running;
	int scale;
	SDL_Window *window;
	SDL_Renderer *renderer;

	Paddle player{ PLAY_AREA_WIDTH / 2, DESIGN_HEIGHT - 50, 0, PLAY_AREA_WIDTH };
	Ball ball{ PLAY_AREA_WIDTH / 2, DESIGN_HEIGHT - 100, { 0, 0, PLAY_AREA_WIDTH, DESIGN_HEIGHT } };
	Block block{ PLAY_AREA_WIDTH / 2, DESIGN_HEIGHT / 2 };

	GUI gui;

	const std::string HIGHSCORE_FILE = "./data/highscore.dat";
	std::fstream highscore_file_stream;
	int score, top_score;
};

#endif