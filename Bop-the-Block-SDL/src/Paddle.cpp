#include "Paddle.h"

Paddle::Paddle(int start_x, int start_y, int x1_constraint, int x2_constraint)
{
	sprite.SetDrawingArea(0, 0, SPRITE_WIDTH, SPRITE_HEIGHT);
	position = start_position = { start_x, start_y, SPRITE_WIDTH, SPRITE_HEIGHT };
	current_max_speed = SPEED::MID;
	this->x1_constraint = x1_constraint;
	this->x2_constraint = x2_constraint;
	x_direction = 0;
	velocity = 0.f;
	x_position = position.x;
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

void Paddle::Update()
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
		velocity += MOVE_SPEED * x_direction;
		// Cap speed based on which speed mode we're in
		if (velocity >= max_speed)
			velocity = max_speed;
		else if (velocity <= -max_speed)
			velocity = -max_speed;
		x_position += velocity;

		// Constraint handling
		if (x_position < x1_constraint)
		{
			x_position = x1_constraint;
			velocity = 0;
		}
		else if (x_position > x2_constraint - SPRITE_WIDTH)
		{
			x_position = x2_constraint - SPRITE_WIDTH;
			velocity = 0;
		}
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
	velocity = 0.f;
	position = start_position;
	x_position = position.x;
}