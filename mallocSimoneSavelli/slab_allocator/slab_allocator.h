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
void slabAllocator_destroy(SlabAllocator* allocator);

//restituisco l'oggetto
Object* slabAllocator_object(SlabAllocator* allocator);

//rilascio il blocco di memoria
void slabAllocator_deallocateObject(SlabAllocator* allocator, Object *obj);


