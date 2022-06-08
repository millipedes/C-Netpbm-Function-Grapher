/**
 * @file canvas.h
 * @brief this file contains the function definitions for canvas.c
 * @author Matthew C. Lindeman
 * @date June 07, 2022
 * @bug None known
 * @todo Nothing
 */
#ifndef CAN_H
#define CAN_H

#include "../../../main/include/constants.h"
#include "pixel.h"

typedef struct CANVAS_T {
  pixel *** pixel_instance;
  int height;
  int width;
} canvas;

canvas * init_canvas(int height, int width);
void canvas_dump_debug(canvas * can);
void write_rectangle(canvas * can, int cen_x, int cen_y, int h, int w,
    color * col);
void letter_print_canvas(canvas * can);
void free_canvas(canvas * can);

#endif
