#include <stdio.h>
#include "../GraphingPackage/GraphEncoding/include/canvas.h"
#include "../GraphingPackage/GraphPresets/include/graph_border.h"

int main(void) {
  canvas * can = init_canvas(3, 3);
  graph_border * gb = init_graph_border(init_color(0, 0, 0), 1);
  write_gb_to_canvas(can, gb);
  canvas_dump_debug(can);
  free_graph_border(gb);
  free_canvas(can);
  return 0;
}
