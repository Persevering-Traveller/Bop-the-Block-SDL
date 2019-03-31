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
	void Update();
	void Draw();

	bool is_running;
	SDL_Window *window;
};

#endif