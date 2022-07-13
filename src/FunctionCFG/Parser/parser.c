/**
 * @file   parser.c
 * @brief  This file contains the functions required for parsing input
 * @author Matthew C. Lindeman
 * @date   June 27, 2022
 * @bug    None known
 * @todo   simplify_tree has two cases that need to be fixed: identity
 * (operator) variable, and cases that look like this where '+' represents any
 * similar operator (i.e. plus &| minus, multiplication &| division etc.):
 *    +                                       +
 *   / \                                     / \
 *  2   +  which should simplify to +  and  2   -  which should simplify to +
 *     / \                         / \     / \                             / \
 *    1   x                       3   x   1   x                           1   x
 * @NOTE   Its worth mentioning that the advantage to using a token_stack as
 * opposed to a list is that with a list it is very difficult to properly index
 * things i.e. we use a stack. However, we need to perminently modify the
 * address of the stack itself thus we pass the address of the stack in to be
 * modified instead of the value of the stack (i.e. why there are a bunch of
 * double pointers.  Since we only have one stack, we will only ever index the
 * fist element of the double pointer).
 */
#define _POSIX_C_SOURCE 200809L
#include"include/parser.h"

/**
 * This function evaluates an abstract syntax tree (i.e. the idea is to pass
 * this into a write_ast_to_canvas s.t. it can eval at each step)
 * @param abstree - the abstract syntax tree to be evaluated
 * @param       x - the variable value
 * @return     .\ - the value of that level of the ast
 */
double evaluate_tree(ast * abstree, double x) {
  switch(abstree->value->type) {
    case TOKEN_VAR:
      return x;
    case TOKEN_NUMBER:
      return abstree->numeric_value;
    case TOKEN_PLUS:
      return addition(evaluate_tree(abstree->children[0], x),
          evaluate_tree(abstree->children[1], x));
    case TOKEN_MINUS:
      return subtraction(evaluate_tree(abstree->children[0], x),
          evaluate_tree(abstree->children[1], x));
    case TOKEN_MULT:
      return multiplication(evaluate_tree(abstree->children[0], x),
          evaluate_tree(abstree->children[1], x));
    case TOKEN_DIV:
      return division(evaluate_tree(abstree->children[0], x),
          evaluate_tree(abstree->children[1], x));
    case TOKEN_POWER:
      return pow(evaluate_tree(abstree->children[0], x),
          evaluate_tree(abstree->children[1], x));
    case TOKEN_SIN:
      return sin(evaluate_tree(abstree->children[0], x));
    case TOKEN_COS:
      return cos(evaluate_tree(abstree->children[0], x));
    case TOKEN_TAN:
      return tan(evaluate_tree(abstree->children[0], x));
    case TOKEN_ARC_SIN:
      return asin(evaluate_tree(abstree->children[0], x));
    case TOKEN_ARC_COS:
      return acos(evaluate_tree(abstree->children[0], x));
    case TOKEN_ARC_TAN:
      return atan(evaluate_tree(abstree->children[0], x));
    case TOKEN_LOG:
      return log(evaluate_tree(abstree->children[0], x));
    default:
      fprintf(stderr, "`%s`passed to evaluate_tree?\nExiting\n",
          token_type_to_string(abstree->value->type));
      exit(1);
  }
}

