#include "Paddle.h"

Paddle::Paddle()
{
	current_max_speed = SPEED::MID;
	x_direction = 0;
	velocity = 0.f;
	x_position = 0.f;
}

void Paddle::Move(int x_direction)
{
	if (x_direction >= 1) this->x_direction = 1;
	else if (x_direction <= -1) this->x_direction = -1;
	else this->x_direction = 0;
}

void Paddle::ChangeSpeed(SPEED which_speed)
{
	current_max_speed = which_speed;
}

void Paddle::Update(float delta_time)
{
	int max_speed;
	switch (current_max_speed)
	{
		case SPEED::HIGH: max_speed = HI_SPEED; break;
		case SPEED::MID: max_speed = MID_SPEED; break;
		case SPEED::LOW: max_speed = LOW_SPEED; break;
	}

	if (x_direction == 0)
		velocity = 0;
	else
	{
		velocity += speed * x_direction;
		// Cap speed based on which speed mode we're in
		if (velocity >= max_speed)
			velocity = max_speed;
		else if (velocity <= -max_speed)
			velocity = -max_speed;
		x_position += velocity * delta_time;
	}
	position.x = (int)x_position;
}

void Paddle::Draw(SDL_Renderer *renderer)
{
	SDL_RenderCopy(renderer, sprite.GetTexture(), &sprite.GetDrawingArea(), &position);
}

void Paddle::Reset()
{
	current_max_speed = SPEED::MID;
	x_direction = 0;
	position = start_position;
}