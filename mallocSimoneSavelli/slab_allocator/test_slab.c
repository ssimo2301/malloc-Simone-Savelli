#include <stdio.h>
#include <stdlib.h>
#include "slab_allocator.h"


int main(){
	SlabAllocator *allocator = slab_allocator_create();

	Object *o1 = slabAllocator_object(allocator);
	o1->data = 42;

	Object *o2 = slabAllocator_object(allocator);
	o2->data = 99;

	slabAllocator_deallocateObject(allocator, o2);
	slabAllocator_destroy(allocator);

	return 0; 
}
     
