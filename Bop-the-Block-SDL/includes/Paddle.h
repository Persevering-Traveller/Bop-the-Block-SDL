#ifndef PADDLE_H
#define PADDLE_H
#include "Entity.h"

enum class SPEED { LOW, MID, HIGH };

class Paddle : public Entity
{
public:
	Paddle();
	void Move(int x_direction);
	void ChangeSpeed(SPEED which_speed);
	void Update(float delta_time);
	void Draw(SDL_Renderer *renderer);
	void Reset();
private:
	const int speed = 3;
	SPEED current_max_speed;
	const int LOW_SPEED = 100;
	const int MID_SPEED = 200;
	const int HI_SPEED = 400;

	int x_direction;
	float x_position;
	float velocity;
};

#endif