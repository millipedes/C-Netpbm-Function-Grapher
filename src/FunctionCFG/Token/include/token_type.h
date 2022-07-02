/**
 * @file   token_type.h
 * @brief  This file contains token_type enumeration and the related functions
 * definitions for the token_type.c
 * @author Matthew C. Lindeman
 * @date   June 19, 2022
 * @bug    None known
 * @todo   Nothing
 */
#ifndef TOKT_H
#define TOKT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
  TOKEN_VAR,
  TOKEN_FILE_NAME,
  TOKEN_NUMBER,
  TOKEN_PLUS,
  TOKEN_MINUS,
  TOKEN_MULT,
  TOKEN_DIV,
  TOKEN_L_PAREN,
  TOKEN_R_PAREN,
  TOKEN_COMMA,
  TOKEN_SUCH_THAT,
  TOKEN_POWER,
  TOKEN_SIN,
  TOKEN_COS,
  TOKEN_TAN,
  TOKEN_ARC_SIN,
  TOKEN_ARC_COS,
  TOKEN_ARC_TAN,
  TOKEN_LOG,
  TOKEN_NEWLINE,
} token_type;

char * token_type_to_string(token_type type);

#endif