ast * derivative_of(ast * abstree) {
  ast * ast1 = NULL;
  char * result = calloc(9 + 3, sizeof(char));
  double r1 = 0.0;
  switch(abstree->value->type) {
    case TOKEN_PLUS:
      return binary_tree(init_ast("+", TOKEN_PLUS),
                         derivative_of(abstree->children[0]),
                         derivative_of(abstree->children[1]));
    case TOKEN_MINUS:
      return binary_tree(init_ast("-", TOKEN_MINUS),
                         derivative_of(abstree->children[0]),
                         derivative_of(abstree->children[1]));
    case TOKEN_POWER:
      if(subtree_all_numbers(abstree->children[0]) &&
         !subtree_all_numbers(abstree->children[1])) {
        abstree->children[1] = simplify_tree(abstree->children[1]);
        strncpy(result,
                abstree->children[1]->value->t_literal,
                strnlen(abstree->children[1]->value->t_literal, MAX_TOK_LEN) + 1);
        r1 = atof(result);
        r1--;
        sprintf(result, "%.8f", r1);
        ast1 = init_ast(result, TOKEN_NUMBER);
        return binary_tree(init_ast("*", TOKEN_MULT),
                           abstree->children[1],
                           binary_tree(init_ast("^", TOKEN_POWER),
                                       abstree->children[0],
                                       ast1));
      }
      break;
    case TOKEN_MULT:
      if(!subtree_all_numbers(abstree->children[0]) &&
          subtree_all_numbers(abstree->children[1]))
        return binary_tree(init_ast("*", TOKEN_MULT),
                           abstree->children[0],
                           derivative_of(abstree->children[1]));
      if(subtree_all_numbers(abstree->children[0]) &&
          !subtree_all_numbers(abstree->children[1]))
        return binary_tree(init_ast("*", TOKEN_MULT),
                           abstree->children[1],
                           derivative_of(abstree->children[0]));
      if(subtree_all_numbers(abstree->children[0]) &&
          subtree_all_numbers(abstree->children[1]))
        return binary_tree(init_ast("*", TOKEN_MULT),
                           abstree->children[0],
                           derivative_of(abstree->children[1]));
      return init_ast("0", TOKEN_NUMBER);
    case TOKEN_NUMBER:
      return init_ast("0", TOKEN_NUMBER);
    case TOKEN_VAR:
      return init_ast("1", TOKEN_NUMBER);
    default:
        fprintf(stderr, "[DER1]: Unrecognized token: `%s`\nExiting\n",
            abstree->value->t_literal);
        exit(1);
  }
  return NULL;
}

/**
 * This function takes a tree and simplifies it. For example, performing all
 * operations to simplify numbers (double) and remove identity branches i.e.
 *   +             *            /            +
 *  / \ => 2 and  / \ => 2 and / \ => 2 and / \ => 3
 * 2   0         2   1        2   1        2   1
 * but of course done recursively such that if a subbranch is an operator over
 * only numbers/has identity subbranch then it will simplify as well.
 * @param -
 * @return
 */
ast * simplify_tree(ast * abstree) {
  char * result = calloc(9 + 3, sizeof(char));
  if(!subtree_all_numbers(abstree)) {
    sprintf(result, "%.8f", evaluate_tree(abstree, 0));
    abstree = NULL;
    abstree = init_ast(result, TOKEN_NUMBER);
    free(result);
    return abstree;
  }
  for(int i = 0; i < abstree->no_children; i++) {
    if(!subtree_all_numbers(abstree->children[i])) {
      abstree->children[i] = simplify_tree(abstree->children[i]);
    } else if (abstree->children[i] != TOKEN_VAR) {
      abstree->children[i] = simplify_tree(abstree->children[i]);
    }
  }
  free(result);
  return abstree;
}

/**
 * This function verifies if a given tree have only numbers as leaf nodes.
 * Unfortunately the function is a little counter-intuitive in that it returns 0
 * if there are only numbers as leaf nodes and 1 if not.
 * @param abstree - the ast to verify
 * @return      1 - there exists a variable among the lead nodes of the tree
 *              0 - there exists no variable amoung the leaf nodes of the tree
 */
int subtree_all_numbers(ast * abstree) {
  int var_child_flag = 0;
  if(abstree->value->type == TOKEN_VAR)
    return 1;
  if(abstree->value->type == TOKEN_NUMBER)
    return 0;
  for (int i = 0; i < abstree->no_children; i++) {
    if(abstree->children[i]->value->type == TOKEN_VAR)
      return 1;
    else if(abstree->children[i]->value->type != TOKEN_NUMBER)
      var_child_flag = subtree_all_numbers(abstree->children[i]);
    if(var_child_flag)
      return 1;
  }
  return 0;
}

