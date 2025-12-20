#include "grid.h"
#include <stdlib.h>
#include <stdio.h>

int grid_init(Grid *g, int width,int height){
    if (!g || width <= 0 || height <= 0){
        fprintf(stderr,"Erreur");
        return -1;
    }
    g->height = height;
    g->width = width;
    g->cells = (Tile*)malloc((size_t)width * (size_t)height * sizeof(Tile));
    if (!g->cells){
        fprintf(stderr,"Erreur malloc");
        return -1;
    }
    grid_clear(g, TILE_EMPTY);
    return 0;
}

void grid_free(Grid *g){
    if (!g){
        fprintf(stderr,"Erreur d'allocation méméoire");
        return;
    }
    free(g->cells);
    g->cells = NULL;
    g->width = 0;
    g->height = 0;
}

void grid_clear(Grid *g, Tile t){
    if(!g || !g->cells){
        fprintf(stderr, "Erreur grille vide");
        return;
    }
    for (int i = 0; i < g->height; i++){
        for (int j = 0; j < g->width; j++){
            grid_set(g,j,i,t);
        }
    }
    return;
}