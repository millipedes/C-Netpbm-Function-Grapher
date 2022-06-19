/**
 * @file   token.h
 * @brief  This file contains the function definitons for token.c
 * @author Matthew C. Lindeman
 * @date   June 19, 2022
 * @bug    None known
 * @todo   Nothing
 */
#ifndef TOK_H
#define TOK_H

#include "token_type.h"
#include "../../../main/include/constants.h"

typedef struct TOKEN_T {
  char * t_literal;
  token_type type;
} token;

token * init_token(char * t_literal, token_type type);
token ** init_token_list(void);
token ** add_token_to_list(token ** list, token * addition, int size);
void token_dump_debug(token * t);
void free_token(token * t);
void free_token_list(token ** tok_list);

#endif

