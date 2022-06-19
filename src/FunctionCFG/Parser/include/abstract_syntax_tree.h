/**
 * @file ast.c
 * @brief This file contains the function definitions for ast.c
 * @author Matthew C. Lindeman
 * @date May 26, 2022
 * @bug None known
 * @todo Nothing
 */
#ifndef AST_H
#define AST_H

#include "../../Token/include/token.h"

typedef struct AST_T {
  token * value;
  struct AST_T ** children;
  int no_children;
} ast;

ast * init_ast(char * t_literal, token_type type);
void ast_dump_debug(ast * abstree);
void free_ast(ast * abstree);

#endif
