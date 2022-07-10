/**
 * @file   user_out_file.c
 * @brief  This file contains the customizable data structures for the output
 * graph file
 * @author Matthew C. Lindeman
 * @date   July 09, 2022
 * @bug    None known
 * @todo   Nothing
 */
#define _POSIX_C_SOURCE 200809L
#include "include/user_output_file.h"

/**
 * This function initializes a user_out_file data structure.  This data
 * structure is initialized to be the default settings but based on user input
 * file the values will change before the file is written
 * @param      N/a
 * @return user_of - the newly created user_output_file
 */
user_out_file * init_user_output_file(void) {
  user_out_file * user_of = calloc(1, sizeof(struct USER_OUT_FILE_T));
  user_of->file_name = NULL;
  user_of->functions = NULL;
  user_of->func_colors = NULL;
  user_of->qty_functions = 0;
  user_of->qty_colors = 0;
  user_of->x_min = -10;
  user_of->y_min = -10; 
  user_of->x_max = 10;
  user_of->y_max = 10;
  user_of->canvas_dims = GRAPH_DIMS;
  user_of->graph_tic_mark_small = GPRAH_TIC_SMALL;
  user_of->graph_tic_mark_large = GPRAH_TIC_LARGE;
  user_of->qty_tic_marks  = QTY_TIC_MARKS;
  user_of->graph_border = GRAPH_BORDER;
  return user_of;
}

/**
 * This function reads a function heading then makes a new user_output_file and
 * initializes the file_name attribute from it
 * @param       ts - the token stack from which the file name comes from
 * @return user_of - the newly initialized user_out_file
 */
user_out_file * process_file_heading(token_stack ** ts) {
  user_out_file * user_of = init_user_output_file();
  ts[0] = pop_token(ts[0]);
  size_t len = strnlen(ts[0]->current->t_literal, MAX_TOK_LEN) + 1;
  user_of->file_name = calloc(len, sizeof(char));
  strncpy(user_of->file_name, ts[0]->current->t_literal, len);
  return user_of;
}

/**
 * This function processes a function block in a user input file (i.e. a block
 * that is prefaced by "FUNC" and postfixed with "END"
 * @param      buf - a user input buffer used as default data storage from the
 * fp
 * @param      lex - the lexer usered to process user input file
 * @param      rev - the token_stack that the lexer writes to (by reverseing
 * tok_list)
 * @param tok_list - a list that the lexer writes into then is reversed and
 * stored in rev
 * @param input_fp - the input file from which the block is reading
 * @param  user_of - the data structure to record the information in
 * @return     N/a
 */
void process_func_section(char buf[], lexer ** lex, token_stack ** rev,
    token_stack ** tok_list, FILE * input_fp, user_out_file * user_of) {
  clean_lexer_token_stack(lex, rev);
  proc_new_line(buf, lex, rev, input_fp, tok_list);
  while(strncmp(rev[0]->current->t_literal, "END", MAX_TOK_LEN)) {
    user_of->qty_functions++;
    if(!user_of->functions)
      user_of->functions = calloc(user_of->qty_functions, sizeof(struct AST_T *));
    else
      user_of->functions = realloc(user_of->functions,
          user_of->qty_functions * sizeof(struct AST_T *));
    user_of->functions[user_of->qty_functions - 1] = parse_expression(rev);
    clean_lexer_token_stack(lex, rev);
    proc_new_line(buf, lex, rev, input_fp, tok_list);
  }
  clean_lexer_token_stack(lex, rev);
}

/**
 * This function processes a color user input
 * @param user_of - the data structure to record the information in
 * @param      ts - the token stack from which the information will be read
 * @param     lex - the lexer is freed in all processing functions (not
 * explicitly mentioned in functions because functions is a block while others
 * are not)
 * @return    N/a
 */
void process_color(user_out_file * user_of, token_stack ** ts, lexer ** lex) {
  ts[0] = pop_token(ts[0]);
  int r = 0;
  int g = 0;
  int b = 0;
  r = atoi(ts[0]->current->t_literal);
  ts[0] = pop_token(ts[0]); // R val
  ts[0] = pop_token(ts[0]); // Comma
  g = atoi(ts[0]->current->t_literal);
  ts[0] = pop_token(ts[0]); // G val
  ts[0] = pop_token(ts[0]); // Comma
  b = atoi(ts[0]->current->t_literal);
  user_of->qty_colors++;
  if(!user_of->func_colors)
    user_of->func_colors = calloc(user_of->qty_colors,
        sizeof(struct COLOR_T *));
  else
    user_of->func_colors = realloc(user_of->func_colors,
        user_of->qty_colors * sizeof(struct COLOR_T *));
  user_of->func_colors[user_of->qty_colors - 1] = init_color(r, g, b);
  clean_lexer_token_stack(lex, ts);
}

