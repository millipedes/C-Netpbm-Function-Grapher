#include "../GraphingPackage/GraphPresets/include/graph_scale.h"

int main(void) {
  canvas      * can = init_canvas(15, 15);
  graph_scale * gs = init_graph_scale(init_axis_tic_marks(3, 3, 2, Y),
      init_coord_axis(1, X), init_coord_axis(1, Y),
      init_graph_border(init_color(0, 0, 0), 1), 2);
  write_gs_to_canvas(can, gs);
  letter_print_canvas(can);
  free_canvas(can);
  free_graph_scale(gs);
  return 0;
}
