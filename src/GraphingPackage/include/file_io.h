/**
 * @file   file_io.h
 * @brief  this file contains the function definitions for file_io.c
 * @author Matthew C. Lindeman
 * @date   June 18, 2022
 * @bug    None known
 * @todo   Nothing
 */
#ifndef FIO_H
#define FIO_H

#include "relation.h"
#include "../../main/include/constants.h"
#include "../../FunctionCFG/Lexer/include/lexer.h"
#include "../../FunctionCFG/Parser/include/parser.h"
#include "../../GraphingPackage/GraphPresets/include/graph_scale.h"

void write_canvas_to_file(char * file_name, canvas * can);
void write_output_headings(FILE * fp, canvas * can);

void write_outputs_from_input_cfg_file(char * file_name);
void proc_new_line(char buf[], lexer ** lex, token_stack ** rev,
    FILE * input_fp, token_stack ** tok_list);
int get_mins_maxes(char * xymin_max, token_stack ** ts);
void clean_lexer_token_stack(lexer ** lex, token_stack ** rev);



#endif
