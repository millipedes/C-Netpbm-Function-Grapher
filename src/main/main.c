#include<math.h>
#include "../GraphingPackage/GraphPresets/include/graph_scale.h"
#include "../GraphingPackage/include/file_io.h"
#include"../GraphingPackage/include/relation.h"

double x_squared(double x);

int main(void) {
  canvas      * can = init_canvas(1000, 1000);
  graph_scale * gs = init_graph_scale(
      init_axis_tic_marks(10, 10, 30, X),         // x axis tic marks
      init_axis_tic_marks(10, 30, 10, Y),         // y axis tic marks
      init_coord_axis(5, X),                      // x axis
      init_coord_axis(5, Y),                      // y axis
      init_graph_border(init_color(0, 0, 0), 10), // border of graph
      2                                           // no axes (don't change!)
      );
  write_gs_to_canvas(can, gs);
  write_canvas_to_file("test.ppm", can);
  // write_rel_to_canvas(can, x_squared, init_color(255, 0, 0));
  free_canvas(can);
  free_graph_scale(gs);
  return 0;
}

double x_squared(double x) {
  return pow(x, 2);
}
