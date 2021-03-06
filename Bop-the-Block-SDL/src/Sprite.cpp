#include "Sprite.h"
#include <SDL_image.h>
#include <iostream>

Sprite::Sprite()
{
	draw_area = { 0, 0, 0, 0 };
}

Sprite::Sprite(int x, int y, int w, int h)
{
	draw_area = { x, y, w, h };
}

Sprite::~Sprite()
{
	SDL_DestroyTexture(texture);
}

bool Sprite::Init(SDL_Renderer *renderer, std::string file_location)
{
	bool status = true;

	SDL_Surface *surface_for_texture = IMG_Load(file_location.c_str());
	if (!surface_for_texture)
	{
		std::cout << file_location + " could not be found!\n";
		status = false;
	}
	else
	{
		texture = SDL_CreateTextureFromSurface(renderer, surface_for_texture);
		if (!texture)
		{
			std::cout << file_location + " could not be turned into a texture!\nIMG Error: " + IMG_GetError() + "\n";
			status = false;
		}
	}

	return status;
}

SDL_Texture *Sprite::GetTexture()
{
	return texture;
}

void Sprite::SetTexture(SDL_Texture *texture)
{
	this->texture = texture;
}

void Sprite::SetDrawingArea(int x, int y, int w, int h)
{
	draw_area = { x, y, w, h };
}

SDL_Rect Sprite::GetDrawingArea()
{
	return draw_area;
}