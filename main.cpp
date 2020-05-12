#include <cstdlib>
#include <ctime>
#include "monkey.h"
#include "game.h"
#include "Fall.h"

using namespace std;

void RenderGameOver(SDL_Renderer* renderer, const int& score);
void RenderScore(SDL_Renderer* renderer, const int& score);
void RenderNumberFall(SDL_Renderer* renderer, const int& number_fall);
int PlayAgain(SDL_Renderer* renderer, SDL_Event e);
bool CheckPlayAgain(SDL_Event e);

int main(int argc, char* argv[])
{
    srand(time(0));
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event e;
    initSDL(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);

    bool CheckP;
    do
    {
        if (PlayAgain(renderer, e) == 0)
        {
            quitSDL(window, renderer);
            return 0;
        }
        CheckP = CheckPlayAgain(e);
    } while (CheckP);

    quitSDL(window, renderer);
    return 0;
}

int PlayAgain(SDL_Renderer* renderer, SDL_Event e)
{
    Game game(renderer);
    MonkeyX monkey(renderer);
    Music music;

    int x, y, speed;
    bool play = false;

    music.PlayStart();
    while (true)
    {
        while (SDL_PollEvent(&e)!= 0)
        {
            if (e.type == SDL_QUIT) return 0;
        }
        game.render_start(renderer);
        SDL_RenderPresent(renderer);
        SDL_GetMouseState(&x, &y);
        if (e.type == SDL_MOUSEBUTTONDOWN)
        {
            if (e.button.button == SDL_BUTTON_LEFT)
            {
                if (x>=930 && x<=990 && y>=10 && y<=70)
                {
                    break;
                }
                if (x>=780 && x<=980 && y>=565 && y<=635)
                {
                    play = true;
                    break;
                }
            }
        }
    }

    while (play == false)
    {
        while (SDL_PollEvent(&e)!= 0)
        {
            if (e.type == SDL_QUIT) return 0;
        }
        game.render_rules(renderer);
        SDL_RenderPresent(renderer);
        SDL_GetMouseState(&x, &y);
        if (e.type == SDL_MOUSEBUTTONDOWN)
            if (e.button.button == SDL_BUTTON_LEFT)
                if (x>=780 && x<=980 && y>=565 && y<=635)
                {
                    play = true;
                }
    }

    while (true)
    {
        while (SDL_PollEvent(&e)!= 0)
        {
            if (e.type == SDL_QUIT) return 0;
        }
        game.render_level(renderer);
        SDL_RenderPresent(renderer);
        SDL_GetMouseState(&x, &y);
        if (e.type == SDL_MOUSEBUTTONDOWN)
        {
            if (e.button.button == SDL_BUTTON_LEFT)
            {
                if (x>=185 && x<=368 && y>=298 && y<=389)
                {
                    speed = 5;
                    break;
                }
                if (x>=415 && x<=598 && y>=298 && y<=389)
                {
                    speed = 10;
                    break;
                }
                if (x>=640 && x<= 823 && y>=298 && y<=389)
                {
                    speed = 13;
                    break;
                }
            }
        }
    }

    Mix_HaltChannel(-1);

    FallRandom* falls = new FallRandom[num_type];
    int list_type[num_type];
    for (int i=0;i<num_type;i++)
    {
        FallRandom* fall_rand = (falls + i); //tham khảo ở phattrienphanmem123az.com
        if (fall_rand)
        {
            list_type[i] = fall_rand->chooseType(renderer);
            fall_rand->resetType();
        } else cout << "Fail in initialize fall_rand \n";
    }

    music.PlayGame();

    //main loop
    int score = 0;
    int number_fall = max_number_fall;
    while (play)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                delete falls;
                return 0;
            }
        }
        game.render_bgg(renderer);
        monkey.HandleInputAction(e);
        monkey.render(renderer);

        for (int i=0;i<num_type;i++)
        {
            FallRandom* fall_rand = (falls + i); //tham khảo ở phattrienphanmem123az.com
            if (fall_rand)
            {
                fall_rand->render(renderer);
                fall_rand->HandleMove(speed);

                bool check_col = CheckCollision(fall_rand->Type_Rect(), monkey.Monkey_Rect());
                if (check_col)
                {
                    music.PlayEat();
                    if (list_type[i] == BANANA)
                    {
                        score += 3;
                        fall_rand->resetType();
                    }
                    if (list_type[i] == APPLE)
                    {
                        score += 1;
                        fall_rand->resetType();
                    }
                    if (list_type[i] == SHIT)
                    {
                        if (score >= 2) score -= 2;
                            else score = 0;
                        fall_rand->resetType();
                    }
                    if (list_type[i] == BOOM)
                    {
                        play = false;
                    }
                } else
                    {
                        if (list_type[i] == BANANA || list_type[i] == APPLE)
                            if (fall_rand->getY() > SCREEN_HEIGHT - 5)
                            {
                                number_fall--;
                            }
                        if (number_fall == 0) play = false;
                    }
            } else cout << "Fail in initialize fall_rand in main loop\n";
        }
        RenderNumberFall(renderer, number_fall);
        RenderScore(renderer, score);

        SDL_RenderPresent(renderer);
    }
    Mix_HaltChannel(-1);
    music.PlayGameOver();
    game.render_gameover(renderer);
    RenderGameOver(renderer, score);

    SDL_RenderPresent(renderer);
    SDL_Delay(2500);

    delete [] falls;
    return 1;
}

bool CheckPlayAgain(SDL_Event e)
{
    while (true)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT) return false;
        }
        int x, y;
        SDL_GetMouseState(&x, &y);
        if (e.type == SDL_MOUSEBUTTONDOWN)
            if (e.button.button == SDL_BUTTON_LEFT)
                if (x>=780 && x<=980 && y>=565 && y<=625)
                {
                    return true;
                }
    }
}

void RenderGameOver(SDL_Renderer* renderer, const int& score)
{
    string score_s = to_string(score);
    Font overgame(50);
    overgame.SetColor(yellow);
    overgame.SetText(score_s);
    overgame.render(renderer, 540, 300, 120, 110);
}

void RenderScore(SDL_Renderer* renderer, const int& score)
{
    Font font_score(60);
    string score_s = to_string(score);
    font_score.SetText(score_s);
    font_score.render(renderer, 830, 57, 80, 90);
}

void RenderNumberFall(SDL_Renderer* renderer, const int& number_fall)
{
    Font font_skip(50);
    string s = to_string(number_fall);
    string ss = "Number of skips: " + s;
    font_skip.SetText(ss);
    font_skip.render(renderer, 10, 2, 200, 40);
}

