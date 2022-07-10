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
  // Lexer
  lexer * lex = NULL;
  // Token Stack
  token_stack * tok_list = NULL;
  token_stack * rev = NULL;
  // User Output File
  user_out_file * user_of = NULL;

  proc_new_line(buf, &lex, &rev, input_fp, &tok_list);
  if(!strncmp(rev->current->t_literal, "FILE_NAME", MAX_TOK_LEN))
    user_of = process_file_heading(&rev);
  clean_lexer_token_stack(&lex, &rev);
  proc_new_line(buf, &lex, &rev, input_fp, &tok_list);

  while(strncmp(rev->current->t_literal, "END", MAX_TOK_LEN)) {
    // FUNCS Block
    if(!strncmp(rev->current->t_literal, "FUNC", MAX_TOK_LEN))
      process_func_section(buf, &lex, &rev, &tok_list, input_fp, user_of);
    // COLOR Handling
    if(rev)
      if(!strncmp(rev->current->t_literal, "COLOR", MAX_TOK_LEN))
        process_color(user_of, &rev, &lex);
    // Process Mins/Maxes
    if(rev)
      if(!strncmp(rev->current->t_literal, "X_MIN", MAX_TOK_LEN)
         || !strncmp(rev->current->t_literal, "X_MAX", MAX_TOK_LEN)
         || !strncmp(rev->current->t_literal, "Y_MIN", MAX_TOK_LEN)
         || !strncmp(rev->current->t_literal, "Y_MAX", MAX_TOK_LEN)
          )
        process_min_maxes(user_of, &rev, &lex);
    // Process Dimensions of Canvas (N.B. canvas_dims == size of pic in pixels)
    if(rev)
      if(!strncmp(rev->current->t_literal, "CANVAS_DIMS", MAX_TOK_LEN))
        process_canvas_dims(user_of, &rev, &lex);
    // Process Qty of Tic Marks
    if(rev)
      if(!strncmp(rev->current->t_literal, "QTY_TIC_MARKS", MAX_TOK_LEN))
        process_qty_tic_marks(user_of, &rev, &lex);
    // Small Dimension of Axis Tic Marks
    if(rev)
      if(!strncmp(rev->current->t_literal, "TIC_MARKS_SMALL", MAX_TOK_LEN))
        process_tic_marks_small(user_of, &rev, &lex);
    // Large Dimension of Axis Tic Marks
    if(rev)
      if(!strncmp(rev->current->t_literal, "TIC_MARKS_LARGE", MAX_TOK_LEN))
        process_tic_marks_large(user_of, &rev, &lex);
    // Width of the Graph Border
    if(rev)
      if(!strncmp(rev->current->t_literal, "GRAPH_BORDER", MAX_TOK_LEN))
        process_graph_border(user_of, &rev, &lex);
    if(rev)
      clean_lexer_token_stack(&lex, &rev);
    proc_new_line(buf, &lex, &rev, input_fp, &tok_list);
  }

  canvas * can = init_canvas(user_of->canvas_dims, user_of->canvas_dims);
  graph_scale * gs = init_graph_scale(
      init_axis_tic_marks(user_of->qty_tic_marks, user_of->graph_tic_mark_small,
        user_of->graph_tic_mark_large, X),
      init_axis_tic_marks(user_of->qty_tic_marks, user_of->graph_tic_mark_large,
        user_of->graph_tic_mark_small, Y),
      init_coord_axis(user_of->x_min, user_of->x_max, 2, X),
      init_coord_axis(user_of->y_min, user_of->y_max, 2, Y),
      init_graph_border(init_color(0, 0, 0), user_of->graph_border),
      2
      );
  write_gs_to_canvas(can, gs);

  for(int i = 0; i < user_of->qty_functions; i++) {
    if(user_of->qty_colors == 1)
      write_ast_to_canvas(can, gs, user_of->functions[i],
          user_of->func_colors[0], 0.00001);
    else
      write_ast_to_canvas(can, gs, user_of->functions[i],
          user_of->func_colors[i], 0.00001);
  }

  write_canvas_to_file(user_of->file_name, can);

  clean_lexer_token_stack(&lex, &rev);
  free_canvas(can);
  free_graph_scale(gs);
  free_user_out_file(user_of);
  fclose(input_fp);
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
