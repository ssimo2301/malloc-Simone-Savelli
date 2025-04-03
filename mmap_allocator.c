#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include <assert.h>
//#include <math.h>
//#include <string.h>
#include <sys/types.h>
//#include <sys/stat.h>
//#include <fcntl.h>
#include <sys/mman.h>
#include "mmap_allocator.h"

//#define PAGE_SIZE 4096


//crea un nuovo allocatore di memoria mmap
MmapAllocator* MmapAllocator_create(size_t size){
	MmapAllocator* allocator = (MmapAllocator*)malloc(sizeof(MmapAllocator));
	if(!allocator){
		perror("malloc failed");
		return NULL;
	}
	allocator->size = (size + PAGE_SIZE - 1) & ~(PAGE_SIZE-1);
	allocator->ptr = mmap(NULL, allocator->size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
	if(allocator->ptr == MAP_FAILED){
		perror("mmap failed");
		free(allocator);
		return NULL;
	}
	//printf("creazione riuscita\n");
	return allocator;
}


//distruggi l'allocatore di memoria mmap
void MmapAllocator_destroy(MmapAllocator* allocator){
	if(allocator){
		if(allocator->ptr && allocator->ptr!=MAP_FAILED){
			size_t alloc_size = (allocator->size + PAGE_SIZE - 1) & ~(PAGE_SIZE-1);
			if(munmap(allocator->ptr, alloc_size) != 0){
				perror("destroy failed");
			}
		}
		free(allocator);
	}
}


//alloca la memoria per un mmap
void* MmapAllocator_alloc(MmapAllocator* allocator, size_t size){
	if(!allocator || size>allocator->size){
		perror("error nell'allocazione");
		return NULL;
	}
	printf("allocazione riuscita");
	return allocator->ptr;
}







