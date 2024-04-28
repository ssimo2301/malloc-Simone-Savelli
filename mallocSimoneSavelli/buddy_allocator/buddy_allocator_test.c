#include "buddy_allocator.h"
#include "buddy_allocator.c"
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 102400
#define BUDDY_LEVELS 9
#define MEMORY_SIZE (1024*1024)
#define MIN_BUCKET_SIZE (MEMORY_SIZE>>(BUDDY_LEVELS))

char buffer[BUFFER_SIZE];
char memory[MEMORY_SIZE];

Buddy alloc;
int main(){
  printf("init...\n");
  void* p1 = buddyAllocator_malloc(100);
  void* p2 = buddyAllocator_malloc(100);
  void* p3 = buddyAllocator_malloc(100000);
  buddyAllocator_free(p1);
  buddyAllocator_free(p2);
  buddyAllocator_free(p3);
}
