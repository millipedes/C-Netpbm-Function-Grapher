/**
 * @file   numerics.c
 * @brief  This file contains the related functions of the numerics to mark axis
 * tic marks
 * @author Matthew C. Lindeman
 * @date   July 01, 2022
 * @bug    None known
 * @todo   Nothing
 */
#define _POSIX_C_SOURCE 200809L
#include "include/numerics.h"

/**
 * This function init
 * @param scale_qty - the quantity of the scale
 * @param    height - the the height of the numeric
 * @param    left_x - the x value of the upper left corner of the numeric string
 * @param      up_y - the y value of the upper left corner of the numeric string
 * @return
 */
numeric * init_numeric(double scale_qty, int height, int left_x, int up_y) {
  numeric * num = calloc(1, sizeof(struct NUMERIC_T));
  char buf[MAX_TOK_LEN];
  sprintf(buf, "%.3f", scale_qty);
  size_t len = strnlen(buf, MAX_TOK_LEN) + 1;
  num->scale_string = calloc(len, sizeof(char));
  strncpy(num->scale_string, buf, len);
  num->numeric_col = init_color(COL_MIN, COL_MIN, COL_MIN);
  num->current_index = 0;
  num->height = height;
  num->width = NUMR_WIDTH;
  num->left_x = left_x;
  num->up_y = up_y;
  return num;
}

/**
 * This function writes the numeric to the given canvas
 * @param  num - the numeric to be written
 * @param  can - the canvas to write to
 * @return N/a
 */
void write_numeric_to_canvas(numeric * num, canvas * can) {
  size_t len = strnlen(num->scale_string, MAX_TOK_LEN);
  for(int i = 0; i < (int)len; i++) {
    switch(num->scale_string[i]) {
      case '0':
        write_zero_to_canvas(num, can);
        break;
      case '1':
        write_one_to_canvas(num, can);
        break;
      case '2':
        write_two_to_canvas(num, can);
        break;
      case '3':
        write_three_to_canvas(num, can);
        break;
      case '4':
        write_four_to_canvas(num, can);
        break;
      case '5':
        write_five_to_canvas(num, can);
        break;
      case '6':
        write_six_to_canvas(num, can);
        break;
      case '7':
        write_seven_to_canvas(num, can);
        break;
      case '8':
        write_eight_to_canvas(num, can);
        break;
      case '9':
        write_nine_to_canvas(num, can);
        break;
      case '.':
        write_period_to_canvas(num, can);
        break;
    }
    num->left_x += num->width / 2; // The space between numbers
    num->current_index++;
  }
}

/**
 * This function writes a zero to a canvas
 * @param  num - the numeric from which the period comes from
 * @param  can - the canvas to be written to
 * @return N/a
 */
void write_zero_to_canvas(numeric * num, canvas * can) {
  double all_rect_height = num->height / 3;
  double current_rect_y = num->up_y;
  double x = num->left_x + num->width * num->current_index;
  // Top
  write_wide_rect(can, num, all_rect_height, current_rect_y);
  current_rect_y += all_rect_height;
  // Left Intermediate Rectangle
  write_third_rect(can, num, all_rect_height, x, current_rect_y);
  // Right Intermediate Rectangle
  write_third_rect(can, num, all_rect_height, x + 2 * (num->width / 3),
      current_rect_y);
  current_rect_y += all_rect_height;
  write_wide_rect(can, num, all_rect_height, current_rect_y);
}

/**
 * This function writes a rectangle that is a width 1/3 of the total numeric
 * width with the given parameters
 * @param    num - the numeric from which the period comes from
 * @param    can - the canvas to be written to
 * @param height - the height of the rectangle
 * @param      x - the leftmost x value of the rectangle
 * @param      y - the uppermost y value of the rectangle
 * @return   N/a
 */
void write_third_rect(canvas * can, numeric * num, double height, double x,
    double y) {
  double inter_rect_width = ceil((double)num->width / 3.0);
  write_rectangle_from_ul(
      can,               // Canvas
      x,
      y,                 // uppermost start
      height,            // Height
      inter_rect_width,  // width
      num->numeric_col   // Color (always black)
      );
}

