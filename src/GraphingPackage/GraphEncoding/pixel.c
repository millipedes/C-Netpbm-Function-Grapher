/**
 * @file   pixel.c
 * @brief  This file contains the functions relating to pixels
 * @author Matthew C. Lindeman
 * @date   June 07, 2022
 * @bug    None known
 * @todo   Nothing
 */
#include "include/pixel.h"

/**
 * This function initializes a pixel
 * @param  pix_color - the color of the pixel
 * @param   layer_no - the layer number of the pixel (i.e. is it above/below
 * another)
 * @return     pix - the new pixel
 */
pixel * init_pixel(color * pix_color, int layer_no) {
  pixel * pix = calloc(1, sizeof(struct PIXEL_T));
  pix->pix_color = pix_color;
  pix->layer_no = layer_no;
  return pix;
}

/**
 * This function is used in debugging a pixel
 * @param  pix - the pixel to be debugged
 * @return N/a
 */
void pixel_dump_debug(pixel * pix) {
  printf("Pixel:\n");
  printf("Color Layer No: %d\n", pix->layer_no);
  color_dump_debug(pix->pix_color);
  printf("--\n");
}

/**
 * This function frees a pixel
 * @param  pix - the pixel to be freed
 * @return N/a
 */
void free_pixel(pixel * pix) {
  if(pix) {
    if(pix->pix_color)
      free_color(pix->pix_color);
    free(pix);
  }
}
