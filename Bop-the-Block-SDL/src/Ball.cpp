#include "Ball.h"

Ball::Ball(int x, int y, SDL_Rect constraints)
{
	position = start_position = { x, y, SPRITE_WIDTH, SPRITE_HEIGHT };
	sprite.SetDrawingArea(0, 0, SPRITE_WIDTH, SPRITE_HEIGHT);
	this->constraints = constraints;
	x_velocity = y_velocity = 0;
	x_position = position.x;
	y_position = position.y;
	// Start direction will always be heading towards
	// the bottom right, towards the paddle
	x_direction = 1;
	y_direction = 1;
}

void Ball::Update(float delta_time)
{
	// Handle play area constraints
	if (x_position <= constraints.x)
	{
		x_direction = -x_direction;
		x_velocity = 0;
		x_position = constraints.x;
	}
	else if (x_position + SPRITE_WIDTH >= constraints.w)
	{
		x_direction = -x_direction;
		x_velocity = 0;
		x_position = constraints.w - SPRITE_WIDTH;
	}
	if (y_position <= constraints.y)
	{
		y_direction = -y_direction;
		y_velocity = 0;
		y_position = constraints.y;
	}
	else if (y_position + SPRITE_HEIGHT >= constraints.h)
	{
		y_direction = -y_direction;
		y_velocity = 0;
		y_position = constraints.h - SPRITE_HEIGHT;
	}

	x_velocity += SPEED * x_direction;
	y_velocity += SPEED * y_direction;

	// Cap speed
	if (x_velocity >= MAX_SPEED)
		x_velocity = MAX_SPEED;
	else if (x_velocity <= -MAX_SPEED)
		x_velocity = -MAX_SPEED;
	if (y_velocity >= MAX_SPEED)
		y_velocity = MAX_SPEED;
	else if (y_velocity <= -MAX_SPEED)
		y_velocity = -MAX_SPEED;

	x_position += x_velocity * delta_time;
	y_position += y_velocity * delta_time;

	position.x = (int)x_position;
	position.y = (int)y_position;
}

void Ball::Draw(SDL_Renderer *renderer)
{
	SDL_RenderCopy(renderer, sprite.GetTexture(), &sprite.GetDrawingArea(), &position);
}

void Ball::Reset()
{
	position = start_position;
	x_velocity = y_velocity = 0;
	x_position = position.x;
	y_position = position.y;
	x_direction = 1;
	y_direction = 1;
}