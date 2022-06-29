/**
 * @file   token_stack.c
 * @brief  this file contains the functions that relate to a token_stack.
 * @author Matthew C. Lindeman
 * @date   June 27, 2022
 * @bug    None known
 * @todo   Nothing
 */
#include"include/token_stack.h"

/**
 * This function initializes a token stack given the first token on the stack
 * @param  ct - the current token to be placed on the stack
 * @return ts - the new token stack
 */
token_stack * init_token_stack(token * ct) {
  token_stack * ts = calloc(1, sizeof(struct TOKEN_STACK_T));
  ts->current = ct;
  ts->prev = NULL;
  return ts;
}

/**
 * This function pushes a token onto the stack
 * @param          ts - the token stack to be pushed onto
 * @param new_current - the new current token (i.e. the one being pushed)
 * @return        nts - the new token stack
 */
token_stack * push_token(token_stack * ts, token * new_current) {
  token_stack * nts = init_token_stack(new_current);
  nts->prev = ts;
  return nts;
}

/**
 * This function prints the debugging information relating to the given token
 * stack
 * @param   ts - the token stack to be debugged
 * @return N/a
 */
void token_stack_dump_debug(token_stack * ts) {
  printf("Token Stack:\n");
  if(ts) {
    if(ts->current)
      token_dump_debug(ts->current);
    if(ts->prev)
      token_stack_dump_debug(ts->prev);
  } else {
    fprintf(stderr, "[TOKEN_STACK DUMP DEBUG]: uninitialized token_stack sent"
        " to debug.\nExiting.\n");
    exit(1);
  }
  printf("--\n");
}

/**
 * This function reverses a token_stack and frees the initial stack
 * @param  bts - the backwards-token-stack to be reversed
 * @return fts - the forwards-token-stack that is bts reversed
 */
token_stack * reverse_stack(token_stack ** bts) {
  token_stack * fts = init_token_stack(
      init_token(bts[0]->current->t_literal, bts[0]->current->type)
      );
  bts[0] = pop_token(bts[0]);
  while(bts[0]) {
    fts = push_token(
        fts, init_token(bts[0]->current->t_literal, bts[0]->current->type));
    bts[0] = pop_token(bts[0]);
  }
  return fts;
}

/**
 * This function pops a token from the stack. Note that if the last token is
 * popped then the return value is NULL
 * @param   ts - the token stack
 * @return tmp - the new token stack
 */
token_stack * pop_token(token_stack * ts) {
  token_stack * tmp = NULL;
  if(ts) {
    if(ts->prev)
       tmp = ts->prev;
    if(ts->current)
      free_token(ts->current);
    free(ts);
  }
  return tmp;
}
