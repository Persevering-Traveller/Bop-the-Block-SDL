#include "GUI.h"

bool GUI::InitFont(SDL_Renderer *renderer, std::string file_location)
{
	bool status = true;

	gui_font = TTF_OpenFont(file_location.c_str(), TEXT_POINT_SIZE);
	if (!gui_font)
	{
		printf("Could not initialize GUI font!\n");
		status = false;
	}

	if (!top_score_text.Setup(renderer, gui_font))
	{
		printf("Could not setup Top Score text!\n");
		status = false;
	}

	if (!score_text.Setup(renderer, gui_font))
	{
		printf("Could not setup Score text!\n");
		status = false;
	}

	if (!stage_text.Setup(renderer, gui_font))
	{
		printf("Could not setup Stage text!\n");
		status = false;
	}

	if (!balls_text.Setup(renderer, gui_font))
	{
		printf("Could not setup Balls text!\n");
		status = false;
	}

	if (!game_over_text.Setup(renderer, gui_font))
	{
		printf("Could not setup Game Over text!\n");
		status = false;
	}

	return status;
}

bool GUI::InitStartLogo(SDL_Renderer *renderer, std::string file_location)
{
	bool status = true;

	if (!start_screen_logo.Init(renderer, file_location))
	{
		printf("Could not initialize start screen logo's sprite!\n");
		status = false;
	}

	return status;
}

void GUI::Update(SDL_Renderer *renderer, int top, int score, int stage, int balls)
{
	if (top_score_prev != top)
	{
		top_score_text.Change_Text(renderer, gui_font, TOP_SCORE_LABEL + std::to_string(top));
		top_score_prev = top;
	}

	if (score_prev != score)
	{
		score_text.Change_Text(renderer, gui_font, SCORE_LABEL + std::to_string(score));
		score_prev = score;
	}

	if (stage_prev != stage)
	{
		stage_text.Change_Text(renderer, gui_font, STAGE_LABEL + std::to_string(stage));
		stage_prev = stage;
	}

	if (balls_prev != balls)
	{
		balls_text.Change_Text(renderer, gui_font, BALLS_LABEL + std::to_string(balls));
		balls_prev = balls;
	}
}

void GUI::DrawStart(SDL_Renderer *renderer)
{
	SDL_RenderCopy(renderer,
		start_screen_logo.GetTexture(),
		&start_screen_logo.GetDrawingArea(),
		&START_LOGO_POSITION);
}

void GUI::DrawGameplay(SDL_Renderer *renderer)
{
	top_score_text.Draw(renderer);
	score_text.Draw(renderer);
	stage_text.Draw(renderer);
	balls_text.Draw(renderer);
}

void GUI::DrawGameOver(SDL_Renderer *renderer)
{
	game_over_text.Draw(renderer);
}

void GUI::Quit()
{
	top_score_text.Quit();
	score_text.Quit();
	stage_text.Quit();
	balls_text.Quit();
	game_over_text.Quit();
}