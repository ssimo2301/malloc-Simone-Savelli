#include <stdio.h>
#include <stdlib.h>
#include "slab_allocator.h"


int main(){
	SlabAllocator *allocator = slab_allocator_create();

	Object *o1 = slabAllocator_object(allocator);
	o1->data = 42;

	Object *02 = slabAllocator_Object(allocator);
	o2->data = 99;

	slabAllocator_deallocateObject(allocator, o2);
	slabAllocator_destroy(allocator);

	return 0; 
}
     
