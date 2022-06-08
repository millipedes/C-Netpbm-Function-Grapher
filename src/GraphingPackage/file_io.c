#include "include/file_io.h"

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
