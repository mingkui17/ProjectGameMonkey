#include "Common.h"

using namespace std;

SDL_Texture* loadTexture(SDL_Renderer* renderer, SDL_Texture* newTexture, string path)
{
    SDL_Surface* loadedSurface =  IMG_Load(path.c_str());
    if(loadedSurface == NULL)
    {
        cout << "Unable to load image " << path << " SDL_image Error: " << IMG_GetError() << endl;
    }
    else
    {
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface -> format, 0, 255, 255));
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if(newTexture == NULL)
        {
            cout << "Unable to create texture from " << path << " SDL Error: " << SDL_GetError() << endl;
        }
        SDL_FreeSurface( loadedSurface );
    }
    return newTexture;
}

void RenderImage(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y, int w, int h)
{
    SDL_Rect Rect;
    Rect.x = x;
    Rect.y = y;
    Rect.w = w;
    Rect.h = h;
    SDL_RenderCopy(renderer, texture, NULL, &Rect);
}

bool CheckCollision(const SDL_Rect& fall_rand, const SDL_Rect& monkey)
{
    int left_a = fall_rand.x;
    int right_a = fall_rand.x + fall_rand.w;
    int top_a = fall_rand.y;
    int bottom_a = fall_rand.y + fall_rand.h;

    int left_b = monkey.x;
    int right_b = monkey.x + monkey.w;
    int top_b = monkey.y;
    int bottom_b = monkey.y + monkey.h;

    //chỉ đúng khi size fall_rand < monkey
    if (left_a > left_b && left_a < right_b)
    {
        if (top_a > top_b && top_a < bottom_b)
        {
            return true;
        }
    }
    if (left_a > left_b && left_a < right_b)
    {
        if (bottom_a > top_b && bottom_a < bottom_b)
        {
            return true;
        }
    }
    if (right_a > left_b && right_a < right_b)
    {
        if (top_a > top_b && top_a < bottom_b)
        {
            return true;
        }
    }
    if (right_a > left_b && right_a < right_b)
    {
        if (bottom_a > top_b && bottom_a < bottom_b)
        {
            return true;
        }
    }
    return false;
}

Font::Font(SDL_Renderer* renderer, int size)
{
    color = {255, 255, 255}; //white color
    font = TTF_OpenFont("Sofia-Regular.otf", size);
}

Font::~Font()
{
    if (font)
    {
		TTF_CloseFont(font);
		font = NULL;
	}
    SDL_DestroyTexture(texture);
}

void Font::SetText(const string& text)
{
    text_ = text;
}

void Font::SetColor(const int& type)
{
    if (type == black) color = {0, 0, 0};
    if (type == yellow) color = {255, 255, 0};
}

SDL_Texture* Font::loadText(SDL_Renderer* renderer)
{
    SDL_Surface* surface = NULL;
	surface = TTF_RenderText_Solid(font, text_.c_str(), color);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (texture == NULL)
        cout << "Unable to create texture from " << text_ << "\nSDL Error: " << SDL_GetError() << endl;
	SDL_FreeSurface(surface);
	return texture;
}

void Font::render(SDL_Renderer* renderer, int x, int y, int w, int h)
{
    texture = loadText(renderer);
    RenderImage(renderer, texture, x, y, w, h);
}

