#ifndef LEVEL_BUILDER_H
#define LEVEL_BUILDER_H
#include <array>
#include <string>
#include "Block.h"

class LevelBuilder
{
public:
	// Play_Area_Width / 16
	static const int MAX_HORIZONTAL_BLOCKS = 14;
	// (Design_Height / 2) + 8 / 8
	static const int MAX_VERTICAL_BLOCKS = 15;

	LevelBuilder();
	~LevelBuilder();

	bool Init(SDL_Renderer *renderer, std::string texture_file_location);
	void SetupLevel(std::string level_file_location);
	void Draw(SDL_Renderer *renderer);
	Block *GetBlockAt(int x, int y);

private:
	SDL_Texture *shared_texture;
	std::array<std::array<Block, MAX_HORIZONTAL_BLOCKS>, MAX_VERTICAL_BLOCKS> level;
};
#endif