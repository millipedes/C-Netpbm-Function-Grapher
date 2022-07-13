/**
 * @file   coord_axis.h
 * @brief  This file contains the function definitions for coord_axis
 * @author Matthew C. Lindeman
 * @date   June 07, 2022
 * @bug    None known
 * @todo   Nothing
 */
#ifndef CAX_H
#define CAX_H

#include <stdlib.h>
#include "../../include/color.h"
#include "../../GraphEncoding/include/canvas.h"
#include "axis.h"

/**
 * A coordinate axis line for subdividing the graph. Marked on the center of the
 * scale and not the origin.  For example if the scale is -10 to 0 on an axis
 * then the line would be on -5, not  dividing quadrants by being on 0.
 */
typedef struct COORD_AXIS_T {
  /** The color of the coordinate axis, default black (0,0,0) */
  color * black;
  /** The minimum value of the axis */
  double axis_min;
  /** The maximum value of the axis */
  double axis_max;
  /** The width in pixels of the axis */
  int width;
  /** X or Y axis */
  axis this_axis;
} coord_axis;

coord_axis * init_coord_axis(double axis_min, double axis_max, int width,
    axis this_axis);
void write_ca_to_canvas(canvas * can, coord_axis * ca);
int in_range_of_ca(coord_axis * ca, int scalar_size, int qty);
void coord_axis_dump_debug(coord_axis * ca);
void free_coord_axis(coord_axis * ca);

#endif
