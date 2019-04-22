#ifndef GUI_H
#define GUI_H
#include <SDL_ttf.h>
#include "Text.h"
#include "Sprite.h"
#include <string>

class GUI
{
public:
	bool InitFont(SDL_Renderer *renderer, std::string file_location);
	bool InitStartLogo(SDL_Renderer *renderer, std::string file_location);
	void Update(SDL_Renderer *renderer, int top, int score, int stage, int balls);
	void DrawStart(SDL_Renderer *renderer);
	void DrawGameplay(SDL_Renderer *renderer);
	void DrawGameOver(SDL_Renderer *renderer);
	void Quit();

private:
	const int COLUMN_CENTER = 255;
	const int ROW_START = 25;
	const int ROW_OFFSET = 50;
	const int TEXT_POINT_SIZE = 14;
	const int TEXT_WIDTH = 45;
	const int TEXT_HEIGHT = 15;

	const int LOGO_WIDTH = 148;
	const int LOGO_HEIGHT = 93;
	const SDL_Rect START_LOGO_POSITION{ 90, 40, LOGO_WIDTH, LOGO_HEIGHT };

	const std::string TOP_SCORE_LABEL = "TOP\n";
	const std::string SCORE_LABEL = "SCORE\n";
	const std::string STAGE_LABEL = "STAGE\n";
	const std::string BALLS_LABEL = "x ";

	// Yay, no need for a default constructor!
	int top_score_prev = 0;
	int score_prev = 0;
	int stage_prev = 1;
	int balls_prev = 3;

	Sprite start_screen_logo{ 0, 0, LOGO_WIDTH, LOGO_HEIGHT };

	TTF_Font *gui_font;
	Text top_score_text{ TOP_SCORE_LABEL + std::to_string(top_score_prev), COLUMN_CENTER, ROW_START, TEXT_WIDTH, TEXT_HEIGHT};
	Text score_text{ SCORE_LABEL + std::to_string(score_prev), COLUMN_CENTER, ROW_START + ROW_OFFSET, TEXT_WIDTH, TEXT_HEIGHT };
	Text stage_text{ STAGE_LABEL + std::to_string(stage_prev), COLUMN_CENTER, ROW_START + ROW_OFFSET * 2, TEXT_WIDTH, TEXT_HEIGHT };
	Text balls_text{ BALLS_LABEL + std::to_string(balls_prev), COLUMN_CENTER, ROW_START + ROW_OFFSET * 3, TEXT_WIDTH/2, TEXT_HEIGHT };
};
#endif
