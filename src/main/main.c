#include <stdio.h>
#include "../GraphingPackage/GraphEncoding/include/canvas.h"
#include "../GraphingPackage/GraphPresets/include/graph_border.h"
#include "../GraphingPackage/GraphPresets/include/coord_axis.h"
#include "../GraphingPackage/GraphPresets/include/axis.h"

int main(void) {
  canvas * can = init_canvas(3, 3);
  graph_border * gb = init_graph_border(init_color(0, 0, 0), 1);
  coord_axis * c_a = init_coord_axis(1, Y);
  write_ca_to_canvas(can, c_a);
  canvas_dump_debug(can);
  free_coord_axis(c_a);
  free_graph_border(gb);
  free_canvas(can);
  return 0;
}
