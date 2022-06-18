/**
 * @file   graph_border.c
 * @brief  this file contains the functions related to the border of the graph
 * @author Matthew C. Lindeman
 * @date   June 07, 2022
 * @bug    None known
 * @todo   Nothing
 */
#include "include/graph_border.h"

/**
 * This function initializes a graph border
 * @param b_color - the color of the border
 * @param   width - the width of the border
 * @return     gb - the new border
 */
graph_border * init_graph_border(color * b_color, int width) {
  graph_border * gb = calloc(1, sizeof(struct GRAPH_BORDER_T));
  gb->b_color = b_color;
  gb->width = width;
  return gb;
}

/**
 * This function writes a graph border to a given canvas
 * @param  can - the canvas to be written to
 * @param   gb - the graph_border to write
 * @return N/a
 */
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

/**
 * This function is used to debug the Graph Border
 * @param   gb - the graph_border to be debugged
 * @return N/a
 */
void graph_border_dump_debug(graph_border * gb) {
  printf("Graph Border:\n");
  color_dump_debug(gb->b_color);
  printf("Border Width: %d\n", gb->width);
  printf("--\n");
}

/**
 * This function frees a graph border
 * @param   gb - the graph_border
 * @return N/a
 */
void free_graph_border(graph_border * gb) {
  if(gb) {
    if(gb->b_color)
      free_color(gb->b_color);
    free(gb);
  }
} 
