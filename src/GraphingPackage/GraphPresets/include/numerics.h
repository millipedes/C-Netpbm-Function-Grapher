#ifndef NUMR_H
#define NUMR_H

#include <string.h>
#include <math.h>
#include "../../GraphEncoding/include/canvas.h"
#include "../../../main/include/constants.h"

typedef struct NUMERIC_T {
  char * scale_string;
  color * numeric_col;
  int current_index;
  int height;
  int width;
  int left_x;
  int up_y;
} numeric;

numeric * init_numeric(double scale_qty, int height, int x_left, int y_up);
void write_numeric_to_canvas(numeric * num, canvas * can);
void write_third_rect(canvas * can, numeric * num, double height, double x,
    double y);
void write_wide_rect(canvas * can, numeric * num, double height, double y);
void write_zero_to_canvas(numeric * num, canvas * can);
void write_one_to_canvas(numeric * num, canvas * can);
void write_two_to_canvas(numeric * num, canvas * can);
void write_three_to_canvas(numeric * num, canvas * can);
void write_four_to_canvas(numeric * num, canvas * can);
void write_five_to_canvas(numeric * num, canvas * can);
void write_six_to_canvas(numeric * num, canvas * can);
void write_seven_to_canvas(numeric * num, canvas * can);
void write_eight_to_canvas(numeric * num, canvas * can);
void write_nine_to_canvas(numeric * num, canvas * can);
void write_period_to_canvas(numeric * num, canvas * can);
void numeric_dump_debug(numeric * num);
void free_numeric(numeric * num);

#endif
