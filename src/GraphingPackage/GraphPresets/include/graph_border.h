/**
 * @file   graph_border.h
 * @brief  this file contains the function definitions for graph_border.c
 * @author Matthew C. Lindeman
 * @date   June 07, 2022
 * @bug    None known
 * @todo   Nothing
 */
#ifndef GRB_H
#define GRB_H

#include "../../include/color.h"
#include "../../GraphEncoding/include/canvas.h"

/**
 * This structure contains the data related to the graph border.
 */
typedef struct GRAPH_BORDER_T {
  /** The color of the graph border */
  color * b_color;
  /** The width in pixels of the graph border */
  int width;
} graph_border;

graph_border * init_graph_border(color * b_color, int width);
void write_gb_to_canvas(canvas * can, graph_border * gb);
void graph_border_dump_debug(graph_border * gb);
void free_graph_border(graph_border * gb);

#endif
