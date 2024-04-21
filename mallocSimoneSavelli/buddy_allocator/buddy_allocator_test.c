#include "buddy_allocator.h"
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 102400
#define BUDDY_LEVELS 9
#define MEMORY_SIZE (1024*1024)
#define MIN_BUCKET_SIZE (MEMORY_SIZE>>(BUDDY_LEVELS))

char buffer[BUFFER_SIZE];
char memory[MEMORY_SIZE];

BuddyAllocator alloc;
int main(){
  int req_size = BuddyAllocator_calcSize(BUDDY_LEVELS);
  printf("size requested for inizialization: %d\n", req_size);
  printf("init...\n");
  BuddyAllocator_init(&alloc, BUDDY_LEVELS, buffer, BUFFER_SIZE, memory, MIN_BUCKET_SZIE);
  printf("done\n");
  void* p1 = BuddyAllocator_malloc(100);
  void* p2 = BuddyAllocator_malloc(100);
  void* p3 = BuddyAllocator_malloc(100000);
  BuddyAllocator_free(p1);
  BuddyAllocator_free(p2);
  BuddyAllocator_free(p3);
}
