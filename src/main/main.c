#include<stdio.h>
#include"../GraphingPackage/GraphEncoding/include/canvas.h"

int main(void) {
  printf("Hello World\n");
  canvas * can = init_canvas(3, 3);
  canvas_dump_debug(can);
  free_canvas(can);
  return 0;
}
