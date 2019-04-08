#include "Paddle.h"

Paddle::Paddle()
{
	low_speed = 3;
	mid_speed = 4;
	hi_speed = 5;

	current_speed = mid_speed;

	x_direction = 0;
}

void Paddle::Move(int x_direction)
{
	if (x_direction >= 1) this->x_direction = 1;
	else if (x_direction <= 1) this->x_direction = -1;
	else this->x_direction = 0;
}

void Paddle::ChangeSpeed(SPEED which_speed)
{
	switch (which_speed)
	{
	case SPEED::LOW: current_speed = low_speed; break;
	case SPEED::MID: current_speed = mid_speed; break;
	case SPEED::HIGH: current_speed = hi_speed; break;
	default: current_speed = mid_speed;
	}
}

void Paddle::Update()
{
	position.x += current_speed * x_direction; // * delta_time
}

void Paddle::Draw(SDL_Renderer *renderer)
{
	SDL_RenderCopy(renderer, sprite.GetTexture(), &sprite.GetDrawingArea(), &position);
}

void Paddle::Reset()
{
	current_speed = mid_speed;
	x_direction = 0;
	position = start_position;
}