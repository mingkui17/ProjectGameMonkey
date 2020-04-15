#include "font.h"

Font::Font(SDL_Renderer* renderer, int size)
{
    color = {0, 0, 0}; //black color
    font = TTF_OpenFont("Sofia-Regular.otf", size);
}

Font::~Font()
{
    if(font)
    {
		TTF_CloseFont(font);
		font = NULL;
	}
    SDL_DestroyTexture(texture);
}

void Font::SetText(string text)
{
    text_ = text;
}

void Font::SetColor(const int& type)
{
    if (type == black) color = {0, 0, 0};
    if (type == orange) color = {255, 165, 0};
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
    this -> texture = loadText(renderer);
    RenderImage(renderer, texture, x, y, w, h);
}
