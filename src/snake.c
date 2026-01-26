#include "snake.h"
#include <stdlib.h>
#include <stdio.h>

static Segment *segment_new(int x,int y){
    Segment *seg = (Segment*)malloc(sizeof(Segment));
    if(!seg){
        perror("Erreur d'allocation mémoire");
        return NULL;
    }
    seg->x = x; seg->y = y;
    seg->next = NULL;
    return seg;
}

void snake_free(Snake *s){
    if(!s) return;
    Segment *cur = s->head;
    while (cur != NULL){
        Segment *next = cur->next;
        free(cur);
        cur = next;
    }
    s->tail = s->head = NULL;
    s->lenght = 0;
}

int snake_init(Snake *s, int start_x,int start_y,int initial_lenght){
    if(!s){
        perror("Erreur d'allocation mémoire");
        return -1;
    }
    if (initial_lenght <= 0){
        perror("Erreur | lenght initiale trop court");
        return -1;
    }
    s->head = s->tail = NULL;
    s->lenght = 0;
    Segment *nwhead = segment_new(start_x,start_y);
    if (!nwhead){
        fprintf(stderr,"Erreur d'allocation");
        return -2;
    }
    s->head = nwhead;
    s->tail = nwhead;
    s->lenght = 1;
    Segment *cur = nwhead;
    for (int i = 1; i < initial_lenght; i++){
        Segment *seg = segment_new(start_x-i,start_y);
        if(!seg){
            fprintf(stderr,"Erreur d'allocation mémoire");
            free(s);
            return -3;
        }
        cur->next = seg;
        cur = seg;
        s->tail = seg;
        s->lenght++;
    }
    s->dir = DIR_RIGHT;
    return 0;
}


int snake_push_front(Snake *s,int x,int y){
    if(!s){
        fprintf(stderr,"Erreur d'allocation mémoire");
        return -1;
    }
    Segment *newhead = segment_new(x,y);
    if (!newhead){
        fprintf(stderr,"Erreur d'allocation");
        return -2;
    }
    newhead->next = s->head;
    s->head = newhead;
    if (s->tail == NULL){
        s->tail = newhead;
    }
    s->lenght++;
    return 0;
}



void snake_pop_back(Snake *s){
    if(!s || !s->head){
        fprintf(stderr,"Erreur d'allocation mémoire");
        return;
    }
    if (s->tail == s->head){
        free(s->head);
        s->head = NULL;
        s->tail = NULL;
        s->lenght = 0;
        return;
    }
    Segment *cur = s->head;
    while (cur != s->tail)
        cur = cur->next;
    free(s->tail);
    s->tail = cur;
    cur->next = NULL;
    s->lenght--;
}

void snake_write_to_grid(const Snake *s, Grid *g){
    if (!s || !g || !g->cells) return;
    Segment *cur = s->head;
    while (cur != NULL){
        if (cur->x >= 0 && cur->x < g->width && cur->y >= 0 && cur->y < g->height){
            grid_set(g, cur->x,cur->y,TILE_SNAKE);
        }
        cur = cur->next;
    }
}