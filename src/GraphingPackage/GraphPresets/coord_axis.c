/**
 * @file coord_axis.c
 * @brief This file contains the functions relating to the coordinate axis of a
 * graph
 * @author Matthew C. Lindeman
 * @date June 07, 2022
 * @bug None known
 * @todo Nothing
 */
#include "include/coord_axis.h"

/**
 * This function initializes the coordinate axis
 * @param     width - the width of the axis
 * @param this_axis - which axis i.e. X, Y, Z (no Z support atm)
 * @return
 */
coord_axis * init_coord_axis(int width, axis this_axis) {
  coord_axis * ca = calloc(1, sizeof(struct COORD_AXIS_T));
  ca->width = width;
  ca->this_axis = this_axis;
  return ca;
}

/**
 * This function is used to write a coordinate axis to a canvas
 * @param can - the canvas to write the axes to
 * @param c_a - the coordinate axis to be written
 * @return
 */
void write_ca_to_canvas(canvas * can, coord_axis * c_a) {
  for(int i = 0; i < canvas->height; i++) {
    for(int j = 0; j < canvas->width; j++) {
      if(c_a->this_axis == X) {
      } else if(c_a->this_axis == Y) {
      }
    }
  }
}

int in_range_of_ca(coord_axis * ca, int scalar_size, int qty) {
  int mid = scalar_size
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
}

/**
 * This function is basically just a free wrapper but project style
 * @param   ca - the coordinate axis to be freed
 * @return N/a
 */
void free_coord_axis(coord_axis * ca) {
  if(ca)
    free(ca);
}
