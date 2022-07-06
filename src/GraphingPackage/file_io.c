/**
 * @file   file_io.c
 * @brief  this file contains the function to write a canvas to a netpbm file
 * @author Matthew C. Lindeman
 * @date   June 18, 2022
 * @bug    None known
 * @todo   fix the write_outputs_from_input_cfg_file as it is currently terrible
 * code. If this is the first function that a potential user is looking at, I
 * would recommend examining other parts of the code base as this function is
 * coded to an implementation not an interface *unlike* the rest of the code
 * base. OR write a PR with a better implementation of
 * write_outputs_from_input_cfg_file.
 * This whole file needs serious work. But as is it can do what I expect the
 * beta version of the software to do.
 */
#define _POSIX_C_SOURCE 200809L
#include "include/file_io.h"

/**
 * This function takes a given canvas and writes it to a netpbm file (to include
 * netpbm file headers).
 * @param file_name - the full path to the file
 * @param       can - the canvas to be written
 * @return      N/a
 */
void write_canvas_to_file(char * file_name, canvas * can) {
  FILE * fp = fopen(file_name, "w");
  write_output_headings(fp, can);
  for(int i = 0; i < can->height; i++) {
    for(int j = 0; j < can->width; j++) {
      fprintf(fp, "%d %d %d\n", can->pixel_instance[i][j]->pix_color->r,
          can->pixel_instance[i][j]->pix_color->g,
          can->pixel_instance[i][j]->pix_color->b);
    }
  }
  fclose(fp);
}

/**
 * This file writes the output file(s) from the input file specification.
 * @param file_name - the name of the input specification file.
 * @return      N/a
 */
