#ifndef SPRITE_H
#define SPRITE_H
#include <SDL.h>
#include <string>

class Sprite
{
public:
	Sprite(int x, int y, int w, int h);
	~Sprite();
	bool Init(SDL_Renderer *renderer, std::string file_location);
	SDL_Texture *GetTexture();
	SDL_Rect GetDrawingArea();

private:
	SDL_Texture *texture;
	SDL_Rect draw_area;
};
#endif