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

	void Update();
	void Draw(SDL_Renderer *renderer);
	void Reset();

private:
	const int SPRITE_WIDTH = 32;
	const int SPRITE_HEIGHT = 8;

	const int MOVE_SPEED = 3;
	const int LOW_SPEED = 1;
	const int MID_SPEED = 2;
	const int HI_SPEED = 4;

	int x1_constraint, x2_constraint;

	SPEED current_max_speed;
	int x_direction;
	float x_position;
	float velocity;
};

#endif