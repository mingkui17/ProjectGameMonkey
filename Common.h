#ifndef COMMON_H
#define COMMON_H

#include "SDL_utils.h"

using namespace std;

SDL_Texture* loadTexture(SDL_Renderer* renderer, SDL_Texture* newTexture, string path);

void RenderImage(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y, int w, int h);
bool CheckCollision(SDL_Rect fall_rand, SDL_Rect monkey);

#endif // COMMON_H
