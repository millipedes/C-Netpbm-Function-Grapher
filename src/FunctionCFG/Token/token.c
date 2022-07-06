/**
 * @file   token.c
 * @brief  This file contains the functions relating to tokens.
 * @author Matthew C. Lindeman
 * @date   June 19, 2022
 * @bug    None known
 * @todo   Nothing
 */
#define _POSIX_C_SOURCE 200809L
#include"include/token.h"

/**
 * This function initializes a token
 * @param t_literal - the token literal as represented by a string
 * @param      type - the token type
 * @return        t - the new token
 */
token * init_token(char * t_literal, token_type type) { 
  token * t = calloc(1, sizeof(struct TOKEN_T));
  size_t len = (strnlen(t_literal, MAX_TOK_LEN) + 1);
  t->t_literal = calloc(len, sizeof(char));
  strncpy(t->t_literal, t_literal, len);
  t->type = type;
  return t;
}

/**
 * This function initializes a token list with no elements
 * @param       N/a
 * @return tok_list - the token list
 */
token ** init_token_list(void) {
  token ** tok_list = calloc(1, sizeof(struct TOKEN_T *));
  tok_list[0] = NULL; // allows for a size trick when adding toks
  return tok_list;
}

/**
 * This function adds the addition token to the token list list
 * @param     list - the list to be added to
 * @param addition - the token to add to the list
 * @param     size - the size of the token list (by the time it is made it will
 * be terminated by a newline, but while making it we need to know the size)
 * @return     N/a
 */
token ** add_token_to_list(token ** tok_list, token * addition, int size) {
  tok_list = realloc(tok_list, (size + 1) * sizeof(struct TOKEN_T *));
  tok_list[size] = addition;
  return tok_list;
}

/**
 * This function dumps the debugging info for a token (i.e. prints it and all
 * related values).
 * @param    t - the token to be debugged
 * @return N/a
 */
void token_dump_debug(token * t) {
  if(t) {
    printf("Token:\n");
    if(t->t_literal)
      printf("t_literal: `%s` ", t->t_literal);
    printf("type: `%s`\n", token_type_to_string(t->type));
  } else {
    fprintf(stderr, "[TOKEN DUMP DEBUG]: uninitialized token sent to debug."
        "\nExiting.\n");
    exit(1);
  }
  printf("--\n");
}

/**
 * This function frees a given token
 * @param    t - the token to be freed
 * @return N/a
 */
void free_token(token * t) {
  if(t) {
    if(t->t_literal)
      free(t->t_literal);
    free(t);
  }
}

/**
 * This function frees a token list
 * @param
 * @return
 */
void free_token_list(token ** tok_list) {
  int size = 0;
  if(tok_list) {
    while(tok_list[size]->type != TOKEN_NEWLINE) {
      if(tok_list[size])
        free_token(tok_list[size]);
      size++;
    }
    if(tok_list[size])
      free_token(tok_list[size]);
    free(tok_list);
  }
}