/**
 * This function writes a rectangle that is the width of the numeric with the
 * given parameters
 * @param    num - the numeric from which the period comes from
 * @param    can - the canvas to be written to
 * @param height - the height of the rectangle
 * @param      y - the uppermost y value of the rectangle
 * @return   N/a
 */
void write_wide_rect(canvas * can, numeric * num, double height, double y) {
  write_rectangle_from_ul(
      can,                 // Canvas
      num->left_x + num->width * num->current_index, // leftmost start
      y,                   // uppermost start
      height,              // Height
      num->width,          // width
      num->numeric_col     // Color (always black)
      );
}

/**
 * This function writes a one to a canvas
 * @param  num - the numeric from which the period comes from
 * @param  can - the canvas to be written to
 * @return N/a
 */
void write_one_to_canvas(numeric * num, canvas * can) {
  write_rectangle_from_ul(
      can,                                           // Canvas
      num->left_x + num->width * num->current_index, // leftmost start
      num->up_y,                                     // uppermost start
      num->height,                                   // Height
      num->width / 2,                                // width
      num->numeric_col                               // Color (always black)
      );
}

/**
 * This function writes a two to a canvas
 * @param  num - the numeric from which the period comes from
 * @param  can - the canvas to be written to
 * @return N/a
 */
void write_two_to_canvas(numeric * num, canvas * can) {
  double all_rect_height = num->height / 5;
  double current_rect_y = num->up_y;
  double x = num->left_x + num->width * num->current_index;
  // Top Rectangle
  write_wide_rect(can, num, all_rect_height, current_rect_y);
  current_rect_y += all_rect_height;
  // Top Intermediate Rectangle
  write_third_rect(can, num, all_rect_height, x + 2 * (num->width / 3),
      current_rect_y);
  current_rect_y += all_rect_height;
  // Middle Rectangle
  write_wide_rect(can, num, all_rect_height, current_rect_y);
  current_rect_y += all_rect_height;
  // Bottom Intermediate Rectangle
  write_third_rect(can, num, all_rect_height, x, current_rect_y);
  current_rect_y += all_rect_height;
  // Bottom Rectangle
  write_wide_rect(can, num, all_rect_height, current_rect_y);
}

/**
 * This function writes a three to a canvas
 * @param  num - the numeric from which the period comes from
 * @param  can - the canvas to be written to
 * @return N/a
 */
void write_three_to_canvas(numeric * num, canvas * can) {
  double all_rect_height = num->height / 5;
  double current_rect_y = num->up_y;
  double x = num->left_x + num->width * num->current_index;
  // Top Rectangle
  write_wide_rect(can, num, all_rect_height, current_rect_y);
  current_rect_y += all_rect_height;
  // Top Intermediate Rectangle
  write_third_rect(can, num, all_rect_height, x + 2 * (num->width / 3),
      current_rect_y);
  current_rect_y += all_rect_height;
  // Middle Rectangle
  write_wide_rect(can, num, all_rect_height, current_rect_y);
  current_rect_y += all_rect_height;
  // Bottom Intermediate Rectangle
  write_third_rect(can, num, all_rect_height, x + 2 * (num->width / 3),
      current_rect_y);
  current_rect_y += all_rect_height;
  // Bottom Rectangle
  write_wide_rect(can, num, all_rect_height, current_rect_y);
}

/**
 * This function writes a four to a canvas
 * @param  num - the numeric from which the period comes from
 * @param  can - the canvas to be written to
 * @return N/a
 */
