/**
 * @file   ast.c
 * @brief  This file contains the function definitions for ast.c
 * @author Matthew C. Lindeman
 * @date   May 26, 2022
 * @bug    None known
 * @todo   Nothing
 */
#ifndef AST_H
#define AST_H

#include "../../Token/include/token_stack.h"

/**
 * This data structure is used to represent functions. It is a standard abstract
 * syntax tree with only double values (as we are dealing with funcitons). There
 * are no explicit nodes.
 */
typedef struct AST_T {
  /** The token representing the value */
  token * value;
  /** The children of the current node */
  struct AST_T ** children;
  /** The numeric value of the current node */
  double numeric_value;
  /** The number of children of the current node */
  int no_children;
} ast;

ast * init_ast(char * t_literal, token_type type);
void ast_pretty_print(ast * abstree);
void ast_dump_debug(ast * abstree);
void free_ast(ast * abstree);
void ast_print_expression(ast * abstree);
void decrement_number_ast(ast * abstree);

#endif
