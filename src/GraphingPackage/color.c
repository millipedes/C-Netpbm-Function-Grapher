/**
 * @file   color.c
 * @brief  This file contains functions relating to initializing, modifying,
 * and debugging the data structure color (struct COLOR_T).
 * @author Matthew C. Lindeman
 * @date   June 07, 2022
 */
#include "include/color.h"

/**
 * This function initializes a color object given a red, green, and blue value.
 * @param    r - The red value (<= 255).
 * @param    g - The green value (<= 255).
 * @param    b - The blue value (<= 255).
 * @return col - The newly initialized color.
 */
color * init_color(int r, int g, int b) {
  color * col = calloc(1, sizeof(struct COLOR_T));
  col->r = r;
  col->g = g;
  col->b = b;
  return col;
}

/**
 * This function is used for debugging a color data structure.
 * @param  col - The color to be debugged.
 * @return N/a
 */
void color_dump_debug(color * col) {
  printf("Color:\n");
  printf("(%d, %d, %d)\n", col->r, col->g, col->b);
  printf("--\n");
}

/**
 * This function changes the rgb values contained in dest to that of src.
 * @param dest - The color structure to be changed.
 * @param  src - The color structure to be changed to.
 * @return N/a
 */
void change_color(color * dest, color * src) {
  dest->r = src->r;
  dest->g = src->g;
  dest->b = src->b;
}

/**
 * This function determines if a given color is white.  If so returns 1, and 0
 * otherwise.
 * @param test - the color to be tested
 * @return   1 - the color is white
 *           0 - the color is not white
 */
int is_color_white(color * test) {
  if(test->r == COL_MAX && test->g == COL_MAX && test->b == COL_MAX)
    return 1;
  return 0;
}

/**
 * This function is basically just a free wrapper, but the style of this project
 * requires free functions for each custom data structure.
 * @param  col - the color to be freed
 * @return N/a
 */
void free_color(color * col) {
  if(col)
    free(col);
}
