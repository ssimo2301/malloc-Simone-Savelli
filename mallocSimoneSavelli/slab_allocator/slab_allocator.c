#include <stdlib.h>
#include <stdio.h>
#include "slab_allocator.h"

#define NUM_SLABS 5
#define NUM_OBJECT_FOR_SLAB 10

//creo il blocco di memoria
SlabAllocator* slab_allocator_create(){
	SlabAllocator *allocator = (SlabAllocator*)malloc(sizeof(SlabAllocator));
	if(allocator == NULL){
		perror("errore nell'allocazione di memoria");
		exit(EXIT_FAILURE);
	}

	allocator->slabs = NULL;

	return allocator;
}


//distruggi lo slab
void slabAllocator_destroy(SlabAllocator* allocator){
	Slab *current = allocator->slabs;
	while(current != NULL){
		Slab *next = current->next;
		free(current->objects);
		free(current);
		current = next;
	}

	free(allocator);
}


//alloca l'oggetto
Object* slabAllocator_object(SlabAllocator* allocator){
	Slab *current = allocator->slabs;
	while(current != NULL){
		if(current->num_free > 0){
			current->num_free--;
			return &(current->objects[current->num_free]);
		}
		current = current->next;
	}

	Slab *new_slab = (Slab*)malloc(sizeof(Slab));
	if(new_slab == NULL){
		perror("errore nell'allocazione dello slab");
		exit(EXIT_FAILURE);
	}

	new_slab->objects = (Object*)malloc(sizeof(Object) * NUM_OBJECT_FOR_SLAB);
	if(new_slab->objects == NULL){
		perror("errore nella allocazione dell'object");
		exit(EXIT_FAILURE);
	}

	new_slab->num_free = NUM_OBJECT_FOR_SLAB;
	new_slab->next = allocator->slabs;
	allocator->slabs = new_slab;

	return &(new_slab->objects[NUM_OBJECT_FOR_SLAB - 1]);
}


//rilascio il blocco di memoria
void slabAllocator_deallocateObject(SlabAllocator* allocator, Object *obj){
	Slab *current = allocator->slabs;
	while (current != NULL){
		if(obj >= current->objects && obj < current->objects+NUM_OBJECT_FOR_SLAB){
			current->num_free++;
			free(current);
			return;
		}
		current = current->next;
	}
	perror("oggetto non trovato");
}


//main
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
      
