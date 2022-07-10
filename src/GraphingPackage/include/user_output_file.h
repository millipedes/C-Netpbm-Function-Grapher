#ifndef UOF_H
#define UOF_H

#include "../../main/include/constants.h"
#include "../../FunctionCFG/Lexer/include/lexer.h"
#include "../../FunctionCFG/Parser/include/parser.h"
#include "../../GraphingPackage/GraphPresets/include/graph_scale.h"

typedef struct USER_OUT_FILE_T {
  ast ** functions;
  color ** func_colors;
  char * file_name;
  int qty_functions;
  int qty_colors;
  double x_min;
  double y_min;
  double x_max;
  double y_max;
  int canvas_dims;
  int qty_tic_marks;
  int graph_tic_mark_small;
  int graph_tic_mark_large;
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
void process_numer_height(user_out_file * user_of, token_stack ** ts,
    lexer ** lex);
void process_numer_width(user_out_file * user_of, token_stack ** ts,
    lexer ** lex);
void user_out_file_dump_debug(user_out_file * user_of);
void free_user_out_file(user_out_file * user_of);

void proc_new_line(char buf[], lexer ** lex, token_stack ** rev,
    FILE * input_fp, token_stack ** tok_list);
void clean_lexer_token_stack(lexer ** lex, token_stack ** rev);

#endif