/**
 * This function parses an expression from a token stack. Essentially anything
 * that is a mathematical term (in the sense of operands of +/-).
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
        return binary_tree(init_ast("-", TOKEN_MINUS), left_child, right_child);
      case TOKEN_R_PAREN:
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

/**
 * This function parses a term from the token stack.  Essentially just anything
 * that is a mathematical coefficient.
 * @param  ts - the token stack from which the term is read
 * @return .\ - the appropriate abstract syntrax tree to model the input
 */
ast * parse_term(token_stack ** ts) {
  ast * left_child = NULL;
  ast * right_child = NULL;
  if(ts[0]) {
    left_child = parse_factor(ts);
    switch(ts[0]->current->type) {
      case TOKEN_VAR:
      case TOKEN_NUMBER:
        return left_child;
      case TOKEN_MULT:
        ts[0] = pop_token(ts[0]);
        right_child = parse_term(ts);
        return binary_tree(init_ast("*", TOKEN_MULT), left_child, right_child);
      case TOKEN_DIV:
        ts[0] = pop_token(ts[0]);
        right_child = parse_term(ts);
        return binary_tree(init_ast("/", TOKEN_DIV), left_child, right_child);
      default:
        return left_child;
    }
  } else {
    return NULL;
  }
}

/**
 * This function is meant to parse a factor, just either a number/variable or an
 * expression within a parenthesis
 * @param   ts - the token stack to be parsed
 * @return tmp - the new abstract syntax tree from the factor
 */
ast * parse_factor(token_stack ** ts) {
  ast * tmp = NULL;
  ast * right_child = NULL;
  switch(ts[0]->current->type) {
    case TOKEN_VAR:
    case TOKEN_NUMBER:
      tmp = init_ast(ts[0]->current->t_literal, ts[0]->current->type);
      ts[0] = pop_token(ts[0]);
      if(ts[0]->current->type != TOKEN_POWER)
        return tmp;
      ts[0] = pop_token(ts[0]);
      right_child = parse_factor(ts);
      return binary_tree(init_ast("^", TOKEN_POWER), tmp, right_child);
    case TOKEN_L_PAREN:
      ts[0] = pop_token(ts[0]);
      tmp = parse_expression(ts);
      if(ts[0]->current->type == TOKEN_R_PAREN) {
        ts[0] = pop_token(ts[0]);
        if(ts[0]->current->type != TOKEN_POWER)
          return tmp;
        ts[0] = pop_token(ts[0]);
        right_child = parse_factor(ts);
        return binary_tree(init_ast("^", TOKEN_POWER), tmp, right_child);
      } else {
        fprintf(stderr, "[PARSER4]: UnMatched Parenthesis\nExiting\n");
        exit(1);
      }
    case TOKEN_SIN:
      ts[0] = pop_token(ts[0]);
      right_child = parse_factor(ts);
      return unary_tree(init_ast("sin", TOKEN_SIN), right_child);
    case TOKEN_COS:
      ts[0] = pop_token(ts[0]);
      right_child = parse_factor(ts);
      return unary_tree(init_ast("cos", TOKEN_COS), right_child);
    case TOKEN_TAN:
      ts[0] = pop_token(ts[0]);
      right_child = parse_factor(ts);
      return unary_tree(init_ast("tan", TOKEN_TAN), right_child);
    case TOKEN_ARC_SIN:
      ts[0] = pop_token(ts[0]);
      right_child = parse_factor(ts);
      return unary_tree(init_ast("arcsin", TOKEN_ARC_SIN), right_child);
    case TOKEN_ARC_COS:
      ts[0] = pop_token(ts[0]);
      right_child = parse_factor(ts);
      return unary_tree(init_ast("arccos", TOKEN_ARC_COS), right_child);
    case TOKEN_ARC_TAN:
      ts[0] = pop_token(ts[0]);
      right_child = parse_factor(ts);
      return unary_tree(init_ast("arctan", TOKEN_ARC_TAN), right_child);
    case TOKEN_LOG:
      ts[0] = pop_token(ts[0]);
      right_child = parse_factor(ts);
      return unary_tree(init_ast("log", TOKEN_LOG), right_child);
    default:
      fprintf(stderr, "[PARSER3]: Unrecognized token: `%s` type: `%s`\nExiting\n",
          ts[0]->current->t_literal, token_type_to_string(ts[0]->current->type));
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
