/**
 * @file   lexer.h
 * @brief  This file contains the function definitions for lexer.c
 * @author Matthew C. Lindeman
 * @date   June 18, 2022
 * @bug    None known
 * @todo   Nothing
 */
#ifndef LEX_H
#define LEX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../../Token/include/token_stack.h"
#include "../../../main/include/constants.h"

/**
 * This structure is used in the lexical analysis of the user input
 */
typedef struct LEXER_T {
  /** The source from which tokens are parsed */
  char * src;
  /** The current index up to which has been parsed */
  int curr_index;
  /** The current character being parsed */
  char c;
} lexer;

lexer * init_lexer(char * src);
token_stack * lex_source(lexer * l);
token * lex_next_token(lexer * l);
token * lex_number(lexer * l);
token * lex_fn_or_var(lexer * l);
void lex_advance(lexer * l);
void lex_whitespace(lexer * l);
void free_lexer(lexer * l);

#endif
