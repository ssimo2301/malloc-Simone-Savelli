#include <stdio.h>
#include <stdlib.h>
#include "buddy_allocator.h"
#include "slab_allocator.h"

typedef struct{
  buddy buddy;
  slab slab;
} allocator_helper;


void malloc_create();

void malloc_destroy();

void* malloc_alloc(size_t size);

char malloc_free(void* mall);
