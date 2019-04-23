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
	already_dead = false;
}

void Ball::Update()
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
	// If off the bottom of the screen, just stop, that ball is dead
	else if (y_position > constraints.h)
	{
		y_direction = 0;
		y_velocity = 0;
		already_dead = true;
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

	x_position += x_velocity;
	y_position += y_velocity;

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
	already_dead = false;
}

void Ball::HandleCollision(SDL_Rect *others_position, bool against_paddle)
{
	// Our bottom overlapping their top
	if (position.y + position.h >= others_position->y && position.y < others_position->y)
	{
		y_direction = -y_direction;
		y_velocity = 0;
		y_position = others_position->y - SPRITE_HEIGHT;
	}
	// Our top overlapping their bottom
	else if (position.y <= others_position->y + others_position->h && position.y + position.h > others_position->y + others_position->h)
	{
		y_direction = -y_direction;
		y_velocity = 0;
		y_position = others_position->y + others_position->h;
	}
	// Our right overlapping their left
	if (position.x + position.w >= others_position->x && position.x < others_position->x)
	{
		if (against_paddle)
		{
			y_direction = -y_direction;
			y_velocity = 0;
		}
		x_direction = -x_direction;
		x_velocity = 0;
		x_position = others_position->x - SPRITE_WIDTH;
	}
	// Our Left overlapping their right
	else if (position.x <= others_position->x + others_position->w && position.x + position.w > others_position->x + others_position->w)
	{
		if (against_paddle)
		{
			y_direction = -y_direction;
			y_velocity = 0;
		}
		x_direction = -x_direction;
		x_velocity = 0;
		x_position = others_position->x + others_position->w;
	}
}

bool Ball::IsAlreadyDead()
{
	return already_dead;
}