#include <stdint.h>
#include <stdlib.h>

//interface
typedef enum{
  Success=0x0;
  NotEnoughMemory = -1;
  Unalignedfree = -2;
  OutOfRange = -3;
  DoubleFree = -4;
} PoolAllocatorResult;

typedef struct PoolAllocator{
  char* buffer;
  int* free_list;
  int buffer_size; //size del buffer
  int size; //numero di blocchi liberi
  int size_max; //numero massimo di blocchi
  int item_size; //size del blocco
  int first_idx; //punto del primo blocco
  int bucket_size //size del bucket
} PoolAllocator


//inizializzo il blocco di memoria
PoolAllocatorResult PoolAllocator_init(PoolAllocator* allocator, int item_size, int num_items, char* memory_block, int memory_size);

//distruggi lo slab
void PoolAllocator_destroy(PoolAllocator* allocator);

//restituisco il blocco di memoria
void* PoolAllocator_getBlock(PoolAllocator* allocator);

//rilascio il blocco di memoria
PoolAllocatorResult PoolAllocator_releaseBlock(PoolAllocator* allocator, void*block);

//stampo la stringa di errore
const char* PoolAllocator_sterror(PoolAllocatorResult result);
