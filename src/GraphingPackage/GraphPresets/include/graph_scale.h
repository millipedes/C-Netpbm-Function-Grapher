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
#include "numerics.h"

/**
 * This struct is used for containing the presets of a graph_scale (i.e. what
 * x/y values does the graph span, tic mark and border info etc.).
 */
typedef struct GRAPH_SCALE_T {
  /** (index 0 : x) (index 1 : y) */
  axis_tic_marks ** atm;
  /** (index 0 : x) (index 1 : y) */
  coord_axis ** coord_axes;
  /** The border of the graph */
  graph_border * gb;
  /** The numbers for the scale under/around tic marks */
  numeric ** num;
  /** Earlier in development I postulated 3d graphs but we are still a ways
   * away
   */
  int axis_no;
} graph_scale;

graph_scale * init_graph_scale(axis_tic_marks * atm_x, axis_tic_marks * atm_y,
    coord_axis * ca_x, coord_axis * ca_y, graph_border * gb, int axis_no);
numeric * make_x_numeric(graph_scale * gs);
numeric * make_y_numeric(graph_scale * gs);
void write_gs_to_canvas(canvas * can, graph_scale * gs);
void free_graph_scale(graph_scale * gs);

#endif
