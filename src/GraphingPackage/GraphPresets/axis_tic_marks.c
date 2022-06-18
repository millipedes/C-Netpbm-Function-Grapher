/**
 * @file   axis_tic_marks.c
 * @brief  This file contains the functions relating to the axis tic marks
 * @author Matthew C. Lindeman
 * @date   June 07, 2022
 * @bug    None known
 * @todo   Nothing
 */
#include "include/axis_tic_marks.h"

/**
 * This function initializes an axis tic mark struct
 * @param    qty - the quantity of tic marks
 * @param  width - the width of the rectangular tic marks
 * @param height - the height of the rectangular tic marks
 * @return
 */
axis_tic_marks * init_axis_tic_marks(int qty, int width, int height,
    axis this_axis) {
  axis_tic_marks * atm = calloc(1, sizeof(struct AXIS_TIC_MARKS));
  atm->qty = qty;
  atm->width = width;
  atm->height = height;
  atm->this_axis = this_axis;
  atm->col = init_color(COL_MIN, COL_MIN, COL_MIN);
  return atm;
}

/**
 * This function writes the axis tic marks to the canvas
 * @param  can - the canvas to be written to
 * @param  atm - the tic marks to write
 * @return N/a
 */
void write_atm_to_canvas(canvas * can, axis_tic_marks * atm) {
  int cur_rec_center = 0;
  int center_increment = 0;
  /* This name is chosen becuase it does not matter if it is X/Y */
  if(atm->this_axis == X) {
    center_increment = can->width / atm->qty;
    for(cur_rec_center = 0;
        cur_rec_center < can->width;
        cur_rec_center += center_increment) {
      write_rectangle(can, cur_rec_center, (can->width / 2), atm->height,
          atm->width, atm->col);
    }
  } else if(atm->this_axis == Y) {
    center_increment = can->height / atm->qty;
    for(cur_rec_center = 0;
        cur_rec_center < can->height;
        cur_rec_center += center_increment) {
      write_rectangle(can, (can->height / 2), cur_rec_center, atm->height,
          atm->width, atm->col);
    }
  }
}

/**
 * This function is for debugging tic marks
 * @param atm - the tic marks to debug
 * @return
 */
void axis_tic_marks_dump_debug(axis_tic_marks * atm) {
  printf("Axis Tic Marks:\n");
  printf("(qty, width, this_axis): (%d, %d, %c)\n", atm->qty, atm->width,
      (int)atm->this_axis == 0 ? 'X' : 'Y');
  printf("--\n");
}

/**
 * This function frees the axis tic marks
 * @param  atm - the tic marks to be freed
 * @return N/a
 */
void free_axis_tic_marks(axis_tic_marks * atm) {
  if(atm) {
    if(atm->col) {
      free_color(atm->col);
    }
    free(atm);
  }
}
