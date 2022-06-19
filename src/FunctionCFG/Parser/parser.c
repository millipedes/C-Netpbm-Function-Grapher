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
// ast * parse_expression(token ** tok_list, int index) {
//   ast * left_child = parse_factor(tok_list, index + 1);
//   ast * right_child = NULL;
//   ast * parent = NULL;
//   switch(tok_list[index]->type) {
//     case TOKEN_PLUS:
//     case TOKEN_MINUS:
//       parent = init_ast(tok_list[index]->t_literal, tok_list[index]->type);
//       right_child = parse_expression(tok_list, );
//       return binary_tree(parent, left_child, right_child);
//     case TOKEN_NUMBER:
//     case TOKEN_VAR:
//       return parse_factor(tok_list, index);
//     default:
//       fprintf(stderr, "[PARSER]: Unexpected expression token: %s\nExiting\n",
//           token_type_to_string(tok_list[index]->type));
//       exit(1);
//   }
//   fprintf(stderr, "[PARSER]: Something went wrong in parse_expression\n"
//       "Exiting\n");
//   exit(1);
// }

/**
 * This function is meant to parse a factor
 * @param tok_list - the token stack to be parsed
 * @return abstree - the new abstract syntax tree from the factor
 */
// ast * parse_factor(token ** tok_list, int index) {
//   ast * abstree = NULL;
//   switch(tok_list[index]->type) {
//     case TOKEN_NUMBER:
//     case TOKEN_VAR:
//       abstree = init_ast(tok_list[index]->t_literal, tok_list[index]->type);
//       return abstree;
//     case TOKEN_L_PAREN:
//       abstree = parse_expression(tok_list, index + 1);
//       return abstree;
//     case TOKEN_MINUS:
//       abstree = init_ast(tok_list[index]->t_literal, tok_list[index]->type);
//       return unary_tree(abstree, parse_expression(tok_list, index + 1));
//     case TOKEN_NEWLINE:
//       return NULL;
//     default:
//       fprintf(stderr, "[PARSER]: Unexpected factor token: %s\nExiting\n",
//           token_type_to_string(tok_list[index]->type));
//       exit(1);
//   }
// }

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
