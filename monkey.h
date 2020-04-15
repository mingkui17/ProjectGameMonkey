#ifndef MONKEY_H
#define MONKEY_H

#include "Common.h"

const int width_monkey = 133;
const int height_monkey = 151;

class MonkeyX
{
private:
    SDL_Texture* monkey_;
    int x, y, w, h;
    int x_;
    int step = 5;
public:
    MonkeyX(SDL_Renderer* renderer);
    ~MonkeyX();

    void HandleInputAction(SDL_Event &e);
    void handleMove();
    void render(SDL_Renderer* renderer);

    SDL_Rect Monkey_Rect()
    {
        SDL_Rect rect;
        rect.x = x;
        rect.y = y;
        rect.w = w;
        rect.h = h;
        return rect;
    }

    int getX() { return x; }
    int getY() { return y; }
    int getW() { return w; }
    int getH() { return h; }
};

#endif // MONKEY_H
