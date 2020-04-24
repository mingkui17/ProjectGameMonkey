#ifndef COMMON_H
#define COMMON_H

#include "SDL_utils.h"

using namespace std;

const int num_type = 20;
const int max_number_fall = 100;

//Fall.h
const int speed = 5;
const int width_type = 61;
const int height_type = 61;

//monkey.h
const int width_monkey = 133;
const int height_monkey = 151;
const int step = 5;

SDL_Texture* loadTexture(SDL_Renderer* renderer, SDL_Texture* newTexture, string path);
void RenderImage(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y, int w, int h);
bool CheckCollision(const SDL_Rect& fall_rand, const SDL_Rect& monkey);

enum Color
{
    black,
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

    void SetText(const string& text);
    void SetColor(const int& type);
    void render(SDL_Renderer* renderer, int x, int y, int w, int h);
    SDL_Texture* loadText(SDL_Renderer* renderer);
};

#endif // COMMON_H
