#include <cstdlib>
#include <ctime>
#include "monkey.h"
#include "game.h"
#include "Fall.h"
#include "font.h"

using namespace std;

void RenderGameOver(SDL_Renderer* renderer, int score);
void RenderScore(SDL_Renderer* renderer, int score);
void RenderTime(SDL_Renderer* renderer, Uint32 time);

int PlayAgain(SDL_Renderer* renderer, SDL_Event e);
bool CheckPlayAgain(SDL_Event e);

int main(int argc, char* argv[])
{
    //khoi dong SDL
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

    //draw background before play
    bool play = false;
    while (true)
    {
        while (SDL_PollEvent(&e)!= 0)
        {
            if (e.type == SDL_QUIT) return 0;
        }
        game.render_start(renderer);
        SDL_RenderPresent(renderer);
        int x, y;
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

    //đọc hướng dẫn cách chơi
    while (play == false)
    {
        while (SDL_PollEvent(&e)!= 0)
        {
            if (e.type == SDL_QUIT) return 0;
        }
        game.render_rules(renderer);
        SDL_RenderPresent(renderer);
        int x, y;
        SDL_GetMouseState(&x, &y);
        if (e.type == SDL_MOUSEBUTTONDOWN)
            if (e.button.button == SDL_BUTTON_LEFT)
                if (x>=780 && x<=980 && y>=565 && y<=635)
                {
                    play = true;
                }
    }

    //tạo type ngẫu nhiên
    FallRandom* falls = new FallRandom[num_type];
    int list_type[num_type];
    for (int i=0;i<num_type;i++)
    {
        FallRandom* fall_rand = (falls + i);
        if (fall_rand) //kiểm tra con trỏ có NULL hay ko
        {
            list_type[i] = fall_rand->chooseType(renderer);
            fall_rand->resetType();
        } else cout << "Fail in initialize fall_rand \n";
    }

    //main loop
    int score = 0;
    while (play)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT) return 0;
            monkey.HandleInputAction(e);
        }
        game.render_bgg(renderer);
        monkey.handleMove();
        monkey.render(renderer);

        for (int i=0;i<num_type;i++)
        {
            FallRandom* fall_rand = (falls + i);
            if (fall_rand)
            {
                fall_rand->render(renderer);
                fall_rand->HandleMove();

                bool check_col = CheckCollision(fall_rand->Type_Rect(), monkey.Monkey_Rect());
                if (check_col)
                {
                    if (list_type[i] == BANANA)
                     {
                         score += 10;
                         fall_rand->resetType();
                     }
                    if (list_type[i] == BOOM) play = false;
                }
            } else cout << "Fail in initialize fall_rand in main loop\n";
        }

        //hiện time

        Uint32 time = 180 - SDL_GetTicks()/1000;
        if (time == 0) play = false;
        RenderTime(renderer, time);

        RenderScore(renderer, score); //ghi điểm

        SDL_RenderPresent(renderer);
    }

    //gameover và báo điểm
    game.render_gameover(renderer);
    RenderGameOver(renderer, score);

    SDL_RenderPresent(renderer);

    delete [] falls;
    return 1;
}

bool CheckPlayAgain(SDL_Event e)
{
    while (true)
    {
        while (SDL_PollEvent(&e)!= 0)
        {
            if (e.type == SDL_QUIT) return false;
        }
        if (e.type == SDL_MOUSEBUTTONDOWN)
            if (e.button.button == SDL_BUTTON_RIGHT)
                return true;
    }
}

void RenderGameOver(SDL_Renderer* renderer, int score)
{
    string score_s = to_string(score);
    string score_ss = "Your Score: " + score_s;
    Font overgame(renderer, 50);
    overgame.SetColor(yellow);
    overgame.SetText(score_ss);
    overgame.render(renderer, 400, 400, 400, 90);
}

void RenderScore(SDL_Renderer* renderer, int score)
{
    Font font_score(renderer, 60);
    string score_s = to_string(score);
    font_score.SetText(score_s);
    font_score.render(renderer, 830, 57, 80, 90);
}

void RenderTime(SDL_Renderer* renderer, Uint32 time)
{
    Font font_time(renderer, 50);
    string time_s = to_string(time);
    string time_ss = "Time: " + time_s;
    font_time.SetText(time_ss);
    font_time.render(renderer, 10, 2, 120, 40);
}

