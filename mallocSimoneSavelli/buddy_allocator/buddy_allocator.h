#include <stdio.h>
#include <stdlib.h>

//blocco del buddy
typedef struct BuddyListItem{
  ListItem list;
  int index;  //indice dell'albero
  int level;  // livello del buddy
  char* start;  //inizio della zona di memoria
  int size;
  struct BuddyListItem* buddy_ptr;
  struct BuddyListItem* parent_ptr;
} BuddyListItem;


//allocatore del buddy
typedef struct {
  ListHead free[MAX_LEVELS];
  ListHead occupied[MAX_LEVELS];
  int num_levels;
  PoolAllocator list_allocator;  //allocatore degli elementi della lista
  int min_bucket_size;
} BuddyAllocator;


//allocatore di memoria
void* BuddyAllocator_malloc(*BuddyAllocator* alloc, int size);

 //restituisce il buddy
BuddyListItem* BuddyAllocator_getBuddy(BuddyAllocator* alloc, int level);

//rilascia il buddy
void BuddyAllocator_releaseBuddy(BuddyAllocator* alloc, BuddyListItem* item);

//free del buddy
void BuddyAllocator_free(BuddyAllocator* alloc, void* mem);

//inizializzazione del buddy
void BuddyAllocator_init(BuddyAllocator* alloc, int num_levels, char* buffer, int buffer_size, char* memory, int min_bucket_size);
