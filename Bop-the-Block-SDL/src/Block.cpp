#include "Block.h"

Block::Block(int x, int y)
{
	position = start_position = { x, y, SPRITE_WIDTH, SPRITE_HEIGHT };
	sprite.SetDrawingArea(0, 0, SPRITE_WIDTH, SPRITE_HEIGHT);
	alive = true;
}

int Block::GetPointValue()
{
	return point_value;
}

void Block::SetPointValue(int value)
{
	point_value = value;
}

void Block::HandleCollision()
{
	if (alive)
		alive = !alive;
	SetPosition(-SPRITE_WIDTH, -SPRITE_WIDTH); // Set collision rect off screen
}

void Block::Update() {}

void Block::Draw(SDL_Renderer *renderer)
{
	if (alive)
		SDL_RenderCopy(renderer, sprite.GetTexture(), &sprite.GetDrawingArea(), &position);
}

void Block::Reset()
{
	alive = true;
}