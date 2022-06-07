/**
 * @file color.c
 * @brief This file contains functions relating to color
 * @author Matthew C. Lindeman
 * @date June 07, 2022
 * @bug None known
 * @todo Nothing
 */
#include"include/color.h"

/**
 * This function initializes a color object given a red, green, and blue value
 * @param    r - the red value (<= 255)
 * @param    g - the green value (<= 255)
 * @param    b - the blue value (<= 255)
 * @return col - the new color
 */
color * init_color(int r, int g, int b) {
  color * col = calloc(1, sizeof(struct COLOR_T));
  col->r = r;
  col->g = g;
  col->b = b;
  return col;
}

/**
 * This function is used for debugging a color
 * @param  col - the color to be debugged
 * @return N/a
 */
void color_dump_debug(color * col) {
  printf("Color:\n");
  printf("(%d, %d, %d)\n", col->r, col->g, col->b);
  printf("--\n");
}

/**
 * This function chandes the color of dest to that of src
 * @param dest - the color to be changed
 * @param  src - the color to be changed to
 * @return N/a
 */
void change_color(color * dest, color * src) {
  dest->r = src->r;
  dest->g = src->g;
  dest->b = src->b;
}

/**
 * This function is basically just a free wrapper, but a part of the coding
 * style for this project
 * @param  col - the color to be freed
 * @return N/a
 */
void free_color(color * col) {
  if(col)
    free(col);
}
