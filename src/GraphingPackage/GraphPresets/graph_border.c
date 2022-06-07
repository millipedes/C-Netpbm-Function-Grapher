#include"include/graph_border.h"

graph_border * init_graph_border(color * b_color, int width) {
  graph_border * gb = calloc(1, sizeof(struct GRAPH_BORDER_T));
  gb->b_color = b_color;
  gb->width = width;
  return gb;
}

void write_gb_to_canvas(canvas * can, graph_border * gb) {
  for(int i = 0; i < can->height; i++) {
    for(int j = 0; j < can->width; j++) {
      if(i < gb->width || i >= (can->height - gb->width)
          || j < gb->width || j >= (can->width - gb->width)) {
        change_color(can->pixel_instance[i][j]->pix_color, gb->b_color);
      }
    }
  }
}

void graph_border_dump_debug(graph_border * gb) {
  printf("Graph Border:\n");
  color_dump_debug(gb->b_color);
  printf("Border Width: %d\n", gb->width);
  printf("--\n");
}

void free_graph_border(graph_border * gb) {
  if(gb) {
    if(gb->b_color)
      free_color(gb->b_color);
    free(gb);
  }
} 
