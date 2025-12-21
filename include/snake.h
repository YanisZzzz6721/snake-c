#ifndef SNAKE_H
#define SNAKE_H 

#include "grid.h"

typedef struct Segment{
    int x;
    int y;
    struct Segment *next;
}Segment;

typedef struct Snake{
    Segment *head;
    Segment *tail;
    int lenght;
}Snake;

int snake_init(Snake *s, int start_x,int start_y,int initial_lenght);

void snake_free(Snake *s);

int snake_push_front(Snake *s,int x,int y);

void snake_pop_back(Snake *s);

void snake_write_to_grid(const Snake *s,Grid *g);

#endif
