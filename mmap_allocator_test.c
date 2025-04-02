#include "mmap_allocator.h"
#include <stdio.h>

#define PAGE_SIZE 4096

MmapAllocator* allocator;



int main(){
	printf("init...\n");
	allocator = MmapAllocator_create(PAGE_SIZE);
	printf("done\n");
	
	void* p1 = MmapAllocator_alloc(&allocator, 100);
	void* p2 = MmapAllocator_alloc(&allocator, 100);
	void* p3 = MmapAllocator_alloc(&allocator, 100000);
	MmapAllocator_free(&allocator, p1);
	MmapAllocator_free(&allocator, p2);
	MmapAllocator_free(&allocator, p3);
}
