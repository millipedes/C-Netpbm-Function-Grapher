/**
 * @file file_io.c
 * @brief this file contains the function to write a canvas to a netpbm file
 * @author Matthew C. Lindeman
 * @date June 18, 2022
 * @bug None known
 * @todo Nothing
 */
#include "include/file_io.h"

/**
 * This function takes a given canvas and writes it to a netpbm file (to include
 * netpbm file headers).
 * @param file_name - the full path to the file
 * @param       can - the canvas to be written
 * @return      N/a
 */
void write_canvas_to_file(char * file_name, canvas * can) {
  FILE * fp = fopen(file_name, "w");
  fprintf(fp, "P3\n");
  fprintf(fp, "%d %d\n255\n", can->width, can->height);
  for(int i = 0; i < can->height; i++) {
    for(int j = 0; j < can->width; j++) {
      fprintf(fp, "%d %d %d\n", can->pixel_instance[i][j]->pix_color->r,
          can->pixel_instance[i][j]->pix_color->g,
          can->pixel_instance[i][j]->pix_color->b);
    }
  }
  fclose(fp);
}
