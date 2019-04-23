#ifndef BALL_H
#define BALL_H
#include "Entity.h"

class Ball : public Entity
{
public:
	Ball(int x, int y, SDL_Rect constraints);

	void Update();
	void Draw(SDL_Renderer *renderer);
	void Reset();

	void ResetBallPosition(int ball_x_position);
	void HandleCollision(SDL_Rect *others_position, bool against_paddle);
	bool IsAlreadyDead();

private:
	const int SPRITE_WIDTH = 8;
	const int SPRITE_HEIGHT = 8;

	const int SPEED = 3;
	const int MAX_SPEED = 2;

	SDL_Rect constraints;
	float x_velocity, y_velocity;
	float x_position, y_position;
	float x_direction, y_direction;

	bool already_dead;
};
#endif