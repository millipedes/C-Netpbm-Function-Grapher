/**
 * @file   graph_scale.c
 * @brief  This file contains the functions related to the graph scale struct
 * (i.e. the tic marks, the axes, and the border)
 * @author Matthew C. Lindeman
 * @date   June 07, 2022
 * @bug    None known
 * @todo   Nothing
 */
#include "include/graph_scale.h"

/**
 * This function initializes a graph scale struct
 * @param     atm - the axis tic marks of the graph scale
 * @param    ca_x - the x coord_axis
 * @param    ca_y - the y coord_axis
 * @param      gb - the border of the graph
 * @param axis_no - how many axes there are, only 2 supported currently
 * @return
 */
graph_scale * init_graph_scale(axis_tic_marks * atm_x, axis_tic_marks * atm_y,
    coord_axis * ca_x, coord_axis * ca_y, graph_border * gb, int axis_no) {
  graph_scale * gs = calloc(1, sizeof(struct GRAPH_SCALE_T));
  gs->atm = calloc(2, sizeof(struct AXIS_TIC_MARKS_T *));
  gs->atm[0] = atm_x;
  gs->atm[1] = atm_y;
  if(axis_no == 2) {
    gs->coord_axes = calloc(2, sizeof(struct COORD_AXIS_T *));
    gs->num = calloc(2, sizeof(struct NUMERIC_T *));
    gs->coord_axes[0] = ca_x;
    gs->coord_axes[1] = ca_y;
  }
  gs->num[0] = make_x_numeric(gs);
  gs->num[1] = make_y_numeric(gs);
  gs->gb = gb;
  gs->axis_no = axis_no;
  return gs;
}

numeric * make_y_numeric(graph_scale * gs) {
  double y_tic_mark_qty =
    ((double)gs->coord_axes[1]->axis_max - (double)gs->coord_axes[1]->axis_min)
    / (double)gs->atm[1]->qty;
  int x_left = (gs->atm[1]->qty / 2 + 0.35) * (GRAPH_DIMS / gs->atm[1]->qty);
  int y_up = (gs->atm[1]->qty / 2 - 1.15) * (GRAPH_DIMS / gs->atm[1]->qty);
  return init_numeric(y_tic_mark_qty, NUMR_HEIGHT, x_left, y_up);
}

numeric * make_x_numeric(graph_scale * gs) {
  double x_tic_mark_qty =
    ((double)gs->coord_axes[0]->axis_max - (double)gs->coord_axes[0]->axis_min)
    / (double)gs->atm[0]->qty;
  int x_left = (gs->atm[0]->qty / 2 + 0.5) * (GRAPH_DIMS / gs->atm[0]->qty);
  int y_up = (gs->atm[0]->qty / 2 + 0.35) * (GRAPH_DIMS / gs->atm[0]->qty);
  return init_numeric(x_tic_mark_qty, NUMR_HEIGHT, x_left, y_up);
}

/**
 * This function writes the graph scale to the provided canvas
 * @param  can - the canvas
 * @param   gs - the graph scale to be written
 * @return N/a
 */
void write_gs_to_canvas(canvas * can, graph_scale * gs) {
  write_atm_to_canvas(can, gs->atm[0]);
  write_atm_to_canvas(can, gs->atm[1]);
  write_ca_to_canvas(can, gs->coord_axes[0]);
  write_ca_to_canvas(can, gs->coord_axes[1]);
  write_numeric_to_canvas(gs->num[0], can);
  write_numeric_to_canvas(gs->num[1], can);
  write_gb_to_canvas(can, gs->gb);
}

/**
 * This function frees a graph scale
 * @param   gs - the graph scale to be freed
 * @return N/a
 */
void free_graph_scale(graph_scale * gs) {
  if(gs) {
    if(gs->atm) {
      for(int i = 0; i < 2; i++)
        free_axis_tic_marks(gs->atm[i]);
      free(gs->atm);
    }
    if(gs->coord_axes) {
      for(int i = 0; i < 2; i++)
        free_coord_axis(gs->coord_axes[i]);
      free(gs->coord_axes);
    }
    if(gs->gb)
      free_graph_border(gs->gb);
    if(gs->num) {
      for(int i = 0; i < 2; i++)
        free_numeric(gs->num[i]);
      free(gs->num);
    }
    free(gs);
  }
}
