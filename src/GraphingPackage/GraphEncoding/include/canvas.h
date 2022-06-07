#ifndef CAN_H
#define CAN_H

#include"../../../main/include/constants.h"
#include"pixel.h"

typedef struct CANVAS_T {
  pixel ** pixel_instance;
  int height;
  int width;
} canvas;

canvas * init_canvas(int height, int width);
void canvas_dump_debug(canvas * can);
void free_canvas(canvas * can);

#endif
