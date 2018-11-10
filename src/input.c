#include "input.h"

int input_update(struct game_state *ga_st)
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
            return 1;
        if (event.type == SDL_KEYDOWN)
            if (event.key.keysym.scancode == SDL_SCANCODE_SPACE)
                player_jump(ga_st);
    }

    const Uint8 *key = SDL_GetKeyboardState(NULL);

    if (key[SDL_SCANCODE_D] || key[SDL_SCANCODE_RIGHT])
        player_run(ga_st, 1);
    else if (key[SDL_SCANCODE_A] || key[SDL_SCANCODE_LEFT])
        player_run(ga_st, -1);
    else
        player_run(ga_st, 0);
    return 0;
}
