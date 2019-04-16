#ifndef TEXT_H
#define TEXT_H
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class Text
{
public:
	Text(std::string text, int x, int y, int w, int h);
	bool Setup(SDL_Renderer *renderer, TTF_Font *font);
	void Change_Text(SDL_Renderer *renderer, TTF_Font *font, std::string new_text);
	void Draw(SDL_Renderer *renderer);
	void Quit();

private:
	bool ChangeTextTexture(SDL_Renderer *renderer, TTF_Font *font);
	std::string text;
	SDL_Rect text_position;
	SDL_Color text_color;
	SDL_Texture *texture;
};
#endif
