#include "mmap_allocator.h"
#include <stdio.h>

#define PAGE_SIZE 4096

MmapAllocator* allocator;



int main(){
	printf("init...\n");
	allocator = MmapAllocator_create(PAGE_SIZE);
	if(!allocator){
		printf("errore nella creazione\n");
		return 1;
	}
	printf("done\n");
	
	void* p1 = MmapAllocator_alloc(allocator, 100);
	if(p1) printf("allocazione p1 riuscita");
	void* p2 = MmapAllocator_alloc(allocator, 100);
	if(p2) printf("allocazione p2 riuscita");
	void* p3 = MmapAllocator_alloc(allocator, 1000000);
	if(p3) printf("allocazione p3 riuscita");
	//MmapAllocator_free(&allocator, p1);
	//MmapAllocator_free(&allocator, p2);
	//MmapAllocator_free(&allocator, p3);

	MmapAllocator_destroy(&allocator);
}
