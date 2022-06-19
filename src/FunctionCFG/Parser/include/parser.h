/**
 * @file   parser.h
 * @brief  This file contains the function definitions for parser.c
 * @author Matthew C. Lindeman
 * @date   June 19, 2022
 * @bug    None known
 * @todo   Nothing
 */
#ifndef PAR_H
#define PAR_H

#include "abstract_syntax_tree.h"

ast * parse_expression(token ** tok_list, int * index);
ast * parse_factor(token ** tok_list, int * index);
ast * binary_tree(ast * parent, ast * left_child, ast * right_child);
ast * unary_tree(ast * parent, ast * child);

#endif
