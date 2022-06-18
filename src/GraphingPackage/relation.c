/**
 * @file   relation.c
 * @brief  this file contains the functions that map relations to a canvas
 * @author Matthew C. Lindeman
 * @date   June 17, 2022
 * @bug    None known
 * @todo   Nothing
 */
#include "include/relation.h"

/**
 * This function writes a relation to a canvas with given graph scale.
 * @param  can - the canvas that will be written to.
 * @param   gs - the graph_scale that will be used as a reference
 * @param  rel - the relation that will be written to the canvas
 * @return N/a
 */
void write_rel_to_canvas(canvas * can, graph_scale * gs, double rel(double),
    color * col, double delta) {
  double y = 0;
  int x_index = 0;
  int y_index = 0;
  for(double i = gs->coord_axes[0]->axis_min;
      i < gs->coord_axes[0]->axis_max;
      i += delta) {
      y = rel(i);
      x_index = map_scale_to_canvas(can, gs, X, i);
      y_index = can->height - map_scale_to_canvas(can, gs, Y, y);
      if(y < gs->coord_axes[1]->axis_max
          && y >= gs->coord_axes[1]->axis_min
          && x_index >= 0 && x_index < can->width
          && y_index >= 0 && y_index < can->height)
        if(is_color_white(can->pixel_instance[y_index][x_index]->pix_color))
          change_color(can->pixel_instance[y_index][x_index]->pix_color, col);
  }
}

/**
 * This function takes a quantity in the scale of the relation and maps it to a
 * canvas index
 * @param can - the canvas to find the index of
 * @param  gs - the graph_scale to make the map
 * @param  ax - then axis for which we are finding the map
 * @param qty - the quantity of the relation
 * @return
 */
int map_scale_to_canvas(canvas * can, graph_scale * gs, axis ax, double qty) {
  /**
   * We are trying to solve the equation:
   * (x|y)_instance / (x|y)_total_magnitude = ? / canvas_width
   * In other words the map from the x that the relation is using (for example
   * x^2(2) == 4 but this is not 4 the index on the canvas) to the canvas index
   */
  if(ax == X)
    return (int)((qty / (gs->coord_axes[0]->axis_max - gs->coord_axes[0]->axis_min))
      * can->width);
  else
    return (int)((qty / (gs->coord_axes[1]->axis_max - gs->coord_axes[1]->axis_min))
      * can->height);
}
