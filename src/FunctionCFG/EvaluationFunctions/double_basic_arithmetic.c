/**
 * @file    double_basic_arithmetic.c
 * @brief   this file contains basic functions to help in the evaluation of
 * abstract syntax trees with respect to those values which are doubles
 * @author  Matthew C. Lindeman
 * @date    June 28, 2022
 * @bug     None known
 * @todo    Nothing
 */
#include "include/double_basic_arithmetic.h"

/**
 * The addition function. Returns term 1 added by term 2.
 * @param  t1 - the first term (numerator)
 * @param  t2 - the second term (denominator)
 * @return .\ - the result of the addition.
 */
double addition(double t1, double t2) {
  return t1 + t2;
}

/**
 * The subtration function. Returns term 1 subtracted by term 2.
 * @param  t1 - the first term (numerator)
 * @param  t2 - the second term (denominator)
 * @return .\ - the result of the subtration.
 */
double subtraction(double t1, double t2) {
  return t1 - t2;
}

/**
 * The multiplication function. Returns term 1 multiplied by term 2.
 * @param  t1 - the first term (numerator)
 * @param  t2 - the second term (denominator)
 * @return .\ - the result of the multiplication.
 */
double multiplication(double t1, double t2) {
  return t1 * t2;
}

/**
 * The division function. Returns term 1 divided by term 2.
 * @param  t1 - the first term (numerator)
 * @param  t2 - the second term (denominator)
 * @return .\ - the result of the division.
 */
double division(double t1, double t2) {
  return t1 / t2;
}
