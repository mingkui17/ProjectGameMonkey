#ifndef GAME_H
#define GAME_H

#include "Common.h"

class Game
{
private:
    SDL_Texture* background;
    SDL_Texture* start;
    SDL_Texture* question;
    SDL_Texture* rules;
    SDL_Texture* background2;
    SDL_Texture* gameover;
    SDL_Texture* replay;
public:
    Game(SDL_Renderer* renderer)
    {
        this -> background = loadTexture(renderer, background, "background.png");
        this -> start = loadTexture(renderer, start, "start.png");
        this -> question = loadTexture(renderer, question, "question1.png");
        this -> rules = loadTexture(renderer, rules, "rules.png");
        this -> background2 = loadTexture(renderer, background2, "background2.1.bmp");
        this -> gameover = loadTexture(renderer, background2, "gameover1.bmp");
        this -> replay = loadTexture(renderer, replay, "replay.png");
    }
    void render_start(SDL_Renderer* renderer)
    {
        SDL_RenderCopy(renderer, background, NULL, NULL);
        RenderImage(renderer, start, 780, 565, 200, 70);
        RenderImage(renderer, question, 930, 10, 60, 60);
    }
    void render_rules(SDL_Renderer* renderer)
    {
        SDL_RenderCopy(renderer, rules, NULL, NULL);
        RenderImage(renderer, start, 780, 565, 200, 70);
    }
    void render_bgg(SDL_Renderer* renderer)
    {
        RenderImage(renderer, background2, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    }
    void render_gameover(SDL_Renderer* renderer)
    {
        RenderImage(renderer, gameover, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        RenderImage(renderer, replay, 780, 565, 200, 60);
    }
    ~Game()
    {
        SDL_DestroyTexture(background);
        SDL_DestroyTexture(start);
        SDL_DestroyTexture(question);
        SDL_DestroyTexture(rules);
        SDL_DestroyTexture(background2);
        SDL_DestroyTexture(gameover);
        SDL_DestroyTexture(replay);
    }
};

#endif // GMAE_H
