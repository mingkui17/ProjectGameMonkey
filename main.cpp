#include <cstdlib>
#include <ctime>

#include "monkey.h"
#include "game.h"
#include "Fall.h"
#include "font.h"

using namespace std;

int main(int argc, char* argv[])
{
    //khoi dong SDL
    srand(time(0));
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event e;
    initSDL(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);

    Game game(renderer);
    MonkeyX monkey(renderer);
    Font font_score(renderer, 20);
    Font font_time(renderer, 20);
    int score = 0;

    //draw background before play
    bool play = false;
    while (true)
    {
        while (SDL_PollEvent(&e)!= 0)
        {
            if (e.type == SDL_QUIT) return 0;
        }
        int x, y;
        SDL_GetMouseState(&x, &y);
        if (e.type == SDL_MOUSEBUTTONDOWN)
            if (e.button.button == SDL_BUTTON_LEFT)
        {
            if (x>=10 && x<=210 && y>=550 && y<=620)
            {
                play = true;
                break;
            }
            if (x>=245 && x<=445 && y>=550 && y<=620)
                break;
        }
        game.render_start(renderer);
        SDL_RenderPresent(renderer);
    }
    if (play == false) return 0;

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

        string time_s = to_string(time);
        string time_ss = "Time: " + time_s;
        font_time.SetText(time_ss);
        font_time.render(renderer, 5, 0, 80, 30);

        //ghi điểm
        string score_s = to_string(score);
        string score_ss = "Score: " + score_s;
        font_score.SetText(score_ss);
        font_score.render(renderer, 450, 0, 90, 30);

        SDL_RenderPresent(renderer);
    }

    //gameover và báo điểm
    game.render_gameover(renderer);

    string score_s = to_string(score);
    string score_ss = "Your Score: " + score_s;

    Font overgame(renderer, 50);
    overgame.SetColor(yellow);
    overgame.SetText(score_ss);
    overgame.render(renderer, 400, 400, 400, 90);

    SDL_RenderPresent(renderer);


    waitUntilKeyPressed();

    delete [] falls;
    quitSDL(window, renderer);
    return 0;
}