void write_outputs_from_input_cfg_file(char * file_name) {
  // User Input Buffer
  char buf[MAX_TOK_LEN];
  // Init Input File
  FILE * input_fp = fopen(file_name, "r");
  // Graph Scale Variables
  double x_min = 0;
  double y_min = 0;
  double x_max = 0;
  double y_max = 0;
  // Function Color Variables
  color ** func_colors = NULL;
  int qty_colors = 0; // Assuming 1> color, this will be how many
  // Function Variables
  ast ** functions = NULL;
  int qty_functions = 0;
  // Output File Information
  char ** file_names = NULL;
  int qty_files = 1;
  // Lexer
  lexer * lex = NULL;
  // Token Stack
  token_stack * tok_list = NULL;
  token_stack * rev = NULL;
  // A default length variable to work with
  size_t len = 0;
  // The red input reading var
  int r = 0;
  // The green input reading var
  int g = 0;
  // The blue input reading var
  int b = 0;

  proc_new_line(buf, &lex, &rev, input_fp, &tok_list);
  if(!strncmp(rev->current->t_literal, "FILE_NAME", MAX_TOK_LEN)) {
    rev = pop_token(rev); // FILE_NAME
    rev = pop_token(rev); // TOKEN_SUCH_THAT
    len = strnlen(rev->current->t_literal, MAX_TOK_LEN) + 1; // + 1 -> Nul term
    file_names = calloc(1, sizeof(char *));
    file_names[0] = calloc(len, sizeof(char));
    strncpy(file_names[0], rev->current->t_literal, len);
  }
  clean_lexer_token_stack(&lex, &rev);

  proc_new_line(buf, &lex, &rev, input_fp, &tok_list);
  x_min = get_mins_maxes("X_MIN", &rev);
  clean_lexer_token_stack(&lex, &rev);

  proc_new_line(buf, &lex, &rev, input_fp, &tok_list);
  y_min = get_mins_maxes("Y_MIN", &rev);
  clean_lexer_token_stack(&lex, &rev);

  proc_new_line(buf, &lex, &rev, input_fp, &tok_list);
  x_max = get_mins_maxes("X_MAX", &rev);
  clean_lexer_token_stack(&lex, &rev);

  proc_new_line(buf, &lex, &rev, input_fp, &tok_list);
  y_max = get_mins_maxes("Y_MAX", &rev);
  clean_lexer_token_stack(&lex, &rev);

  int end_flag = 0;
  while(!end_flag) {
    proc_new_line(buf, &lex, &rev, input_fp, &tok_list);
    end_flag = strncmp(rev->current->t_literal, "COLOR", MAX_TOK_LEN);
    if(end_flag) {
      clean_lexer_token_stack(&lex, &rev);
      break;
    }

    rev = pop_token(rev);
    rev = pop_token(rev);

    r = atoi(rev->current->t_literal);
    rev = pop_token(rev); // color
    rev = pop_token(rev); // comma
    g = atoi(rev->current->t_literal);
    rev = pop_token(rev); // color
    rev = pop_token(rev); // comma
    b = atoi(rev->current->t_literal);

    qty_colors++;
    if(!func_colors)
      func_colors = realloc(NULL, qty_colors * sizeof(struct COLOR_T *));
    else
      func_colors = realloc(func_colors, qty_colors * sizeof(struct COLOR_T *));
    func_colors[qty_colors - 1] = init_color(r, g, b);
    clean_lexer_token_stack(&lex, &rev);
  }

  proc_new_line(buf, &lex, &rev, input_fp, &tok_list);
  if(!strncmp(rev->current->t_literal, "FUNCS", MAX_TOK_LEN))
    clean_lexer_token_stack(&lex, &rev);

  end_flag = 1;
  while(end_flag != 0) {
    proc_new_line(buf, &lex, &rev, input_fp, &tok_list);
    end_flag = strncmp(rev->current->t_literal, "END", MAX_TOK_LEN);
    if(end_flag == 0) {
      clean_lexer_token_stack(&lex, &rev);
      break;
    }
    qty_functions++;
    if(!functions)
      functions = calloc(qty_functions, sizeof(struct AST_T *));
    else
      functions = realloc(functions, qty_functions * sizeof(struct AST_T *));
    functions[qty_functions - 1] = parse_expression(&rev);
    clean_lexer_token_stack(&lex, &rev);
  }

  canvas * can = init_canvas(GRAPH_DIMS, GRAPH_DIMS);
  graph_scale * gs = init_graph_scale(
      init_axis_tic_marks(QTY_TIC_MARKS, GPRAH_TIC_SMALL, GPRAH_TIC_LARGE, X),
      init_axis_tic_marks(QTY_TIC_MARKS, GPRAH_TIC_LARGE, GPRAH_TIC_SMALL, Y),
      init_coord_axis(x_min, x_max, 2, X),
      init_coord_axis(y_min, y_max, 2, Y),
      init_graph_border(init_color(0, 0, 0), GRAPH_BORDER), 2);
  write_gs_to_canvas(can, gs);

  for(int i = 0; i < qty_functions; i++) {
    if(qty_colors == 1)
      write_ast_to_canvas(can, gs, functions[i], func_colors[0], 0.00001);
    else
      write_ast_to_canvas(can, gs, functions[i], func_colors[i], 0.00001);
  }
  for(int i = 0; i < qty_files; i++) {
    write_canvas_to_file(file_names[i], can);
  }

  /**
   * Freeing in the following order:
   * #) Name        Type
   * -------------------------------
   * 1) func_colors color **,
   * 2) file_names  char **,
   * 3) functions   ast **,
   * 4) ts          token_stack *, // done before this
   * 5) rev         token_stack *, // done before this
   * 6) lex         lexer *,       // done before this
   * 7) can         canvas *,
   * 8) gs          graph_scale *;
   * 9) input_fp    FILE *,
   */
  if(func_colors) {
    for(int i = 0; i < qty_colors; i++) {
      free_color(func_colors[i]);
    }
    free(func_colors);
  }
  if(file_names) {
    for(int i = 0; i < qty_files; i++) {
      if(file_names[i])
        free(file_names[i]);
    }
    free(file_names);
  }
  if(functions) {
    for(int i = 0; i < qty_functions; i++) {
      if(functions[i])
        free_ast(functions[i]);
    }
    free(functions);
  }
  free_canvas(can);
  free_graph_scale(gs);
  fclose(input_fp);
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
 * This function retrieves either x or y min or max, depending on the xymin_max
 * that is passed to the funcion.
 * @param xymin_max - the string that determines what we are getting
 * @param       rev - the token_stack from which we get the values
 * @return   result - the result of the data retrieval
 */
int get_mins_maxes(char * xymin_max, token_stack ** rev) {
  int result = 0;
  if(!strncmp(rev[0]->current->t_literal, xymin_max, MAX_TOK_LEN)) {
    rev[0] = pop_token(rev[0]); // FILE_NAME
    rev[0] = pop_token(rev[0]); // TOKEN_SUCH_THAT
    if(rev[0]->current->type == TOKEN_MINUS) {
      rev[0] = pop_token(rev[0]);
      result = -atof(rev[0]->current->t_literal);
    } else {
      result = atof(rev[0]->current->t_literal);
    }
  }
  return result;
}

/**
 * This function writes the netpbm file headings to the given output file.
 * @param   fp - the file pointer to be written to.
 * @param  can - the canvas from which to get the height/width
 * @return N/a
 */
void write_output_headings(FILE * fp, canvas * can) {
  fprintf(fp, "P3\n");
  fprintf(fp, "%d %d\n255\n", can->width, can->height);
}

/**
 * This function frees and points the given lexer/token_stack to NULL. Since we
 * are modifying addresses, again we need to pass a double pointer
 * @param lex - lex to be freed and NULLed
 * @param rev - token_stack to be freed and NULLed
 * @return
 */
void clean_lexer_token_stack(lexer ** lex, token_stack ** rev) {
  // Clean up the pointers to use them again
  if(rev[0])
    while(rev[0]) rev[0] = pop_token(rev[0]);
  rev[0] = NULL;
  free_lexer(lex[0]);
  lex[0] = NULL;
}
