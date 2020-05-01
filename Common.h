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

SDL_Texture* loadTexture(SDL_Renderer* renderer, SDL_Texture* newTexture, const string& path);
Mix_Chunk* loadMusic(const string& path);
void RenderImage(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y, int w, int h);
bool CheckCollision(const SDL_Rect& fall_rand, const SDL_Rect& monkey);

#endif // COMMON_H
