#include "include/graph_scale.h"

graph_scale * init_graph_scale(axis_tic_marks * atm, coord_axis * ca_x,
    coord_axis * ca_y, graph_border * gb, int axis_no) {
  graph_scale * gs = calloc(1, sizeof(struct GRAPH_SCALE_T));
  gs->atm = atm;
  if(axis_no == 2) {
    gs->coord_axes = calloc(2, sizeof(struct COORD_AXIS_T *));
    gs->coord_axes[0] = ca_x;
    gs->coord_axes[1] = ca_y;
  }
  gs->gb = gb;
  gs->axis_no = axis_no;
  return gs;
}

void write_gs_to_canvas(canvas * can, graph_scale * gs) {
  write_atm_to_canvas(can, gs->atm);
  write_ca_to_canvas(can, gs->coord_axes[0]);
  write_ca_to_canvas(can, gs->coord_axes[1]);
  write_gb_to_canvas(can, gs->gb);
}

void free_graph_scale(graph_scale * gs) {
  if(gs) {
    if(gs->atm)
      free_axis_tic_marks(gs->atm);
    if(gs->coord_axes) {
      for(int i = 0; i < 2; i++)
        free_coord_axis(gs->coord_axes[i]);
      free(gs->coord_axes);
    }
    if(gs->gb)
      free_graph_border(gs->gb);
    free(gs);
  }
} 
