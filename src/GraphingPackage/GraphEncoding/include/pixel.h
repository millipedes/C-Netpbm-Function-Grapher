/**
 * @file pixel.h
 * @brief This file contains the function definitions for pixel.c
 * @author Matthew C. Lindeman
 * @date June 07, 2022
 * @bug None known
 * @todo Nothing
 */
#ifndef PIX_H
#define PIX_H

#include"../../include/color.h"

typedef struct PIXEL_T {
  color * pix_color;
  int layer_no;
} pixel;

pixel * init_pixel(color * pix_color, int layer_no);
void pixel_dump_debug(pixel * pix);
void free_pixel(pixel * pix);

#endif
