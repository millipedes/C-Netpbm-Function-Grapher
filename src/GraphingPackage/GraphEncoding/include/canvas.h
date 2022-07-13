/**
 * @file   canvas.h
 * @brief  this file contains the function definitions for canvas.c
 * @author Matthew C. Lindeman
 * @date   June 07, 2022
 * @bug    None known
 * @todo   Nothing
 */
#ifndef CAN_H
#define CAN_H

#include "../../../main/include/constants.h"
#include "pixel.h"

/**
 * This structure is representative of the canvas that will be written to an
 * output netpbm file.
 */
typedef struct CANVAS_T {
  /** The pixels of the canvas */
  pixel *** pixel_instance;
  /** The height of the canvas in pixels */
  int height;
  /** The width of the canvas in pixels */
  int width;
} canvas;

canvas * init_canvas(int height, int width);
void canvas_dump_debug(canvas * can);
void write_rectangle(canvas * can, int cen_x, int cen_y, int h, int w,
    color * col);
void write_rectangle_from_ul(canvas * can, int left_x, int up_y, int h, int w,
    color * col);
void free_canvas(canvas * can);

#endif
