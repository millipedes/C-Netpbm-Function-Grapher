/**
 * @file color.h
 * @brief This file contains function definitions for color.c
 * @author Matthew C. Lindeman
 * @date June 07, 2022
 * @bug None known
 * @todo Nothing
 */
#ifndef COL_H
#define COL_H

#include <stdio.h>
#include <stdlib.h>

typedef struct COLOR_T {
  int r;
  int g;
  int b;
} color;

color * init_color(int r, int g, int b);
void color_dump_debug(color * col);
void change_color(color * dest, color * src);
void free_color(color * col);

#endif
