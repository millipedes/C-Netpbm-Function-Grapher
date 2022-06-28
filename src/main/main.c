/**
 * Hard coded graph back end includes
 */
// #include <math.h>
// #include "../GraphingPackage/include/relation.h"
// #include "../GraphingPackage/include/file_io.h"
/**
 * Front end includes
 */
#include "../FunctionCFG/Token/include/token_stack.h"
#include "../FunctionCFG/Lexer/include/lexer.h"
#include "../FunctionCFG/Parser/include/parser.h"

// double x_squared(double x);

int main(void) {
  /**
   * As the front end of the program is currently in development, the hard coded
   * back-end functions have been left for reference for when I return to meet
   * the two
   */
  // canvas      * can = init_canvas(1000, 1000);
  // graph_scale * gs = init_graph_scale(
  //     init_axis_tic_marks(10, 5, 30, X),          // x axis tic marks
  //     init_axis_tic_marks(10, 30, 5, Y),          // y axis tic marks
  //     init_coord_axis(-10.0, 10.0, 2, X),         // x axis
  //     init_coord_axis(-10.0, 10.0, 2, Y),         // y axis
  //     init_graph_border(init_color(0, 0, 0), 10), // border of graph
  //     2                                           // no axes (don't change!)
  //     );
  // write_gs_to_canvas(can, gs);
  // color * green = init_color(0, 255, 0);
  // write_rel_to_canvas(can, gs, x_squared, green, 0.00001);
  // write_canvas_to_file("test.ppm", can);
  // free_color(green);
  // free_canvas(can);
  // free_graph_scale(gs);


  /**
   * Front end functions relating to CFG
   */
  lexer * lex = init_lexer("(2 + x)^(2 * 4 + 1) + 2\n");
  token_stack * tok_list = lex_source(lex);
  token_stack * rev = reverse_stack(&tok_list);

  ast * abstree = parse_expression(&rev);
  ast_pretty_print(abstree);
  free_ast(abstree);

  if(rev)
    while(rev) rev = pop_token(rev);
  free_lexer(lex);
  return 0;
}

// double x_squared(double x) {
//   return pow(x + 1, 2) - 3;
// }
