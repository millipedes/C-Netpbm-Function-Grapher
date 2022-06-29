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
      // See y notes for why negative minimums require an if
      if(gs->coord_axes[0]->axis_min >= 0)
        x_index = map_scale_to_canvas(can, gs, X, i);
      else
        x_index
          = map_scale_to_canvas(can, gs, X, i - gs->coord_axes[0]->axis_min);
      /**
       * Because the canvas y is upside down (i.e. zero is top not bottom) we
       * need to invert the y index values (hence the can->height - ...).
       *
       * If there are negative values in the user defined graph_scale then we
       * need to add the magnitude of the negative value as map_scale_to_canvas
       * expects only natural number scalar magnitudes for the mapping (think
       * about how to map two line segments to one another, that is the method
       * used).
       */
      if(gs->coord_axes[1]->axis_min >= 0)
        y_index = can->height - map_scale_to_canvas(can, gs, Y, y);
      else
        y_index = can->height -
          (map_scale_to_canvas(can, gs, Y, y - gs->coord_axes[1]->axis_min));
      if(y < gs->coord_axes[1]->axis_max
          && y >= gs->coord_axes[1]->axis_min
          && x_index >= 0 && x_index < can->width
          && y_index >= 0 && y_index < can->height)
        if(is_color_white(can->pixel_instance[y_index][x_index]->pix_color))
          change_color(can->pixel_instance[y_index][x_index]->pix_color, col);
  }
}

/**
 * This funciton writes a function to a canvas for a given abstract syntax tree.
 * @param     can - the canvas to be written
 * @param      gs - the graph scale corresponding to the given canvas
 * @param abstree - the given abstract syntax tree function to write
 * @param     col - the color of the function on the graph
 * @param   delta - the increment to write the relation with (smaller -> more
 * definition on graphs)
 * @return    N/a
 */
void write_ast_to_canvas(canvas * can, graph_scale * gs, ast * abstree,
    color * col, double delta) {
  double y = 0;
  int x_index = 0;
  int y_index = 0;
  for(double i = gs->coord_axes[0]->axis_min;
      i < gs->coord_axes[0]->axis_max;
      i += delta) {
      y = evaluate_tree(abstree, i);
      // See y notes for why negative minimums require an if
      if(gs->coord_axes[0]->axis_min >= 0)
        x_index = map_scale_to_canvas(can, gs, X, i);
      else
        x_index
          = map_scale_to_canvas(can, gs, X, i - gs->coord_axes[0]->axis_min);
      /**
       * Because the canvas y is upside down (i.e. zero is top not bottom) we
       * need to invert the y index values (hence the can->height - ...).
       *
       * If there are negative values in the user defined graph_scale then we
       * need to add the magnitude of the negative value as map_scale_to_canvas
       * expects only natural number scalar magnitudes for the mapping (think
       * about how to map two line segments to one another, that is the method
       * used).
       */
      if(gs->coord_axes[1]->axis_min >= 0)
        y_index = can->height - map_scale_to_canvas(can, gs, Y, y);
      else
        y_index = can->height -
          (map_scale_to_canvas(can, gs, Y, y - gs->coord_axes[1]->axis_min));
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
