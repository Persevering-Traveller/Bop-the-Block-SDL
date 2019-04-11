#ifndef BALL_H
#define BALL_H
#include "Entity.h"

class Ball : public Entity
{
public:
	Ball(int x, int y, SDL_Rect constraints);

	void Update(float delta_time);
	void Draw(SDL_Renderer *renderer);
	void Reset();

private:
	const int SPRITE_WIDTH = 16;
	const int SPRITE_HEIGHT = 16;

	const int SPEED = 3;
	const int MAX_SPEED = 100;

	SDL_Rect constraints;
	float x_velocity, y_velocity;
	float x_position, y_position;
	float x_direction, y_direction;
};
#endif