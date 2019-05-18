#include "LevelBuilder.h"
#include "Block.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <fstream>

LevelBuilder::LevelBuilder()
{
	shared_texture = nullptr;
}

LevelBuilder::~LevelBuilder()
{
	SDL_DestroyTexture(shared_texture);
}

bool LevelBuilder::Init(SDL_Renderer *renderer, std::string texture_file_location)
{
	bool status = true;

	SDL_Surface *surface_for_texture = IMG_Load(texture_file_location.c_str());
	if (!surface_for_texture)
	{
		std::cout << texture_file_location + " could not be found!\n";
		status = false;
	}
	else
	{
		shared_texture = SDL_CreateTextureFromSurface(renderer, surface_for_texture);
		if (!shared_texture)
		{
			std::cout << texture_file_location + " could not be turned into a texture!\nIMG Error: " + IMG_GetError() + "\n";
			status = false;
		}
		else
		{
			for (auto &arr : level)
			{
				for (auto &block : arr)
				{
					block.GetSprite()->SetTexture(shared_texture);
				}
			}
		}
	}

	return status;
}

void LevelBuilder::SetupLevel(std::string level_file_location)
{
	std::ifstream file;
	int i = 0, j = 0;
	char place;
	file.open(level_file_location);
	// Read through the file for 1s and 0s
	while(!file.eof())
	{
		file >> place;
		// Skip any 0s
		if (place == '0')
		{
			i++;
		}
		if (place == '1') //but place a block if there's a 1
		{
			level[j][i].SetPosition(i * 16, j * 8);
			level[j][i].SetAlive(true);
			i++;
		}
		
		if (i == MAX_HORIZONTAL_BLOCKS)
		{
			j++;
			i = 0;
		}
	}

	file.close();
}

void LevelBuilder::Draw(SDL_Renderer *renderer)
{
	for (auto &arr : level)
	{
		for (auto &block : arr)
		{
			block.Draw(renderer);
		}
	}
}

Block *LevelBuilder::GetBlockAt(int x, int y)
{
	return &level[x][y];
}

bool LevelBuilder::AnyBlocksLeft()
{
	for (auto &arr : level)
	{
		for (auto &block : arr)
		{
			if (block.GetAlive())
				return true;
		}
	}

	return false;
}