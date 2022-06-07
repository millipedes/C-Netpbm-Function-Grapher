/**
 * @file canvas.c
 * @brief this file contains the canvas related functions
 * @author Matthew C. Lindeman
 * @date June 07, 2022
 * @bug None known
 * @todo Nothing
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
 * This function frees a canvas
 * @param  can - the canvas
 * @return N/a
 */
void free_canvas(canvas * can) {
  if(can) {
    if(can->pixel_instance) {
      for(int i = 0; i < can->height;  i++) {
        if(can->pixel_instance[i]) {
          for(int j = 0; j < can->width; j++) {
            if(can->pixel_instance[i][j])
              free_pixel(can->pixel_instance[i][j]);
          }
          free(can->pixel_instance[i]);
        }
      }
      free(can->pixel_instance);
    }
    free(can);
  }
}
