/**
 * @file   user_out_file.h
 * @brief  This file contains the function definitions for user_out_file.c
 * @author Matthew C. Lindeman
 * @date   July 09, 2022
 * @bug    None known
 * @todo   Nothing
 */
#ifndef UOF_H
#define UOF_H

#include "../../main/include/constants.h"
#include "../../FunctionCFG/Lexer/include/lexer.h"
#include "../../FunctionCFG/Parser/include/parser.h"
#include "../../GraphingPackage/GraphPresets/include/graph_scale.h"

/**
 * This data structure is used to get the custom parameters to be used in a user
 * output file from the user input file to the program.
 */
typedef struct USER_OUT_FILE_T {
  /** The functions to be plotted */
  ast ** functions;
  /** The colors of the functions to be plotted */
  color ** func_colors;
  /** The output file name */
  char * file_name;
  /** The quantity of functions */
  int qty_functions;
  /** The quantity of colors */
  int qty_colors;
  /** The minimum x value of the graph */
  double x_min;
  /** The minimum y value of the graph */
  double y_min;
  /** The maximum x value of the graph */
  double x_max;
  /** The maximum y value of the graph */
  double y_max;
  /** The dimensions of resulting canvas in pixels */
  int canvas_dims;
  /** The quantity of tic marks to be displayed */
  int qty_tic_marks;
  /** The small dimension of tic marks in pixels */ 
  int graph_tic_mark_small;
  /** The large dimension of tic marks in pixels */
  int graph_tic_mark_large;
  /** The graph border width in pixels */
  int graph_border;
}user_out_file;

user_out_file * init_user_output_file(void);
user_out_file * process_file_heading(token_stack ** ts);
void process_func_section(char buf[], lexer ** lex, token_stack ** rev,
    token_stack ** tok_list, FILE * input_fp, user_out_file * user_of);
void process_color(user_out_file * user_of, token_stack ** ts, lexer ** lex);
void process_min_maxes(user_out_file * user_of, token_stack ** ts,
    lexer ** lex);
void process_canvas_dims(user_out_file * user_of, token_stack ** ts,
    lexer ** lex);
void process_qty_tic_marks(user_out_file * user_of, token_stack ** ts,
    lexer ** lex);
void process_tic_marks_small(user_out_file * user_of, token_stack ** ts,
    lexer ** lex);
void process_tic_marks_large(user_out_file * user_of, token_stack ** ts,
    lexer ** lex);
void process_graph_border(user_out_file * user_of, token_stack ** ts,
    lexer ** lex);
void user_out_file_dump_debug(user_out_file * user_of);
void free_user_out_file(user_out_file * user_of);

void proc_new_line(char buf[], lexer ** lex, token_stack ** rev,
    FILE * input_fp, token_stack ** tok_list);
void clean_lexer_token_stack(lexer ** lex, token_stack ** rev);

#endif
