#include <stdio.h>
#include <stdlib.h>

//blocco del buddy
typedef struct BuddyListItem{
  int size;
  int is_free;
  struct Block *next;
} Buddy;

//inizializza il buddy
void buddyAllocator_init(int size);

//allocatore di memoria
void* buddyAllocator_malloc(int size);

//free del buddy
void buddyAllocator_free(void* mem);

//stampa lo stato del buddy
void buddyAllocator_print();


