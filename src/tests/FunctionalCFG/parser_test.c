/**
 * @file   parser_test.c
 * @brief  This file contains functions that are used in testing functions in
 * parser.c
 * @author Matthew C. Lindeman
 * @date   July 13, 2022
 * @bug    None known
 * @todo   Nothing
 */
#include "include/parser_test.h"

void test_parser_simplify_tree(char * input) {
  lexer * lex = init_lexer(input);
  token_stack * tok_list = lex_source(lex);
  token_stack * rev = reverse_stack(&tok_list);
  ast * abstree = parse_expression(&rev);
  abstree = simplify_tree(abstree);
  ast_dump_debug(abstree);
  free_ast(abstree);
  free_lexer(lex);
  while(rev) rev = pop_token(rev);
}

void test_parser_derivative_of(char * input) {
  lexer * lex = init_lexer(input);
  token_stack * tok_list = lex_source(lex);
  token_stack * rev = reverse_stack(&tok_list);
  ast * abstree = parse_expression(&rev);
  abstree = derivative_of(abstree);
  // ast_dump_debug(abstree);
  abstree = simplify_tree(abstree);
  ast_print_expression(abstree);
  printf("\n");
  free_ast(abstree);
  free_lexer(lex);
  while(rev) rev = pop_token(rev);
}
