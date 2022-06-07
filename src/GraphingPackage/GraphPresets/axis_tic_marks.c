/**
 * @file axis_tic_marks.c
 * @brief This file contains the functions relating to the axis tic marks
 * @author Matthew C. Lindeman
 * @date June 07, 2022
 * @bug None known
 * @todo Nothing
 */
#include "include/axis_tic_marks.h"

axis_tic_marks * init_axis_tic_marks(int qty, int width, axis this_axis) {
  axis_tic_marks * atm = calloc(1, sizeof(struct AXIS_TIC_MARKS));
  atm->qty = qty;
  atm->width = width;
  atm->this_axis = this_axis;
  atm->col = init_color(COL_MIN, COL_MIN, COL_MIN);
  return atm;
}

void write_atm_to_canvas(canvas * can, axis_tic_marks * atm) {
}

void axis_tic_marks_dump_debug(axis_tic_marks * atm) {
  printf("Axis Tic Marks:\n");
  printf("(qty, width, this_axis): (%d, %d, %c)\n", atm->qty, atm->width,
      (int)atm->this_axis == 0 ? 'X' : 'Y');
  printf("--\n");
}

void free_axis_tic_marks(axis_tic_marks * atm) {
  if(atm) {
    if(atm->col) {
      free_color(atm->col);
    }
    free(atm);
  }
}
