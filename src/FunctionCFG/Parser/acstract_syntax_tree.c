/**
 * @file    ast.c
 * @brief   This file contains the functions relating to making/maintiaing the
 * abstract syntax tree
 * @author  Matthew C. Lindeman
 * @date    June 19, 2022
 * @bug     None known
 * @todo    Nothing
 */
#include "include/abstract_syntax_tree.h"

/**
 * This function initializes a new abstract syntax tree
 * @param t_literal - the literal string of the token
 * @param      type - the type of the token
 * @return  abstree - the abstract syntax tree
 */
ast * init_ast(char * t_literal, token_type type) {
  ast * abstree = calloc(1, sizeof(struct AST_T));
  abstree->value = init_token(t_literal, type);
  abstree->children = NULL;
  if(abstree->value->type == TOKEN_NUMBER)
    abstree->numeric_value = atof(abstree->value->t_literal);
  else
    abstree->numeric_value = 0.0;
  abstree->no_children = 0;
  return abstree;
}

/**
 * This function is used for debugging abstract syntax trees
 * @param abstree - the abstract syntax tree to be debugged
 * @return    N/a
 */
void ast_dump_debug(ast * abstree) {
  printf("AST\n");
  token_dump_debug(abstree->value);
  printf("ast no children: %d\n", abstree->no_children);
  for(int i = 0; i < abstree->no_children; i++) {
    printf("Child %d:\n", i);
    ast_dump_debug(abstree->children[i]);
  }
  printf("**\n");
}

/**
 * This function is used for debugging abstract syntax trees
 * @param abstree - the abstract syntax tree to be debugged
 * @return    N/a
 */
void ast_pretty_print(ast * abstree) {
  printf("AST\n");
  printf("Token Value: `%s`, Token Type: %d, No Children: %d\n",
      abstree->value->t_literal, abstree->value->type, abstree->no_children);
  printf("Children\n");
  for(int i = 0; i < abstree->no_children; i++) {
    printf("Token Value: `%s`, Token Type: %d, No Children: %d\n",
        abstree->children[i]->value->t_literal, abstree->children[i]->value->type,
        abstree->children[i]->no_children);
  }
  printf("End of Children\n\n");
  for(int i = 0; i < abstree->no_children; i++) {
    ast_pretty_print(abstree->children[i]);
  }
}

/**
 * This function frees an abstract syntax tree
 * @param abstree - the abstract syntax tree to be freed
 * @return    N/a
 */
void free_ast(ast * abstree) {
  if(abstree) {
    if(abstree->value)
      free_token(abstree->value);
    if(abstree->children) {
      for(int i = 0; i < abstree->no_children; i++) {
        if(abstree->children[i])
          free_ast(abstree->children[i]);
      }
      free(abstree->children);
    }
    free(abstree);
  }
}

/**
 * This function prints an abstract syntax tree as though it were an expression
 * on one line. Can't print its own new line, so you want to follow it with one.
 * @param abstree - The abstract syntax tree to be printed.
 * @return    N/a
 */
void ast_print_expression(ast * abstree) {
  if(abstree->no_children == 0)
    printf("%s ", abstree->value->t_literal);
  else if(abstree->no_children == 1) {
    ast_print_expression(abstree->children[0]);
    printf("%s ", abstree->value->t_literal);
  } else if(abstree->no_children == 2) {
    ast_print_expression(abstree->children[0]);
    printf("%s ", abstree->value->t_literal);
    ast_print_expression(abstree->children[1]);
  }
}

/**
 * This function decrements a number ast node
 * @param abstree - The node that will de decremented.
 * @return N/a
 */
void decrement_number_ast(ast * abstree) {
  char * result = calloc(9 + 3, sizeof(char));
  double r1 = 0.0;
  r1 = abstree->numeric_value - 1;
  sprintf(result, "%.8f", r1);
  free_ast(abstree);
  abstree = NULL;
  abstree = init_ast(result, TOKEN_NUMBER);
}
