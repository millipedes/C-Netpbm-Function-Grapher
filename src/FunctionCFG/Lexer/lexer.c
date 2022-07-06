/**
 * @file   lexer.c
 * @brief  This file contains the functions that relate to lexing
 * @author Matthew C. Lindeman
 * @date   June 19, 2022
 * @bug    None known
 * @todo   Nothing
 */
#define _POSIX_C_SOURCE 200809L
#include"include/lexer.h"

/**
 * This function initializes a lexer given a certain src to lex
 * @param src - the source to be lexed
 * @return  l - the new lexer
 */
lexer * init_lexer(char * src) {
  lexer * l = calloc(1, sizeof(struct LEXER_T));
  size_t len = (strnlen(src, MAX_TOK_LEN) + 1);
  l->src = calloc(len, sizeof(char));
  strncpy(l->src, src, len);
  l->curr_index = 0;
  l->c = l->src[l->curr_index];
  return l;
}

/**
 * This function makes a token_stack from the source contained by lexer l
 * @param   l - the lexer containing the source from the user
 * @return ts - the token_stack that is reflective of the source
 */
token_stack * lex_source(lexer * l) {
  /**
   * NOTE: that on an empty input, l->c will be a new line thus this is
   * sufficient
   */
  token_stack * ts = init_token_stack(lex_next_token(l));
  while(l->c != '\n' && l->c != '\r')
    ts = push_token(ts, lex_next_token(l));
  // The newline itself
  ts = push_token(ts, lex_next_token(l));
  return ts;
}

/**
 * This function will lex the next token from the source and return the
 * corresponding token.
 * @param   l - the lexer that contains the source
 * @return .\ - (no explicit name i.e. lambda) the corresponding token
 */
token * lex_next_token(lexer * l) {
  lex_whitespace(l);
  if(isalpha(l->c)) {
    return lex_fn_or_var(l);
  }

  if(isdigit(l->c)) {
    return lex_number(l);
  }

  switch(l->c) {
    case '(':
      lex_advance(l);
      return init_token("(", TOKEN_L_PAREN);
    case ')':
      lex_advance(l);
      return init_token(")", TOKEN_R_PAREN);
    case '^':
      lex_advance(l);
      return init_token("^", TOKEN_POWER);
    case '+':
      lex_advance(l);
      return init_token("+", TOKEN_PLUS);
    case '-':
      lex_advance(l);
      return init_token("-", TOKEN_MINUS);
    case '*':
      lex_advance(l);
      return init_token("*", TOKEN_MULT);
    case '/':
      lex_advance(l);
      return init_token("/", TOKEN_DIV);
    case ',':
      lex_advance(l);
      return init_token(",", TOKEN_COMMA);
    case ':':
      lex_advance(l);
      if(l->c == ':') {
        lex_advance(l);
        return init_token("::", TOKEN_SUCH_THAT);
      } else {
        fprintf(stderr, "[LEXER]: `:` followed by `%c` which is not \'such "
            "that\'\n", l->c);
        exit(1);
      }
    case '\n':
    case '\r':
      return init_token("0", TOKEN_NEWLINE);
  }
  return NULL;
}

/**
 * This function lexs a number (both double/int)
 * @param    l - the lexer containing the source
 * @return tmp - the token
 */
token * lex_number(lexer * l) {
  size_t len = 0;
  int start_index = l->curr_index;
  int dec_flag = 0;
  while(isdigit(l->c)) {
    lex_advance(l);
    if(l->c == '.' && dec_flag == 0) {
      lex_advance(l);
      len++;
      dec_flag = 1;
    }
    len++;
  }
  char * result = calloc(len + 1, sizeof(char));
  memcpy(result, &l->src[start_index], len);
  token * tmp = init_token(result, TOKEN_NUMBER);
  if(result)
    free(result);
  return tmp;
}

/**
 * This function lexs a word
 * @param    l - the lexer containing the source
 * @return tmp - the token
 */
token * lex_fn_or_var(lexer * l) {
  token * tmp = NULL;
  size_t len = 0;
  int period_flag = 0;
  int start_index = l->curr_index;
  while(isalpha(l->c) || l->c == '_') {
    lex_advance(l);
    if(l->c == '.' && period_flag == 0) {
      lex_advance(l);
      len++;
      period_flag = 1;
    }
    len++;
  }
  char * result = calloc(len + 1, sizeof(char));
  memcpy(result, &l->src[start_index], len);
  if(!strncmp("sin", result, MAX_TOK_LEN))
    tmp = init_token(result, TOKEN_SIN);
  else if(!strncmp("cos", result, MAX_TOK_LEN))
    tmp = init_token(result, TOKEN_COS);
  else if(!strncmp("tan", result, MAX_TOK_LEN))
    tmp = init_token(result, TOKEN_TAN);
  else if(!strncmp("arcsin", result, MAX_TOK_LEN))
    tmp = init_token(result, TOKEN_ARC_SIN);
  else if(!strncmp("arccos", result, MAX_TOK_LEN))
    tmp = init_token(result, TOKEN_ARC_COS);
  else if(!strncmp("arctan", result, MAX_TOK_LEN))
    tmp = init_token(result, TOKEN_ARC_TAN);
  else if(!strncmp("log", result, MAX_TOK_LEN))
    tmp = init_token(result, TOKEN_LOG);
  else if(!period_flag)
    tmp = init_token(result, TOKEN_VAR);
  else
    tmp = init_token(result, TOKEN_FILE_NAME);

  // token * tmp = period_flag == 0 ? init_token(result, TOKEN_VAR)
  //   : init_token(result, TOKEN_FILE_NAME);
  if(result) {
    free(result);
  }
  return tmp;
}

/**
 * This function ``advances" the lexer once
 * @param    l - the lexer to be advanced
 * @return N/a
 */
void lex_advance(lexer * l) {
  l->curr_index++;
  l->c = l->src[l->curr_index];
}

/**
 * This function lexs whitespace (as lang doesn't support whitespace atm)
 * @param    l - the lexer from which the whitespace is skipped
 * @return N/a
 */
void lex_whitespace(lexer * l) {
  while(l->c == ' ' || l->c == '\t')
    lex_advance(l);
}

/**
 * This function frees a lexer
 * @param    l - the lexer to be freed
 * @return N/a
 */
void free_lexer(lexer * l) {
  if(l) {
    if(l->src)
      free(l->src);
    free(l);
  }
}
