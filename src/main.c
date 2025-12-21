#include "game.h"
#include "SDL.h"
#include "snake.h"
#include <stdio.h>

int main(void) {
    Game game;
    if (game_init(&game, 30, 20, 28) != 0) {
        fprintf(stderr, "Failed to initialize game\n");
        return 1;
    }
    Snake snake;
    if (snake_init(&snake, 10, 10, 5) != 0) {
        fprintf(stderr, "Failed to init snake\n");
        game_free(&game);
        return 1;
    }


    const int target_fps = 60;
    const int frame_delay = 1000 / target_fps;

    Uint32 last_move = SDL_GetTicks();
    Uint32 move_delay = 150; // ms (plus petit = plus rapide)
    //Boucle de jeu
    while (game.running) {
        Uint32 frame_start = SDL_GetTicks();
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                game.running = false;
            }
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    game.running = false;
                }
            }
        }
        Uint32 now = SDL_GetTicks();
        if (now - last_move >= move_delay) {
        last_move = now;
        //calculer new_x, new_y à partir de la direction
        //  push_front(new_x,new_y)
        //pop_back() (si pas de nourriture)
}

        game_build_grid(&game, &snake);
        game_render(&game);


        Uint32 frame_time = SDL_GetTicks() - frame_start;
        if (frame_time < frame_delay) {
            SDL_Delay(frame_delay - frame_time);
        }
    }
    snake_free(&snake);
    game_free(&game);
    return 0;
}
