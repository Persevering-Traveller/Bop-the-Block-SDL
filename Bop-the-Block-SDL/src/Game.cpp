#include "Game.h"
#include <iostream>

Game::Game()
{
	is_running = true;
	scale = 3;
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
		window = SDL_CreateWindow(WINDOW_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, DESIGN_WIDTH * scale, DESIGN_HEIGHT * scale, SDL_WINDOW_SHOWN);
		if (!window)
		{
			std::cout << "A window could not be created!\n";
			status = false;
		}
		else
		{
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (!renderer)
			{
				std::cout << "Could not create the renderer!\n";
				status = false;
			}
			else
			{
				SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
				SDL_RenderSetLogicalSize(renderer, DESIGN_WIDTH, DESIGN_HEIGHT);
				SDL_RenderSetIntegerScale(renderer, SDL_TRUE);

				if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
				{
					std::cout << "SDL Image could not initialize!\n";
					status = false;
				}
			}
		}
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

bool Game::Setup()
{
	bool status = true;

	if (!player.Init(renderer, "./data/sprites/paddle.png"))
	{
		std::cout << "Player could not initialize!\n";
		status = false;
	};

	if (!ball.Init(renderer, "./data/sprites/ball.png"))
	{
		std::cout << "Player could not initialize!\n";
		status = false;
	};

	return status;
}

void Game::HandleControls()
{
	const Uint8 *keyboard_state = SDL_GetKeyboardState(NULL);

	// Player controls
	if (keyboard_state[SDL_SCANCODE_LEFT])
		player.Move(-1);
	else if (keyboard_state[SDL_SCANCODE_RIGHT])
		player.Move(1);
	else
		player.Move(0);
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

			if (event.key.keysym.sym == SDLK_z)
				player.ChangeSpeed(SPEED::HIGH);
			else if (event.key.keysym.sym == SDLK_x)
				player.ChangeSpeed(SPEED::LOW);
		}
		if (event.type == SDL_KEYUP)
		{
			if (event.key.keysym.sym == SDLK_z || event.key.keysym.sym == SDLK_x)
				player.ChangeSpeed(SPEED::MID);
		}
	}

	HandleControls();
	
	player.Update();
	ball.Update();

	// Paddle Collision
	if (ball.IsOverlapping(&player.GetPosition()))
		ball.HandleCollision(&player.GetPosition(), true);
}

void Game::Draw() 
{
	SDL_RenderClear(renderer);

	player.Draw(renderer);
	ball.Draw(renderer);

	SDL_RenderPresent(renderer);
}