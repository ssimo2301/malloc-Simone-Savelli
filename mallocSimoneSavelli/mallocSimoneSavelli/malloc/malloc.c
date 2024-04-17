#include <stdio.h>
#include <stdlib.h>
#include "malloc.h"
#include "slab_allocator.h"
#include "buddy_allocator.h"

allocator_helper helper;

void malloc_create(){
  
}


void malloc_destroy(){
  fprintf("destroy\n");
  helper_destroy(&(helper.mhelper), size);
  fprintf("distrutto\n");
}


void* malloc_alloc(size_t size){
  if(size >= 64)
    return buddy_allocator_malloc(&(helper.buddy), size);
  else if(size < 64)
    return slab_allocator_malloc(&(helper.slab), size);
  else if (size < 0 || size > 256)
    return -1;
}


char malloc_free(void* mall){
  PoolAllocator_destroy(&(helper.slab), mem);
  BuddyAllocator_free(&(helper.buddy), mem);
  return 0;
}
