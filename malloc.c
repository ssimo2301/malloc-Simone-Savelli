#include <stdlib.h>

#include "buddy_allocator.h"
#include "mmap_allocator.h"
#include "malloc.h"


MallocAllocator alloc;


void MallocAllocator_create(){
	alloc = MmapAllocator_create(PAGE_SIZE);
	BuddyAllocator_init(&alloc->buddy, BUDDY_LEVELS, buffer, BUFFER_SIZE, memory, MIN_BUCKET_SIZE);
}


void MallocAllocator_destroy(){
	MmapAllocator_destroy(alloc->mmap);
	BuddyAllocator_free(&alloc->buddy, *mem);	
}


void* MallocAllocator_alloc(size_t size){
	if(size > PAGE_SIZE){
		perror("alloc failed, size troppo grande");
	else if(size > PAGE_SIZE/4){
		MmapAllocator_alloc(alloc->mmap, size);
		printf("alloc della mmap riuscita");
	}
	else if(size > 0){
		BuddyAllocator_malloc(alloc->buddy, size);
		printf("alloc del buddy riuscito");
	}
	else{
		perror("size minore di 0");
	}
}


//char MallocAllocator_free(void* ptr){}

