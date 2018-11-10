#include <err.h>
#include "menu.h"

void print_background_menu(struct game_state *ga_st)
{
    if (ga_st == NULL)
    {
        warnx("Window not created");
        return;
    }
    SDL_Rect pos_bg;
    pos_bg.x = 0;
    pos_bg.y = 0;
    pos_bg.w = bg->w;
    pos_bg.h = bg->h;

    SDL_RenderCopy(ga_st->renderer, text, NULL, &pos_bg);
    SDL_RenderPresent(ga_st->renderer);
    SDL_Delay(1000);
    SDL_DestroyTexture(text);

    /*SDL_RenderClear(ga_st->renderer);
    SDL_RenderPresent(ga_st->renderer);
    SDL_FreeSurface(bg);*/
}

void init_sdl_tmp(struct game_state *ga_st)
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

    window = SDL_CreateWindow("Window", SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED, 600, 400, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Surface *bg = IMG_Load("ressources/background_menu_3.png");

    SDL_Texture *text = SDL_CreateTextureFromSurface(ga_st->renderer, bg);


    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    ga_st->window = window;
    ga_st->renderer = renderer;
}


void menu(struct game_state *ga_st)
{
    init_sdl_tmp(ga_st);
    SDL_Event event;
    enum selec selec = PLAY;
    int state = 1;

    while (state == 1)
    {
        manage_update(selec, ga_st, 1);
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                state = 0;
            const Uint8 *key = SDL_GetKeyboardState(NULL);

            if (key[SDL_SCANCODE_ENTER])
                manage_update(selec, ga_st, 1);

            else if (key[SDLK_SCANCODE_UP])
            {
                if (selec == 0)
                    selec = COPYRIGHT;
                else
                    selec -= 1;
                manage_update(selec, ga_st, 0);
            }

            else if (key[SDLK_SCANCODE_DOWN])
            {
                if (selec == 4)
                    selec = PLAY;
                else
                    selec += 1;
                manage_update(selec, ga_st, 0);
            }

        }
    }
}