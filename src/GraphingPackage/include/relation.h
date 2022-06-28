/**
 * @file   relation.h
 * @brief  this file contains the function definitions for relation.c
 * @author Matthew C. Lindeman
 * @date   June 17, 2022
 * @bug    None known
 * @todo   Nothing
 */
#ifndef REL_H
#define REL_H

#include "../../FunctionCFG/Parser/include/parser.h"
#include "../../GraphingPackage/GraphPresets/include/graph_scale.h"
#include "../../GraphingPackage/include/color.h"

void write_rel_to_canvas(canvas * can, graph_scale * gs, double rel(double),
    color * col, double delta);
void write_ast_to_canvas(canvas * can, graph_scale * gs, ast * abstree,
    color * col, double delta);
int map_scale_to_canvas(canvas * can, graph_scale * gs, axis ax, double qty);

#endif
