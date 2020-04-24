#include <cstdlib>
#include <ctime>
#include "monkey.h"
#include "game.h"
#include "Fall.h"
#include "font.h"

using namespace std;

void RenderGameOver(SDL_Renderer* renderer, const int& score);
void RenderScore(SDL_Renderer* renderer, const int& score);
void RenderNumberFall(SDL_Renderer* renderer, const int& number_fall);
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
    Mix_HaltChannel(-1); //tắt nhạc
    Game game(renderer);
    MonkeyX monkey(renderer);

    Mix_Chunk* m_start = Mix_LoadWAV("backgr.ogg");
    Mix_Chunk* m_bk = Mix_LoadWAV("play.ogg");
    Mix_Chunk* m_eat = Mix_LoadWAV("eat.wav");
    Mix_Chunk* m_go = Mix_LoadWAV("GameOver.wav");
    if (m_start == NULL || m_eat == NULL || m_bk == NULL || m_go == NULL)
    {
        cout << "Error Music: %s \n" << Mix_GetError();
    }

    //draw background before play
    bool play = false;
    Mix_PlayChannel(-1, m_start, -1);
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
    Mix_HaltChannel(-1);

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

    Mix_PlayChannel(-1, m_bk, -1);

    //main loop
    int score = 0;
    int number_fall = max_number_fall;
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
                        Mix_PlayChannel(-1, m_eat, 0);
                        score += 3;
                        fall_rand->resetType();
                    }
                    if (list_type[i] == APPLE)
                    {
                        Mix_PlayChannel(-1, m_eat, 0);
                        score += 1;
                        fall_rand->resetType();
                    }
                    if (list_type[i] == SHIT)
                    {
                        Mix_PlayChannel(-1, m_eat, 0);
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
        RenderScore(renderer, score); //ghi điểm

        SDL_RenderPresent(renderer);

    }

    //gameover và báo điểm
    Mix_HaltChannel(-1); //tắt nhạc
    Mix_PlayChannel(-1, m_go, 0);
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
    Font overgame(renderer, 50);
    overgame.SetColor(yellow);
    overgame.SetText(score_s);
    overgame.render(renderer, 540, 300, 120, 110);
}

void RenderScore(SDL_Renderer* renderer, const int& score)
{
    Font font_score(renderer, 60);
    string score_s = to_string(score);
    font_score.SetText(score_s);
    font_score.render(renderer, 830, 57, 80, 90);
}

void RenderNumberFall(SDL_Renderer* renderer, const int& number_fall)
{
    Font font_skip(renderer, 50);
    string s = to_string(number_fall);
    string ss = "Number of skips: " + s;
    font_skip.SetText(ss);
    font_skip.render(renderer, 10, 2, 200, 40);
}

