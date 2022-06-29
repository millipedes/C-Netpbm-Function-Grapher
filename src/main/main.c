/**
 * @file   main.c
 * @brief  This file contains the entry point to the code, essentially just
 * passing the user's input file into a function that will read it and write the
 * correct output file(s).  See:
 * https://github.com/millipedes/C-Netpbm-Function-Grapher.git for more info
 * @author Matthew C. Lindeman
 * @date   June 28, 2022
 * @bug    None known
 * @todo   Nothing
 */
// #include <math.h>
// #include "../GraphingPackage/include/relation.h"
#include "../GraphingPackage/include/file_io.h"
// #include "../FunctionCFG/Token/include/token_stack.h"
// #include "../FunctionCFG/Lexer/include/lexer.h"
// #include "../FunctionCFG/Parser/include/parser.h"
int main(int argc, char * argv[]) {
// int main(void) {
  if(argc < 2) {
    fprintf(stderr, "Usage:\n./path_to/executable path_to/input.txt\n");
    exit(1);
  }
  write_outputs_from_input_cfg_file(argv[1]); // Write the input file to output
  //                                             // file(s)
  // canvas      * can = init_canvas(1000, 1000);
  // graph_scale * gs = init_graph_scale(
  //     init_axis_tic_marks(10, 5, 30, X),          // x axis tic marks
  //     init_axis_tic_marks(10, 30, 5, Y),          // y axis tic marks
  //     init_coord_axis(-20.0, 20.0, 2, X),         // x axis
  //     init_coord_axis(-20.0, 20.0, 2, Y),         // y axis
  //     init_graph_border(init_color(0, 0, 0), 10), // border of graph
  //     2                                           // no axes (don't change!)
  //     );
  // write_gs_to_canvas(can, gs);
  // color * green = init_color(0, 255, 0);
  // // write_rel_to_canvas(can, gs, x_squared, green, 0.00001);
  // /**
  //  * Front end functions relating to CFG
  //  */
  // lexer * lex = init_lexer("x\n");
  // token_stack * tok_list = lex_source(lex);
  // token_stack * rev = reverse_stack(&tok_list);

  // ast * abstree = parse_expression(&rev);
  // write_ast_to_canvas(can, gs, abstree, green, 0.00001);
  // write_canvas_to_file("test.ppm", can);
  // free_ast(abstree);

  // if(rev)
  //   while(rev) rev = pop_token(rev);
  // free_lexer(lex);
  // free_color(green);
  // free_canvas(can);
  // free_graph_scale(gs);return 0;
}
