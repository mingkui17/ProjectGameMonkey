#ifndef FONT_H
#define FONT_H

#include "Common.h"

using namespace std;

enum Color
{
    black,
    orange,
    yellow
};

class Font
{
private:
    string text_;
    SDL_Color color;
    TTF_Font* font = NULL;
	SDL_Texture* texture;

public:
    Font(SDL_Renderer* renderer, int size);
    ~Font();

    void SetText(string text);
    void SetColor(const int& type);
    void render(SDL_Renderer* renderer, int x, int y, int w, int h);
    SDL_Texture* loadText(SDL_Renderer* renderer);

};

#endif // FONT_H
