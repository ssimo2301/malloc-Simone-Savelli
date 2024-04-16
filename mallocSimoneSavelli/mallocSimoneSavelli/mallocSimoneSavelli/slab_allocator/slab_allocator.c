#include "slab_allocator.h"
#include <stdlib.h>
#include <stdio.h>

//inizializzo il blocco di memoria
PoolAllocatorResult PoolAllocator_init(PoolAllocator* allocator, int item_size, int num_items, char* memory_block, int memory_size){
  allocator = (PoolAllocator*)malloc(sizeof(PoolAllocator));
  if(allocator == NULL){
    perror("errore nella init del PoolAllocator slab");
    exit(EXIT_FAILURE);
  }
  allocator->item_size = item_size;
  allocator->size = num_items;
  allocator->buffer = memory_block;
  allocator->buffer_size = memory_size;

  return allocator;
}


//distruggi lo slab
void PoolAllocator_destroy(PoolAllocator* allocator){
  void *current = allocator->buffer;
  while(current != NULL){
    void *next = current->next;
    free(current->buffer);
    free(current);
    current = next;
  }
  free(allocator);
}


//restituisco il blocco di memoria
void* PoolAllocator_getBlock(PoolAllocator* allocator){
  return allocator->buffer;
}


//rilascio il blocco di memoria
PoolAllocatorResult PoolAllocator_releaseBlock(PoolAllocator* allocator, void*block){
  void *current = allocator->buffer;
  while(current != NULL){
    void *next = allocator->next;
    if(current == block){
      free(current->buffer);
      free(current);
      current = next;
    }
    current = next;
  }
  return allocator;
    
}


//stampo la stringa di errore
const char* PoolAllocator_sterror(PoolAllocatorResult result){
  return(result);
}
