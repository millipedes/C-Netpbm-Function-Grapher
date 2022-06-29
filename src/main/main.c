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
#include "../GraphingPackage/include/file_io.h"

int main(int argc, char * argv[]) {
  if(argc < 2) {
    fprintf(stderr, "Usage:\n./path_to/executable path_to/input.txt\n");
    exit(1);
  }
  write_outputs_from_input_cfg_file(argv[1]); // Write the input file to output
                                              // file(s)
}
