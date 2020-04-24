#include "Fall.h"

using namespace std;

FallRandom::FallRandom()
{
    this -> x = rand() % (SCREEN_WIDTH-width_type);
    this -> y = 0;
    this -> w = width_type;
    this -> h = height_type;
    y_ = speed;
}

int FallRandom::chooseType(SDL_Renderer* renderer)
{
    int type = rand() % TYPE;
    if (type == BANANA)
    {
        this -> type_image = loadTexture(renderer, type_image, "banana.bmp");
    }
    if (type == APPLE)
    {
        this -> type_image = loadTexture(renderer, type_image, "apple.png");
    }
    if (type == SHIT)
    {
        this -> type_image = loadTexture(renderer, type_image, "shit.png");
    }
    if (type == BOOM)
    {
        this -> type_image = loadTexture(renderer, type_image, "boom1.bmp");
    }
    return type;
}

FallRandom::~FallRandom()
{
    SDL_DestroyTexture(type_image);
}

void FallRandom::HandleMove()
{
    y += y_;
    if (y > SCREEN_HEIGHT)
    {
        resetType();
    }
}

void FallRandom::render(SDL_Renderer* renderer)
{
    RenderImage(renderer, type_image, x, y, w, h);
}

SDL_Rect FallRandom::Type_Rect()
{
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    return rect;
}

void FallRandom::resetType()
{
    y = -(rand() % 500);
    x = rand() % (SCREEN_WIDTH-width_type);
}
