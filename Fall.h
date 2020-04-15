#ifndef FALL_H
#define FALL_H

#include "Common.h"

using namespace std;

const int width_type = 61;
const int height_type = 61;

enum
{
    BANANA,
    BOOM,
    TYPE
};

class FallRandom
{
private:
    SDL_Texture* type_image;
    int x, y, w, h;
    int y_;
    int type;

public:
    FallRandom();
    ~FallRandom();

    void HandleMove();
    void render(SDL_Renderer* renderer);
    void resetType();
    int chooseType(SDL_Renderer* renderer);
    int getType() { return type; }

    SDL_Rect Type_Rect();
};
#endif // FALL_H
