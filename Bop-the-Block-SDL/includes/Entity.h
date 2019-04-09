#ifndef ENTITY_H
#define ENTITY_H
#include "Sprite.h"

class Entity
{
public:
	bool Init(SDL_Renderer *renderer, std::string file_location);
	bool IsOverlapping(SDL_Rect *collision_rect);
	void SetPosition(int x, int y);
	SDL_Rect GetPosition();
	void SetStartPosition(int x, int y);
	SDL_Rect GetStartPosition();
	Sprite *GetSprite();

	
	virtual void Update(float delta_time) = 0;
	virtual void Draw(SDL_Renderer *renderer) = 0;
	virtual void Reset() = 0;

protected:
	SDL_Rect start_position;
	SDL_Rect position;
	Sprite sprite;
};
#endif