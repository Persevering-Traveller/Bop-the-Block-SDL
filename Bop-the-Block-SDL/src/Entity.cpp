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

bool Entity::IsOverlapping(SDL_Rect *collision_rect)
{
	// Good old fashioned Bounding Box collision
	if (position.x + position.w > collision_rect->x && position.y < collision_rect->y + collision_rect->h ||
		position.x + position.w > collision_rect->x && position.y + position.h > collision_rect->y ||
		position.x > collision_rect->x + collision_rect->w && position.y < collision_rect->y + collision_rect->h ||
		position.x > collision_rect->x + collision_rect->w && position.y + position.h > collision_rect->y)
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