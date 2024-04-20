#include <stdio.h>
#include <stdlib.h>
#include "malloc.h"
#include "slab_allocator.h"
#include "buddy_allocator.h"

void main(){
  fprintf("main");
  char *block1, *block2, *block3;
  block1 = malloc_alloc(10);
  fprintf("allocazione 10 Byte: %p\n", block1);
  block2 = malloc_alloc(100);
  fprintf("allocazione 100 Byte: %p\n", block1);
  block3 = malloc_alloc(1000);
  fprintf("allocazione 1000 Byte: %p\n", block1);
  fprintf("fine main\n");
  return 0;
}
