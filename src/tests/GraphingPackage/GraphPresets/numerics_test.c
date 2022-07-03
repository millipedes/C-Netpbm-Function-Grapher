/**
 * @file   numerics_test.c
 * @brief  This file contains functions testing the 
 * @author Matthew C. Lindeman
 * @date 
 * @bug None known
 * @todo Nothing
 */
#include "include/numerics_test.h"

/**
 * This function is used in testing the numerics functions
 * @param  N/a
 * @return N/a
 */
void numerics_test(void) {
  canvas * can = init_canvas(1000, 1000);
  numeric * num1 = init_numeric(2.13, 50, 100, 100);
  write_numeric_to_canvas(num1, can);
  numeric * num2 = init_numeric(2.15, 30, 200, 200);
  write_numeric_to_canvas(num2, can);
  numeric * num3 = init_numeric(2.1, 90, 300, 300);
  write_numeric_to_canvas(num3, can);
  write_canvas_to_file("test.ppm", can);
  free_canvas(can);
  free_numeric(num1);
  free_numeric(num2);
  free_numeric(num3);
}
