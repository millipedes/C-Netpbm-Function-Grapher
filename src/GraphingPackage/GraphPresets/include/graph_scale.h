/**
 * @file   graph_scale.h
 * @brief  This file contains the function definitions for graph_scale.c
 * @author Matthew C. Lindeman
 * @date   June 07, 2022
 * @bug    None known
 * @todo   Nothing
 */
#ifndef GRS_H
#define GRS_H

#include "axis_tic_marks.h"
#include "coord_axis.h"
#include "graph_border.h"

typedef struct GRAPH_SCALE_T {
  axis_tic_marks ** atm;    // (index 0 : x) (index 1 : y) (maybe index 2 : z)
  coord_axis ** coord_axes; // (index 0 : x) (index 1 : y) (maybe index 2 : z)
  graph_border * gb;        // Just the border
  int axis_no;              // 2 || 3 qty of axes
} graph_scale;

graph_scale * init_graph_scale(axis_tic_marks * atm_x, axis_tic_marks * atm_y,
    coord_axis * ca_x, coord_axis * ca_y, graph_border * gb, int axis_no);
void write_gs_to_canvas(canvas * can, graph_scale * gs);
void free_graph_scale(graph_scale * gs);

#endif
