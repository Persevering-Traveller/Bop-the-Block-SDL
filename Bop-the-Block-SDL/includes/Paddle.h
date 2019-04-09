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
	int current_speed;
	int low_speed, mid_speed, hi_speed;
	int x_direction;
};

#endif