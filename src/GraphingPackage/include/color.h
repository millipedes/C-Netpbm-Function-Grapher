/**
 * @file   color.h
 * @brief  This file contains function definitions for color.c
 * @author Matthew C. Lindeman
 * @date   June 07, 2022
 * @bug    None known
 * @todo   Nothing
 */
#ifndef COL_H
#define COL_H

#include <stdio.h>
#include <stdlib.h>
#include "../../main/include/constants.h"

/**
 * This structure is used to represent an rgb color.
 */
typedef struct COLOR_T {
  /** The red value of the color */
  int r;
  /** The green value of the color */
  int g;
  /** The blue value of the color */
  int b;
} color;

color * init_color(int r, int g, int b);
void color_dump_debug(color * col);
int is_color_white(color * test);
void change_color(color * dest, color * src);
void free_color(color * col);

#endif
