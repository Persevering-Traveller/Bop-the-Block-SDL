#include "Game.h"
#include <iostream>

Game::Game()
{
	is_running = true;
	scale = 3;

	top_score = score = 0;
	// For now until we create a Start Screen
	current_state = Game::State::PLAY;
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

				if (!TTF_Init() == -1)
				{
					std::cout << "SDL TTF could not initialize!\n";
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

	gui.Quit();
	highscore_file_stream.close();

	TTF_Quit();
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
		std::cout << "Ball could not initialize!\n";
		status = false;
	};

	if (!block.Init(renderer, "./data/sprites/block.png"))
	{
		std::cout << "Block could not initialize!\n";
		status = false;
	};

	if (!gui.Init(renderer, "./data/font/font.ttf"))
	{
		std::cout << "GUI could not initialize!\n";
		status = false;
	}

	// Read the Highscore data file
	highscore_file_stream.open(HIGHSCORE_FILE, std::fstream::in);
	if (!highscore_file_stream.is_open())
	{
		// If the file doesn't exist yet, create it
		highscore_file_stream.open(HIGHSCORE_FILE, std::fstream::out);
		highscore_file_stream.close();
	}
	else
	{
		// Read the high score from a previous session
		std::string scoreboard;
		highscore_file_stream >> scoreboard;
		top_score = std::atoi(scoreboard.c_str());

		highscore_file_stream.close();
	}

	return status;
}

void Game::HandleControls()
{
	const Uint8 *keyboard_state = SDL_GetKeyboardState(NULL);

	int x_direction = 0;

	// Player controls
	if (keyboard_state[SDL_SCANCODE_LEFT])
		x_direction += -1;
	if (keyboard_state[SDL_SCANCODE_RIGHT])
		x_direction += 1;

	player.Move(x_direction);
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
	// Block Collision
	if (ball.IsOverlapping(&block.GetPosition()))
	{
		ball.HandleCollision(&block.GetPosition(), false);
		block.HandleCollision();
		score+=1;
	}

	// Assign top score
	if (score > top_score)
	{
		top_score = score;
		// Write the new high score everytime it changes
		highscore_file_stream.open(HIGHSCORE_FILE, std::fstream::out | std::fstream::trunc);
		highscore_file_stream << std::to_string(top_score);
		highscore_file_stream.close();
	}

	gui.Update(renderer, top_score, score, 1, 3);
}

void Game::Draw() 
{
	SDL_RenderClear(renderer);

	gui.Draw(renderer);
	player.Draw(renderer);
	block.Draw(renderer);
	ball.Draw(renderer);

	SDL_RenderPresent(renderer);
}