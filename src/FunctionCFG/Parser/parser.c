/**
 * @file   parser.c
 * @brief  This file contains the functions required for parsing input
 * @author Matthew C. Lindeman
 * @date   June 19, 2022
 * @bug    None known
 * @todo   Nothing
 */
#include"include/parser.h"

/**
 * This function parses an expression
 * @param  tok_list - the token stack to be parsed
 * @return       .\ - the abstract syntax tree of the expression
 */
ast * parse_expression(token_stack ** ts) {
  ast * left_child = NULL;
  ast * right_child = NULL;
  if(ts[0]) {
    left_child = parse_term(ts);
    switch(ts[0]->current->type) {
      case TOKEN_PLUS:
        ts[0] = pop_token(ts[0]);
        right_child = parse_expression(ts);
        return binary_tree(init_ast("+", TOKEN_PLUS), left_child, right_child);
      case TOKEN_MINUS:
        ts[0] = pop_token(ts[0]);
        right_child = parse_expression(ts);
        return binary_tree(init_ast("-", TOKEN_PLUS), left_child, right_child);
      case TOKEN_VAR:
      case TOKEN_NUMBER:
      case TOKEN_NEWLINE: // This will occur bc factor pops id i.e. newline
        return left_child;
      default:
        fprintf(stderr, "[PARSER1]: Unrecognized token: `%s`\nExiting\n",
            ts[0]->current->t_literal);
        exit(1);
    }
  } else {
    return left_child;
  }
}

ast * parse_term(token_stack ** ts) {
  switch(ts[0]->current->type) {
    case TOKEN_VAR:
    case TOKEN_NUMBER:
      return parse_factor(ts);
    default:
      fprintf(stderr, "[PARSER2]: Unrecognized token: `%s`\nExiting\n",
          ts[0]->current->t_literal);
      exit(1);
  }
}

/**
 * This function is meant to parse a factor
 * @param tok_list - the token stack to be parsed
 * @return abstree - the new abstract syntax tree from the factor
 */
ast * parse_factor(token_stack ** ts) {
  ast * tmp;
  switch(ts[0]->current->type) {
    case TOKEN_VAR:
    case TOKEN_NUMBER:
      tmp = init_ast(ts[0]->current->t_literal, ts[0]->current->type);
      ts[0] = pop_token(ts[0]);
      return tmp;
    default:
      fprintf(stderr, "[PARSER3]: Unrecognized token: `%s`\nExiting\n",
          ts[0]->current->t_literal);
      exit(1);
  }
}

/**
 * This function takes a parent tree, allocates space for children, then sets
 * the children to be left and right children respectively
 * @param      parent - the parent node of the tree
 * @param  left_child - the left child of the tree
 * @param right_child - the right child of the tree
 * @return     parent - the new tree with children left_child and right_child
 */
ast * binary_tree(ast * parent, ast * left_child, ast * right_child) {
  parent->children = calloc(2, sizeof(struct AST_T *));
  parent->children[0] = left_child;
  parent->children[1] = right_child;
  parent->no_children = 2;
  return parent;
}

/**
 * This function generates a unary tree with a parent-child relationship
 * @param  parent - the parent of the tree
 * @param   child - the child of the tree
 * @return parent - the new tree
 */
ast * unary_tree(ast * parent, ast * child) {
  parent->children = calloc(1, sizeof(struct AST_T *));
  parent->children[0] = child;
  parent->no_children = 1;
  return parent;
} 
