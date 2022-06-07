#ifndef COL_H
#define COL_H

#include<stdio.h>
#include<stdlib.h>

typedef struct COLOR_T {
  int r;
  int g;
  int b;
} color;

color * init_color(int r, int g, int b);
void color_dump_debug(color * col);
void free_color(color * col);

#endif