/**
 * This function will process: (x|y)_(min|max).
 * @param user_of - the data structure in which the evidence is stored
 * @param      ts - the token stack to be read from 
 * @param     lex - the lexer is freed in all process functions
 * @return    N/a
 */
void process_min_maxes(user_out_file * user_of, token_stack ** ts,
    lexer ** lex) {
  if(!strncmp(ts[0]->current->t_literal, "X_MIN", MAX_TOK_LEN)) {
    ts[0] = pop_token(ts[0]);
    if(ts[0]->current->type == TOKEN_MINUS) {
      ts[0] = pop_token(ts[0]);
      user_of->x_min = -atof(ts[0]->current->t_literal);
    } else 
      user_of->x_min = atof(ts[0]->current->t_literal);
  } else if(!strncmp(ts[0]->current->t_literal, "X_MAX", MAX_TOK_LEN)) {
    ts[0] = pop_token(ts[0]);
    if(ts[0]->current->type == TOKEN_MINUS) {
      ts[0] = pop_token(ts[0]);
      user_of->x_max = -atof(ts[0]->current->t_literal);
    } else 
      user_of->x_max = atof(ts[0]->current->t_literal);
  } else if(!strncmp(ts[0]->current->t_literal, "Y_MIN", MAX_TOK_LEN)) {
    ts[0] = pop_token(ts[0]);
    if(ts[0]->current->type == TOKEN_MINUS) {
      ts[0] = pop_token(ts[0]);
      user_of->y_min = -atof(ts[0]->current->t_literal);
    } else 
      user_of->y_min = atof(ts[0]->current->t_literal);
  } else if(!strncmp(ts[0]->current->t_literal, "Y_MAX", MAX_TOK_LEN)) {
    ts[0] = pop_token(ts[0]);
    if(ts[0]->current->type == TOKEN_MINUS) {
      ts[0] = pop_token(ts[0]);
      user_of->y_max = -atof(ts[0]->current->t_literal);
    } else 
      user_of->y_max = atof(ts[0]->current->t_literal);
  }
  clean_lexer_token_stack(lex, ts);
}

/**
 * This function will process the canvas_dims (i.e. the side length of the
 * resulting square image).
 * @param user_of - The data structure in which information will be stored
 * @param      ts - The token_stack from which the infomation is read
 * @param     lex - The lexer is freed in all process funtions
 * @return    N/a
 */
void process_canvas_dims(user_out_file * user_of, token_stack ** ts,
    lexer ** lex) {
  ts[0] = pop_token(ts[0]);
  user_of->canvas_dims = atoi(ts[0]->current->t_literal);
  clean_lexer_token_stack(lex, ts);
}

/**
 * This function will process the quantity of tic marks to be displayed on each
 * axis
 * @param user_of - The data structure in which information will be stored
 * @param      ts - The token_stack from which the infomation is read
 * @param     lex - The lexer is freed in all process funtions
 * @return    N/a
 */
void process_qty_tic_marks(user_out_file * user_of, token_stack ** ts,
    lexer ** lex) {
  ts[0] = pop_token(ts[0]);
  user_of->qty_tic_marks = atoi(ts[0]->current->t_literal);
  clean_lexer_token_stack(lex, ts);
}

/**
 * This function will process the small dimension of the tic marks (i.e. height
 * of y axis tic marks and width of x axis tic marks)
 * @param user_of - The data structure in which information will be stored
 * @param      ts - The token_stack from which the infomation is read
 * @param     lex - The lexer is freed in all process funtions
 * @return    N/a
 */
void process_tic_marks_small(user_out_file * user_of, token_stack ** ts,
    lexer ** lex) {
  ts[0] = pop_token(ts[0]);
  user_of->graph_tic_mark_small = atoi(ts[0]->current->t_literal);
  clean_lexer_token_stack(lex, ts);
}

