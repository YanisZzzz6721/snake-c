#include "game.h"
#include "SDL.h"
#include <stdio.h>

int main(void) {
    Game game;
    if (game_init(&game, 30, 20, 28) != 0) {
        fprintf(stderr, "Failed to initialize game\n");
        return 1;
    }

    const int target_fps = 60;
    const int frame_delay = 1000 / target_fps;

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
        //Update des frame (a faire plutard)
        //Rendu
        game_render(&game);

        Uint32 frame_time = SDL_GetTicks() - frame_start;
        if (frame_time < frame_delay) {
            SDL_Delay(frame_delay - frame_time);
        }
    }
    game_free(&game);
    return 0;
}
