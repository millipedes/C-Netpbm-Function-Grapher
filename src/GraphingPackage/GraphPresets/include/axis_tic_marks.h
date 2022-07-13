/**
 * @file   axis_tic_marks.h
 * @brief  This file contains the function definitions for axis_tic_marks.c
 * @author Matthew C. Lindeman
 * @date   June 07, 2022
 * @bug    None known
 * @todo   Nothing
 */
#ifndef ATM_H
#define ATM_H

#include "../../GraphEncoding/include/canvas.h"
#include "../../../main/include/constants.h"
#include "axis.h"

/**
 * This data structure contains the data related to the axis tic marks of a
 * particular axis (i.e. one axis_tic_marks for x and one for y).
 */
typedef struct AXIS_TIC_MARKS {
  /** The color of the axis tic marks, by default they are black (0,0,0)  */
  color * col;
  /** The total number of tic marks to be displayed */
  int qty;
  /** The width of the tic marks in pixels */
  int width;
  /** The height of the tic marks in pixels */
  int height;
  /** X or Y axis */
  axis this_axis;
} axis_tic_marks;

axis_tic_marks * init_axis_tic_marks(int qty, int width, int height,
    axis this_axis);
void write_atm_to_canvas(canvas * can, axis_tic_marks * atm);
void axis_tic_marks_dump_debug(axis_tic_marks * atm);
void free_axis_tic_marks(axis_tic_marks * atm);

#endif
