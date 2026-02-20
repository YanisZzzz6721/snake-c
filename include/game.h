#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include "SDL.h"
#include "snake.h"
#include "grid.h"

typedef struct Game{
    SDL_Window *win;
    SDL_Renderer *ren;

    int cell_px;
    int margin_px;

    Grid grid;
    bool running;

}Game;

int game_init(Game *g,int grid_w, int grid_h, int cell_px);
//Instanciation de la grille et des cellules

void game_free(Game *g);

void game_render(Game *g);

void game_build_grid(Game *g, const Snake *s);


#endif