void write_four_to_canvas(numeric * num, canvas * can) {
  double all_rect_height = num->height / 3;
  double inter_rect_width = (double)num->width / 3.0;
  double current_rect_y = num->up_y;
  // Top Intermediate Rectangle
  write_rectangle_from_ul(
      can,                                           // Canvas
      num->left_x + num->width * num->current_index,
      current_rect_y,                                // uppermost start
      all_rect_height,                               // Height
      ceil(inter_rect_width),                        // width
      num->numeric_col                               // Color (always black)
      );
  // Top Intermediate Rectangle
  write_rectangle_from_ul(
      can,                                           // Canvas
      num->left_x + num->width * num->current_index + 2 * (num->width / 3),
      current_rect_y,                                // uppermost start
      all_rect_height,                               // Height
      ceil(inter_rect_width),                        // width
      num->numeric_col                               // Color (always black)
      );
  current_rect_y += all_rect_height;
  // Middle Rectangle
  write_rectangle_from_ul(
      can,                                           // Canvas
      num->left_x + num->width * num->current_index, // leftmost start
      current_rect_y,                                // uppermost start
      all_rect_height,                               // Height
      num->width,                                    // width
      num->numeric_col                               // Color (always black)
      );
  current_rect_y += all_rect_height;
  // Bottom Intermediate Rectangle
  write_rectangle_from_ul(
      can,                                           // Canvas
      num->left_x + num->width * num->current_index + 2 * (num->width / 3),
      current_rect_y,                                // uppermost start
      all_rect_height,                               // Height
      ceil(inter_rect_width),                        // width
      num->numeric_col                               // Color (always black)
      );
}

/**
 * This function writes a five to a canvas
 * @param  num - the numeric from which the period comes from
 * @param  can - the canvas to be written to
 * @return N/a
 */
void write_five_to_canvas(numeric * num, canvas * can) {
  double all_rect_height = num->height / 5;
  double current_rect_y = num->up_y;
  double x = num->left_x + num->width * num->current_index;
  // Top Rectangle
  write_wide_rect(can, num, all_rect_height, current_rect_y);
  current_rect_y += all_rect_height;
  // Top Intermediate Rectangle
  write_third_rect(can, num, all_rect_height, x, current_rect_y);
  current_rect_y += all_rect_height;
  // Middle Rectangle
  write_wide_rect(can, num, all_rect_height, current_rect_y);
  current_rect_y += all_rect_height;
  // Bottom Intermediate Rectangle
  write_third_rect(can, num, all_rect_height, x + 2 * (num->width / 3),
      current_rect_y);
  current_rect_y += all_rect_height;
  // Bottom Rectangle
  write_wide_rect(can, num, all_rect_height, current_rect_y);
}

/**
 * This function writes a six to a canvas
 * @param  num - the numeric from which the period comes from
 * @param  can - the canvas to be written to
 * @return N/a
 */
void write_six_to_canvas(numeric * num, canvas * can) {
  double all_rect_height = num->height / 5;
  double current_rect_y = num->up_y;
  double x = num->left_x + num->width * num->current_index;
  // Top Rectangle
  write_wide_rect(can, num, all_rect_height, current_rect_y);
  current_rect_y += all_rect_height;
  // Top Intermediate Rectangle
  write_third_rect(can, num, all_rect_height, x, current_rect_y);
  current_rect_y += all_rect_height;
  // Middle Rectangle
  write_wide_rect(can, num, all_rect_height, current_rect_y);
  current_rect_y += all_rect_height;
  // Bottom Left Intermediate Rectangle
  write_third_rect(can, num, all_rect_height, x, current_rect_y);
  // Bottom Right Intermediate Rectangle
  write_third_rect(can, num, all_rect_height, x + 2 * (num->width / 3),
      current_rect_y);
  current_rect_y += all_rect_height;
  // Bottom Rectangle
  write_wide_rect(can, num, all_rect_height, current_rect_y);
}

/**
 * This function writes a seven to a canvas
 * @param  num - the numeric from which the period comes from
 * @param  can - the canvas to be written to
 * @return N/a
 */
void write_seven_to_canvas(numeric * num, canvas * can) {
  double all_rect_height = num->height / 5;
  double current_rect_y = num->up_y;
  double x = num->left_x + num->width * num->current_index;
  // Top Rectangle
  write_wide_rect(can, num, all_rect_height, current_rect_y);
  current_rect_y += all_rect_height;
  // Stem of 7 Rectangle
  write_third_rect(can, num, all_rect_height * 4, x + 2 * (num->width / 3),
      current_rect_y);
}

