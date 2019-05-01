#ifndef GAME_H
#define GAME_H
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Paddle.h"
#include "Ball.h"
#include "LevelBuilder.h"
#include "GUI.h"

#include<fstream>

class Game
{
	enum class State { START, PLAY, PAUSE, GAME_OVER };

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

	const int PLAY_AREA_WIDTH = DESIGN_WIDTH - 96;

	void Update();
	void Draw();
	void Reset();
	void HandleControls();

	bool is_running;
	State current_state;
	int scale;
	SDL_Window *window;
	SDL_Renderer *renderer;

	Paddle player{ PLAY_AREA_WIDTH / 2, DESIGN_HEIGHT - 50, 0, PLAY_AREA_WIDTH };
	Ball ball{ PLAY_AREA_WIDTH / 2, DESIGN_HEIGHT - 100, { 0, 0, PLAY_AREA_WIDTH, DESIGN_HEIGHT } };
	LevelBuilder level_builder;

	const int MAX_LEVELS = 3;
	int level_number;
	std::string levels[3] = {
		"./data/levels/level1.dat",
		"./data/levels/level2.dat",
		"./data/levels/level3.dat",
	};
	
	GUI gui;

	const std::string HIGHSCORE_FILE = "./data/highscore.dat";
	std::fstream highscore_file_stream;
	int score, top_score;
	int ball_count;
};

#endif