#include "Text.h"
#include <SDL_ttf.h>

Text::Text(std::string text, int x, int y, int w, int h)
{
	bool status = true;
	this->text = text;
	text_position = { x, y, w, h };
	text_color = { 0, 0, 0 };
}

bool Text::Setup(SDL_Renderer *renderer, TTF_Font *font)
{
	bool status = true;
	if (!ChangeTextTexture(renderer, font))
	{
		printf("Could not setup text!\n");
		status = false;
	}

	return status;
}

void Text::Change_Text(SDL_Renderer *renderer, TTF_Font *font, std::string new_text)
{
	text = new_text;
	SDL_DestroyTexture(texture);
	if (!ChangeTextTexture(renderer, font))
	{
		printf("Could not update text's texture!\n");
	}
}

void Text::Draw(SDL_Renderer *renderer)
{
	SDL_RenderCopy(renderer, texture, NULL, &text_position);
}

void Text::Quit()
{
	SDL_DestroyTexture(texture);
	text = "";
}

bool Text::ChangeTextTexture(SDL_Renderer *renderer, TTF_Font *font)
{
	bool status = true;

	SDL_Surface *temp_surface = TTF_RenderText_Solid(font, text.c_str(), text_color);
	if (!temp_surface)
	{
		printf("Could not create text surface!\n");
		status = false;
	}
	else
	{
		texture = SDL_CreateTextureFromSurface(renderer, temp_surface);
		if (!texture)
		{
			printf("Could not create text texture from surface!\n");
			status = false;
		}
		SDL_FreeSurface(temp_surface);
	}

	return status;
}