/**
 * This function will process the large dimension of the tic marks (i.e. width
 * of y axis tic marks and height of x axis tic marks)
 * @param user_of - The data structure in which information will be stored
 * @param      ts - The token_stack from which the infomation is read
 * @param     lex - The lexer is freed in all process funtions
 * @return    N/a
 */
void process_tic_marks_large(user_out_file * user_of, token_stack ** ts,
    lexer ** lex) {
  ts[0] = pop_token(ts[0]);
  user_of->graph_tic_mark_large = atoi(ts[0]->current->t_literal);
  clean_lexer_token_stack(lex, ts);
}

/**
 * This function will process the width of the graph border (which can be 0)
 * @param user_of - The data structure in which information will be stored
 * @param      ts - The token_stack from which the infomation is read
 * @param     lex - The lexer is freed in all process funtions
 * @return    N/a
 */
void process_graph_border(user_out_file * user_of, token_stack ** ts,
    lexer ** lex) {
  ts[0] = pop_token(ts[0]);
  user_of->graph_border = atoi(ts[0]->current->t_literal);
  clean_lexer_token_stack(lex, ts);
}

/**
 * This function is used for debugging the user_out_file data structure
 * @param user_of - the user_out_file data structure to be debugged
 * @return
 */
void user_out_file_dump_debug(user_out_file * user_of) {
  for(int i = 0; i < user_of->qty_functions; i++)
    ast_dump_debug(user_of->functions[i]);
  for(int i = 0; i < user_of->qty_colors; i++)
    color_dump_debug(user_of->func_colors[i]);
  if(user_of->file_name)
    printf("output file name: `%s`\n", user_of->file_name);
  printf("qty_functions: %d\n", user_of->qty_functions);
  printf("qty_colors: %d\n", user_of->qty_colors);
  printf("x_min: %f\n", user_of->x_min);
  printf("y_min: %f\n", user_of->y_min);
  printf("x_max: %f\n", user_of->x_max);
  printf("y_max: %f\n", user_of->y_max);
  printf("canvas_dims: %d\n", user_of->canvas_dims);
  printf("qty_tic_marks: %d\n", user_of->qty_tic_marks);
  printf("graph_tic_mark_small: %d\n", user_of->graph_tic_mark_small);
  printf("graph_tic_mark_large: %d\n", user_of->graph_tic_mark_large);
  printf("graph_border: %d\n", user_of->graph_border);
}

/**
 * This function processes a new line. Since we are modifying addresses to do
 * this with some data sctructures, they are double pointers
 * @param      buf - the input buffer to read into
 * @param      lex - the lexer to read into
 * @param      rev - the token_stack to read into
 * @param input_fp - the input file pointer
 * @param tok_list - the token_stack read into by lexer then reversed in rev
 * @return     N/a
 */
void proc_new_line(char buf[], lexer ** lex, token_stack ** rev,
    FILE * input_fp, token_stack ** tok_list) {
  fgets(buf, MAX_TOK_LEN, input_fp);
  lex[0] = init_lexer(buf);
  tok_list[0] = lex_source(lex[0]);
  rev[0] = reverse_stack(tok_list);
}

/**
 * This function frees and points the given lexer/token_stack to NULL. Since we
 * are modifying addresses, again we need to pass a double pointer
 * @param  lex - lex to be freed and NULLed
 * @param  rev - token_stack to be freed and NULLed
 * @return N/a
 */
void clean_lexer_token_stack(lexer ** lex, token_stack ** rev) {
  // Clean up the pointers to use them again
  if(rev[0])
    while(rev[0]) rev[0] = pop_token(rev[0]);
  rev[0] = NULL;
  free_lexer(lex[0]);
  lex[0] = NULL;
}

/**
 * This function frees a user_out_file data structure
 * @param user_of - the user output file to be freed
 * @return    N/a
 */
void free_user_out_file(user_out_file * user_of) {
  if(user_of) {
    // Free Functions
    for (int i = 0; i < user_of->qty_functions; i++)
      if(user_of->functions[i])
        free_ast(user_of->functions[i]);
    if(user_of->functions)
      free(user_of->functions);
    // Free Colors
    for (int i = 0; i < user_of->qty_colors; i++)
      if(user_of->func_colors[i])
        free_color(user_of->func_colors[i]);
    if(user_of->func_colors)
      free(user_of->func_colors);
    // Free file_name
    if(user_of->file_name)
      free(user_of->file_name);
    free(user_of);
  }
}
