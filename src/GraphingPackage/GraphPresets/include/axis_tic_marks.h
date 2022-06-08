#ifndef ATM_H
#define ATM_H

#include "../../GraphEncoding/include/canvas.h"
#include"../../../main/include/constants.h"
#include "axis.h"

typedef struct AXIS_TIC_MARKS {
  color * col;
  int qty;
  int width;
  int height;
  axis this_axis;
} axis_tic_marks;

axis_tic_marks * init_axis_tic_marks(int qty, int width, int height, axis this_axis);
void write_atm_to_canvas(canvas * can, axis_tic_marks * atm);
void axis_tic_marks_dump_debug(axis_tic_marks * atm);
void free_axis_tic_marks(axis_tic_marks * atm);

#endif
