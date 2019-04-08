#include "Game.h"
#include <iostream>

Game::Game()
{
	is_running = true;
}

bool Game::Init()
{
	bool status = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL could not initialize!\n";
		status = false;
	}
	else
	{
		window = SDL_CreateWindow(WINDOW_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
		if (!window)
		{
			std::cout << "A window could not be created!\n";
			status = false;
		}
		else
		{
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (!renderer)
			{
				std::cout << "Could not create the renderer!\n";
				status = false;
			}
			else
			{
				SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);

				if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
				{
					std::cout << "SDL Image could not initialize!\n";
					status = false;
				}
			}
		}
	}

	if (!player.Init(renderer, "./data/sprites/paddle.png"))
	{
		std::cout << "Player could not initialize!\n";
		status = false;
	}
	else
	{
		player.GetSprite()->SetDrawingArea(0, 0, 32, 16);
		player.SetStartPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT - 100);
		player.SetPosition(player.GetStartPosition().x, player.GetStartPosition().y);
	}

	return status;
}

void Game::Run()
{
	while (is_running)
	{
		Update();
		Draw();
	}
}

void Game::Quit()
{
	if (window)
		SDL_DestroyWindow(window);
	if (renderer)
		SDL_DestroyRenderer(renderer);
	IMG_Quit();
	SDL_Quit();
}

void Game::Update()
{
	SDL_Event event;
	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
			is_running = false;
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_ESCAPE)
				is_running = false;
		}
	}

	player.Update();
}

void Game::Draw() 
{
	SDL_RenderClear(renderer);

	player.Draw(renderer);

	SDL_RenderPresent(renderer);
}