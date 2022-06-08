#include "../GraphingPackage/GraphPresets/include/graph_scale.h"
#include "../GraphingPackage/include/file_io.h"

int main(void) {
  canvas      * can = init_canvas(1000, 1000);
  graph_scale * gs = init_graph_scale(init_axis_tic_marks(10, 10, 30, X),
      init_axis_tic_marks(10, 30, 10, Y), init_coord_axis(5, X),
      init_coord_axis(5, Y), init_graph_border(init_color(0, 0, 0), 10), 2);
  write_gs_to_canvas(can, gs);
  write_canvas_to_file("test.ppm", can);
  free_canvas(can);
  free_graph_scale(gs);
  return 0;
}
