#include <math.h>
#include "../GraphingPackage/include/relation.h"
#include "../GraphingPackage/include/file_io.h"

double x_squared(double x);

int main(void) {
  canvas      * can = init_canvas(1000, 1000);
  graph_scale * gs = init_graph_scale(
      init_axis_tic_marks(10, 10, 30, X),         // x axis tic marks
      init_axis_tic_marks(10, 30, 10, Y),         // y axis tic marks
      init_coord_axis(0, 10.0, 5, X),             // x axis
      init_coord_axis(0, 10.0, 5, Y),             // y axis
      init_graph_border(init_color(0, 0, 0), 10), // border of graph
      2                                           // no axes (don't change!)
      );
  write_gs_to_canvas(can, gs);
  color * green = init_color(0, 255, 0);
  write_rel_to_canvas(can, gs, x_squared, green, 0.0000001);
  write_canvas_to_file("test.ppm", can);
  free_color(green);
  free_canvas(can);
  free_graph_scale(gs);
  return 0;
}

double x_squared(double x) {
  return pow(x, 2);
}
