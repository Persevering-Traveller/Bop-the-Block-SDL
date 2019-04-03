#ifndef ENTITY_H
#define ENTITY_H
#include "Sprite.h"

class Entity
{
public:
	virtual void Update() = 0;
	virtual void Draw(SDL_Renderer *renderer) = 0;

protected:
	SDL_Rect position;
	Sprite sprite;
};
#endif