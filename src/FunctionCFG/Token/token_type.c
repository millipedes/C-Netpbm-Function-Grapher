/**
 * @file   token_type.c
 * @brief  This file contains the functions relating to token_types
 * @author Matthew C. Lindeman
 * @date   June 19, 2022
 * @bug    None known
 * @todo   Nothing
 */
#include "include/token_type.h"

/**
 * This function takes in a token_type and returns the string literal of that
 * type (the literal type name itself)
 * @param type - the type
 * @return  .\ - the string of the type
 */
char * token_type_to_string(token_type type) {
  switch(type) {
    case TOKEN_VAR:       return "TOKEN_VAR";
    case TOKEN_FILE_NAME: return "TOKEN_FILE_NAME";
    case TOKEN_NUMBER:    return "TOKEN_NUMBER";
    case TOKEN_PLUS:      return "TOKEN_PLUS";
    case TOKEN_MINUS:     return "TOKEN_MINUS";
    case TOKEN_MULT:      return "TOKEN_MULT";
    case TOKEN_DIV:       return "TOKEN_DIV";
    case TOKEN_L_PAREN:   return "TOKEN_L_PAREN";
    case TOKEN_R_PAREN:   return "TOKEN_R_PAREN";
    case TOKEN_COMMA:     return "TOKEN_COMMA";
    case TOKEN_SUCH_THAT: return "TOKEN_SUCH_THAT";
    case TOKEN_POWER:     return "TOKEN_POWER";
    case TOKEN_SIN:       return "TOKEN_SIN";
    case TOKEN_COS:       return "TOKEN_COS";
    case TOKEN_TAN:       return "TOKEN_TAN";
    case TOKEN_ARC_SIN:   return "TOKEN_ARC_SIN";
    case TOKEN_ARC_COS:   return "TOKEN_ARC_COS";
    case TOKEN_ARC_TAN:   return "TOKEN_ARC_TAN";
    case TOKEN_LOG:       return "TOKEN_LOG";
    case TOKEN_NEWLINE:   return "TOKEN_NEWLINE";
  }
  fprintf(stderr, "Holy smokes what?\n");
  exit(1);
}
