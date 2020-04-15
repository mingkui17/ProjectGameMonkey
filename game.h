#ifndef GAME_H
#define GAME_H

#include "Common.h"
#include "font.h"

class Game
{
private:
    SDL_Texture* background;
    SDL_Texture* start;
    SDL_Texture* exit;
    SDL_Texture* background2;
    SDL_Texture* gameover;
public:
    Game(SDL_Renderer* renderer)
    {
        this -> background = loadTexture(renderer, background, "background.bmp");
        this -> start = loadTexture(renderer, start, "start.png");
        this -> exit = loadTexture(renderer, exit, "exit.bmp");
        this -> background2 = loadTexture(renderer, background2, "background2.bmp");
        this -> gameover = loadTexture(renderer, background2, "gameover.bmp");
    }
    void render_start(SDL_Renderer* renderer)
    {
        SDL_RenderCopy(renderer, background, NULL, NULL);
        RenderImage(renderer, start, 10, 550, 200, 70);
    }
    void render_bgg(SDL_Renderer* renderer)
    {
        RenderImage(renderer, background2, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        SDL_Rect filledRect;
        filledRect.x = 0;
        filledRect.y = 0;
        filledRect.h = 30;
        filledRect.w = SCREEN_WIDTH;
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
        SDL_RenderFillRect(renderer, &filledRect);
    }
    void render_gameover(SDL_Renderer* renderer)
    {
        RenderImage(renderer, gameover, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    }
    ~Game()
    {
        SDL_DestroyTexture(background);
        SDL_DestroyTexture(start);
        SDL_DestroyTexture(exit);
        SDL_DestroyTexture(background2);
        SDL_DestroyTexture(gameover);
    }
};

#endif // GMAE_H
