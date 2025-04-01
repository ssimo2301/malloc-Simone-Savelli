#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <math.h>
#include "mmap_allocator.h"

#define PAGE_SIZE 4096


//crea un nuovo allocatore di memoria mmap
MmapAllocator* MmapAllocator_create(size_t size){
	MmapAllocator* allocator = (MmapAllocator*)malloc(sizeof(MmapAllocator));
	if(!allocator){
		perror("malloc failed");
		return -1;
	}
	allocator->size = (size + PAGE_SIZE - 1) & ~(PAGE_SIZE-1);
	allocator->ptr = mmap(NULL, allocator->size, PROT_READ|PROT_WRITE, MAP_PRIVATE, -1, 0);
	if(allocator->ptr == MAP_FAILED){
		perror("mmap failed");
		return -1;
	}
	return allocator;
}


//distruggi l'allocatore di memoria mmap
void MmapAllocator_destroy(MmapAllocator* allocator){
	if(munmap(allocator->ptr, allocator->size) != 0){
		perror("munmap failed");
		return -1;
	}
	free(allocator);
}


//alloca la memoria per un mmap
void* MmapAllocator_alloc(MmapAllocator* allocator, size_t size){
	if(!allocator || size>allocator->size){
		perror("error nall'allocazione");
		return -1;
	}
	return allocator->ptr;
}


//libera la memoria di una mmap
void MmapAllocator_free(MmapAllocator* allocator, void* mem){
	size_t alloc_size = (allocator->size + PAGE_SIZE -1) & ~(PAGE_SIZE - 1);
	if(munmap(allocator->ptr, alloc_size) != 0){
		perror("munmap failed");
		return -1;
	}
}




