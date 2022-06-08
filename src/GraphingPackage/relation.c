#include "include/relation.h"

void write_rel_to_canvas(canvas * can, double rel(double), color * col) {
  double y = 0;
  for(int i = 0; i < can->width; i++) {
    y = rel((double) i);
    if(y < can->height && y >= 0)
      change_color(can->pixel_instance[i][(int)y]->pix_color, col);
  }
}
