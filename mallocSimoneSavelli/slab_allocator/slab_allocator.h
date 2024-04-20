#include <stdint.h>
#include <stdlib.h>

//interface
typedef struct {
  int data;
} Object;

typedef struct {
  Object *objects;
  int num_free;
  struct Slab *next;
} Slab;

typedef struct {
  Slab *slabs;
} SlabAllocator;


//creo il blocco di memoria
SlabAllocator* slab_allocator_create();

//distruggi lo slab
void SlabAllocator_destroy(SlabAllocator* allocator);

//restituisco l'oggetto
Object* SlabAllocator_getObject(PoolAllocator* allocator);

//rilascio il blocco di memoria
void SlabAllocator_deallocateObject(SlabAllocator* allocator, Object *obj);


