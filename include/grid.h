#ifndef GRID_H
#define GRID_H

#include <stdint.h>

typedef enum{
    TILE_EMPTY = 0,
    TILE_WALL = 1,
    TILE_SNAKE = 2,
    TILE_FOOD = 3,
} Tile;

typedef struct Grid{
    int width;
    int height;
    Tile *cells;
}Grid;

int grid_init(Grid *g, int width, int height);

void grid_free(Grid *g);

void grid_clear(Grid *g, Tile t);

static inline Tile grid_get(const Grid *g, int x, int y){
    return g->cells[y * g->width + x];
}

static inline void grid_set(Grid *g, int x, int y, Tile t){
    g->cells[y * g->width + x] = t;
}

#endif