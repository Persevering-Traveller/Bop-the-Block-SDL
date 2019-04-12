#include "Entity.h"
#include <iostream>

bool Entity::Init(SDL_Renderer *renderer, std::string file_location)
{
	bool status = true;
	if (!sprite.Init(renderer, file_location))
	{
		status = false;
	}

	return status;
}

bool Entity::IsOverlapping(SDL_Rect *others_position)
{
	// Good old fashioned Bounding Box collision
	if (position.x + position.w > others_position->x &&
		position.y + position.h > others_position->y &&
		position.x < others_position->x + others_position->w && 
		position.y < others_position->y + others_position->h)
	{
		return true;
	}

	return false;
}

void Entity::SetPosition(int x, int y)
{
	position = { x, y, sprite.GetDrawingArea().w, sprite.GetDrawingArea().h };
}

SDL_Rect Entity::GetPosition()
{
	return position;
}

void Entity::SetStartPosition(int x, int y)
{
	start_position = { x, y, sprite.GetDrawingArea().w, sprite.GetDrawingArea().h };
}

SDL_Rect Entity::GetStartPosition()
{
	return start_position;
}

Sprite *Entity::GetSprite()
{
	return &sprite;
}