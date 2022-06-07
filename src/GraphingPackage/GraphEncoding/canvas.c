#include"include/canvas.h"

canvas * init_canvas(int height, int width) {
  canvas * can = calloc(1, sizeof(struct CANVAS_T));
  can->height = height;
  can->width = width;
  can->pixel_instance = calloc(height, sizeof(struct PIXEL_T *));
  for(int i = 0; i < height; i++) {
    can->pixel_instance[i] =
      init_pixel(init_color(COL_MAX, COL_MAX, COL_MAX), 0);
  }
  return can;
}

void canvas_dump_debug(canvas * can) {
  printf("Canvas:\n");
  for(int i = 0; i < can->height; i++) {
    pixel_dump_debug(can->pixel_instance[i]);
  }
  printf("(h, w): (%d, %d)\n", can->height, can->width);
}

void free_canvas(canvas * can) {
  if(can) {
    if(can->pixel_instance) {
      for(int i = 0; i < can->height;  i++) {
        if(can->pixel_instance[i])
          free_pixel(can->pixel_instance[i]);
      }
      free(can->pixel_instance);
    }
    free(can);
  }
}
