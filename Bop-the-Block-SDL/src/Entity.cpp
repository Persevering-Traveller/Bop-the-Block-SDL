#include "Entity.h"

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
	position = { x, y, position.w, position.h };
}

SDL_Rect Entity::GetPosition()
{
	return position;
}