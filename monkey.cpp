#include "monkey.h"

MonkeyX::MonkeyX (SDL_Renderer* renderer)
{
    this -> monkey_ = loadTexture(renderer, monkey_, "monkey1.bmp");
    this -> x = (SCREEN_WIDTH - width_monkey)/2;
    this -> y = SCREEN_HEIGHT - height_monkey - 3 ;
    this -> w = width_monkey;
    this -> h = height_monkey;
    x_ = 0;
}

MonkeyX::~MonkeyX()
{
    SDL_DestroyTexture(monkey_);
}

void MonkeyX::HandleInputAction(SDL_Event &e)
{
    if (e.type == SDL_KEYDOWN)
    {
        switch (e.key.keysym.sym)
        {
            case SDLK_RIGHT: x_ += step;
                break;
            case SDLK_LEFT: x_ -= step;
                break;
        }
    }
    else if (e.type == SDL_KEYUP)
        {
            switch (e.key.keysym.sym)
            {
                case SDLK_RIGHT:
                {
                    x_ -= step;
                    break;
                }
                case SDLK_LEFT: x_ += step;
                    break;
            }
        }
    else
    {
        int x_mouse, y_mouse;
        SDL_GetMouseState(&x_mouse, &y_mouse);
        if (x_mouse < width_monkey/2) x = 0; //điều khiển chuột ở giữa ảnh khỉ
            else if (x_mouse > (SCREEN_WIDTH - width_monkey/2)) x = SCREEN_WIDTH - width_monkey;
                else x = x_mouse - width_monkey/2;
    }
}

void MonkeyX::handleMove()
{
    x += x_;
    if (x < 0 || x + width_monkey > SCREEN_WIDTH) x -= x_; //tránh ảnh khỉ bị thò ra khỏi biên
}

void MonkeyX::render(SDL_Renderer* renderer)
{
    RenderImage(renderer, monkey_, x, y, w, h);
}



