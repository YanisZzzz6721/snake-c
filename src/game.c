#include "game.h"
#include "snake.h"
#include <stdio.h>
#include <stdlib.h>

int game_init(Game *g, int grid_w,int grid_h, int cell_px){
    if (!g || grid_w <= 0 || grid_h <= 0 || cell_px <= 0){
        fprintf(stderr,"Erreur");
        return -1;
    }
    g->running = true;
    g->cell_px = cell_px;
    g->margin_px = 20;
    g->win = NULL;
    g->ren = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) != 0){
        fprintf(stderr,"Erreur SDL: %s",SDL_GetError());
        return 1;
    }

    int width = 2 * g->margin_px + grid_w * g->cell_px;
    int height = 2* g->margin_px + grid_h * g->cell_px;


    g->win = SDL_CreateWindow(
        "Snake",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width, height,
        SDL_WINDOW_SHOWN
    );
    if(!g->win){
        fprintf(stderr,"Erreur SDL: %s",SDL_GetError());
        SDL_Quit();
        return 2;
    }


    g->ren = SDL_CreateRenderer(g->win, -1, SDL_RENDERER_ACCELERATED);
    if (!g->ren) {
        fprintf(stderr, "SDL_CreateeRendererer failed: %s\n", SDL_GetError());
        SDL_DestroyWindow(g->win);
        g->win = NULL;
        SDL_Quit();
        return 3;
    }


    if (grid_init(&g->grid, grid_w,grid_h) != 0){
        fprintf(stderr,"grid_failed");
        SDL_DestroyRenderer(g->ren);
        SDL_DestroyWindow(g->win);
        g->ren = NULL;
        g->win = NULL;
        SDL_Quit();
        return 4;
    }
    return 0;

}

void game_free(Game *g){
    if(!g) return;
    grid_free(&g->grid);
    if(g->ren) SDL_DestroyRenderer(g->ren);
    if(g->win) SDL_DestroyWindow(g->win);
    g->ren = NULL;
    g->win = NULL;
    SDL_Quit();
}

static void grid_set_wall(Grid *grid){
    int w = grid->width;
    int h = grid->height;
    for (int x = 0; x < w; x++){
        grid_set(grid,x,0,TILE_WALL);
        grid_set(grid,x, h - 1, TILE_WALL);
    }
    for (int y = 0; y < grid->height; y++){
        grid_set(grid,0,y,TILE_WALL);
        grid_set(grid,w-1,y,TILE_WALL);
    }
}

void game_build_grid(Game *g, const Snake *s){
    grid_clear(&g->grid, TILE_EMPTY);
    grid_set_wall(&g->grid);
    snake_write_to_grid(s, &g->grid);
}

void game_render(Game *g) {
    SDL_SetRenderDrawColor(g->ren, 15, 15, 20, 255);
    SDL_RenderClear(g->ren);

    for (int y = 0; y < g->grid.height; y++) {
        for (int x = 0; x < g->grid.width; x++) {

            Tile t = grid_get(&g->grid, x, y);

            int px = g->margin_px + x * g->cell_px;
            int py = g->margin_px + y * g->cell_px;

            SDL_Rect rect = {
                px,
                py,
                g->cell_px,
                g->cell_px
            };

            switch (t) {
                case TILE_EMPTY:
                    SDL_SetRenderDrawColor(g->ren, 30, 30, 40, 255);
                    break;
                case TILE_WALL:
                    SDL_SetRenderDrawColor(g->ren, 120, 120, 140, 255);
                    break;
                case TILE_SNAKE:
                    SDL_SetRenderDrawColor(g->ren, 80, 200, 120, 255);
                    break;
                case TILE_FOOD:
                    SDL_SetRenderDrawColor(g->ren, 220, 80, 80, 255);
                    break;
            }

            SDL_RenderFillRect(g->ren, &rect);
        }
    }

    SDL_RenderPresent(g->ren);
}
