/**
 * @file   canvas.c
 * @brief  this file contains the canvas related functions
 * @author Matthew C. Lindeman
 * @date   June 07, 2022
 * @bug    None known
 * @todo   Nothing
 */
#include "include/canvas.h"

/**
 * This function intializes a canvas of given height and width
 * @param height - the height of the canvas
 * @param  width - the width of the canvas
 * @return   can - the new canvas
 */
canvas * init_canvas(int height, int width) {
  canvas * can = calloc(1, sizeof(struct CANVAS_T));
  can->height = height;
  can->width = width;
  can->pixel_instance = calloc(height, sizeof(struct PIXEL_T **));
  for(int i = 0; i < height; i++) {
    can->pixel_instance[i] = calloc(width, sizeof(struct PIXEL_T *));
    for(int j = 0; j < width; j++) {
      can->pixel_instance[i][j] =
        init_pixel(init_color(COL_MAX, COL_MAX, COL_MAX), 0);
    }
  }
  return can;
}

/**
 * This function is used for debugging a canvas structure
 * @param  can - the canvas structure
 * @return N/a
 */
void canvas_dump_debug(canvas * can) {
  printf("Canvas:\n");
  for(int i = 0; i < can->height; i++) {
    for(int j = 0; j < can->width; j++)
      pixel_dump_debug(can->pixel_instance[i][j]);
  }
  printf("(h, w): (%d, %d)\n", can->height, can->width);
}

/**
 * This function draws a rectangle centered at (cen_x, cen_y) on the canvas of
 * the given color
 * @param   can - the canvas to be written to
 * @param cen_x - the x center coordinate of the reactangle
 * @param cen_y - the canvas to be written to
 * @param     h - the height of the rectangle
 * @param     w - the width of the rectangle
 * @param   col - the color of the rectangle
 * @return  N/a
 */
void write_rectangle(canvas * can, int cen_x, int cen_y, int h, int w,
    color * col) {
  // Start top until the bottom
  for(int i = (cen_y - (h / 2)); i <= (cen_y + (h / 2)); i++)
    // Start at the left until the right
    for(int j = (cen_x - (w / 2)); j <= (cen_x + (w / 2)); j++)
      if(i >= 0 && j >= 0 && i < can->height && j < can->width)
        change_color(can->pixel_instance[i][j]->pix_color, col);
}

void write_rectangle_from_ul(canvas * can, int left_x, int up_y, int h, int w,
    color * col) {
  for(int i = up_y; i <= (up_y + h); i++)
    for(int j = left_x; j <= (left_x + w); j++)
      if(i >= 0 && j >= 0 && i < can->height && j < can->width)
        change_color(can->pixel_instance[i][j]->pix_color, col);
}

/**
 * This function frees a canvas
 * @param  can - the canvas
 * @return N/a
 */
void free_canvas(canvas * can) {
  if(can) {
    if(can->pixel_instance) {
      for(int i = 0; i < can->height;  i++)
        if(can->pixel_instance[i]) {
          for(int j = 0; j < can->width; j++)
            if(can->pixel_instance[i][j])
              free_pixel(can->pixel_instance[i][j]);
          free(can->pixel_instance[i]);
      }
      free(can->pixel_instance);
    }
    free(can);
  }
}
