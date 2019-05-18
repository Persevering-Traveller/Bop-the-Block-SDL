#ifndef BLOCK_H
#define BLOCK_H
#include "Entity.h"

class Block : public Entity
{
public:
	Block();
	int GetPointValue();
	void SetPointValue(int value);
	bool GetAlive();
	void SetAlive(bool value);
	void HandleCollision();

	void Update();
	void Draw(SDL_Renderer *renderer);
	void Reset();

private:
	const int SPRITE_WIDTH = 16;
	const int SPRITE_HEIGHT = 8;

	bool alive;
	int point_value;
};
#endif