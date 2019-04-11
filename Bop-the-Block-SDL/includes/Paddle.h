#ifndef PADDLE_H
#define PADDLE_H
#include "Entity.h"

enum class SPEED { LOW, MID, HIGH };

class Paddle : public Entity
{
public:
	Paddle(int start_x, int start_y, int x1_constraint, int x2_constraint);
	void Move(int x_direction);
	void ChangeSpeed(SPEED which_speed);

	void Update(float delta_time);
	void Draw(SDL_Renderer *renderer);
	void Reset();

private:
	const int SPRITE_WIDTH = 32;
	const int SPRITE_HEIGHT = 16;

	const int MOVE_SPEED = 3;
	const int LOW_SPEED = 100;
	const int MID_SPEED = 200;
	const int HI_SPEED = 400;

	int x1_constraint, x2_constraint;

	SPEED current_max_speed;
	int x_direction;
	float x_position;
	float velocity;
};

#endif