/**
 * This function writes an eight to a canvas
 * @param  num - the numeric from which the period comes from
 * @param  can - the canvas to be written to
 * @return N/a
 */
void write_eight_to_canvas(numeric * num, canvas * can) {
  double all_rect_height = num->height / 5;
  double current_rect_y = num->up_y;
  double x = num->left_x + num->width * num->current_index;
  // Top Rectangle
  write_wide_rect(can, num, all_rect_height, current_rect_y);
  current_rect_y += all_rect_height;
  // Top Intermediate Left Rectangle
  write_third_rect(can, num, all_rect_height, x, current_rect_y);
  // Top Intermediate Right Rectangle
  write_third_rect(can, num, all_rect_height, x + 2 * (num->width / 3),
      current_rect_y);
  current_rect_y += all_rect_height;
  // Middle Rectangle
  write_wide_rect(can, num, all_rect_height, current_rect_y);
  current_rect_y += all_rect_height;
  // Bottom Intermediate Left Rectangle
  write_third_rect(can, num, all_rect_height, x, current_rect_y);
  // Bottom Intermediate Right Rectangle
  write_third_rect(can, num, all_rect_height, x + 2 * (num->width / 3),
      current_rect_y);
  current_rect_y += all_rect_height;
  // Bottom Rectangle
  write_wide_rect(can, num, all_rect_height, current_rect_y);
}

/**
 * This function writes a nine to a canvas
 * @param  num - the numeric from which the period comes from
 * @param  can - the canvas to be written to
 * @return N/a
 */
void write_nine_to_canvas(numeric * num, canvas * can) {
  double all_rect_height = num->height / 5;
  double current_rect_y = num->up_y;
  double x = num->left_x + num->width * num->current_index;
  // Top Rectangle
  write_wide_rect(can, num, all_rect_height, current_rect_y);
  current_rect_y += all_rect_height;
  // Intermediate Left Rectangle
  write_third_rect(can, num, all_rect_height, x, current_rect_y);
  // Intermediate Right Rectangle
  write_third_rect(can, num, all_rect_height, x + 2 * (num->width / 3),
      current_rect_y);
  current_rect_y += all_rect_height;
  // Middle Rectangle
  write_wide_rect(can, num, all_rect_height, current_rect_y);
  current_rect_y += all_rect_height;
  // Bottom Intermediate Rectangle
  write_third_rect(can, num, all_rect_height, x + 2 * (num->width / 3),
      current_rect_y);
  current_rect_y += all_rect_height;
  // Bottom Rectangle
  write_wide_rect(can, num, all_rect_height, current_rect_y);
}

/**
 * This function writes a period to a canvas
 * @param  num - the numeric from which the period comes from
 * @param  can - the canvas to be written to
 * @return N/a
 */
void write_period_to_canvas(numeric * num, canvas * can) {
  double start_y = ceil(5.0 * (double)num->height / 6.0);
  double height = ceil((double)num->height / 6.0);
  write_rectangle_from_ul(
      can,                                           // Canvas
      num->left_x + num->width * num->current_index, // leftmost start
      num->up_y + start_y,                           // uppermost start
      height,                                        // Height
      height,                                        // width
      num->numeric_col                               // Color (always black)
      );
}

/**
 * This function is used in debugging a numeric
 * @param  num - the numeric to be debugged
 * @return N/a
 */
void numeric_dump_debug(numeric * num) {
  printf("Numeric:\n");
  printf("Scale String: `%s`\n", num->scale_string);
  printf("Current Index: %d\n", num->current_index);
  printf("Height: %d\n", num->height);
  printf("Width: %d\n", num->width);
  printf("Upper Left Corner Coords: (%d, %d)\n", num->left_x, num->up_y);
  color_dump_debug(num->numeric_col);
}

/**
 * This function frees a given numeric
 * @param  num - the numeric
 * @return N/a
 */
void free_numeric(numeric * num) {
  if(num) {
    if(num->scale_string)
      free(num->scale_string);
    if(num->numeric_col)
      free_color(num->numeric_col);
    free(num);
  }
}
