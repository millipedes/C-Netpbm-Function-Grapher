/**
 * @file   coord_axis.c
 * @brief  This file contains the functions relating to the coordinate axis of a
 * graph
 * @author Matthew C. Lindeman
 * @date   June 07, 2022
 * @bug    None known
 * @todo   Nothing
 */
#include "include/coord_axis.h"

/**
 * This function initializes the coordinate axis
 * @param     width - the width of the axis
 * @param this_axis - which axis i.e. X, Y, Z (no Z support atm)
 * @return       ca - the new axis
 */
coord_axis * init_coord_axis(double axis_min, double axis_max, int width,
    axis this_axis) {
  coord_axis * ca = calloc(1, sizeof(struct COORD_AXIS_T));
  ca->axis_min = axis_min;
  ca->axis_max = axis_max;
  ca->width = width;
  ca->this_axis = this_axis;
  ca->black = init_color(COL_MIN, COL_MIN, COL_MIN);
  return ca;
}

/**
 * This function is used to write a coordinate axis to a canvas
 * @param  can - the canvas to write the axes to
 * @param  c_a - the coordinate axis to be written
 * @return N/a
 */
void write_ca_to_canvas(canvas * can, coord_axis * c_a) {
  for(int i = 0; i < can->height; i++) {
    for(int j = 0; j < can->width; j++) {
      if(c_a->this_axis == X && in_range_of_ca(c_a, can->height, i)) {
        change_color(can->pixel_instance[i][j]->pix_color, c_a->black);
      } else if(c_a->this_axis == Y && in_range_of_ca(c_a, can->width, j)) {
        change_color(can->pixel_instance[i][j]->pix_color, c_a->black);
      }
    }
  }
}

/**
 * This function determins if qty exists within the boundry of the axis
 * @param          ca - the coordinate axis to test
 * @param scalar_size - the size of the canvas to test (the reason I made this
 * function is it doesn't matter the dimension (i.e. X, Y) the algorithm is the
 * same)
 * @param         qty - the quantity to test
 * @return          1 - qty in boundry of axis
 *                  0 - qty not in boundry of axis
 */
int in_range_of_ca(coord_axis * ca, int scalar_size, int qty) {
  int mid = scalar_size / 2;
  if(qty > mid - ca->width && qty < mid + ca->width)
    return 1;
  return 0;
}

/**
 * This function is used for debugging coordinate axis
 * @param   ca - the coordinate axis
 * @return N/a
 */
void coord_axis_dump_debug(coord_axis * ca) {
  printf("Coordinate Axis:\n");
  printf("%c Axis of %d width\n", (int)ca->this_axis == 0 ? 'X' : 'Y',
      ca->width);
  printf("Axis Min: %lf Axis Max: %lf\n", ca->axis_min, ca->axis_max);
}

/**
 * This function is basically just a free wrapper but project style
 * @param   ca - the coordinate axis to be freed
 * @return N/a
 */
void free_coord_axis(coord_axis * ca) {
  if(ca) {
    if(ca->black)
      free_color(ca->black);
    free(ca);
  }
}
