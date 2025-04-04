#include <stdlib.h>

#include "buddy_allocator.h"
#include "mmap_allocator.h"
#include "malloc.h"

//#define BUFFER_SIZE 102400
//#define BUDDY_LEVELS 9
//#define MEMORY_SIZE (1024*1024)
//#define MIN_BUCKET_SIZE (MEMORY_SIZE>>(BUDDY_LEVELS))

char buffer[BUFFER_SIZE];
char memory[MEMORY_SIZE];

MallocAllocator alloc;



int main(){
	printf("init...\n");
	allocator = MallocAllocator_create();
	if(!allocator){
		printf("errore nella creazione\n");
		return 1;
	}
	printf("done");
	
	void* p1 = MallocAllocator_alloc(100);
	if(p1) printf("allocazione p1 riuscita\n");
	void* p2 = MallocAllocator_alloc(1500);
	if(p2) printf("allocazione p2 riuscita\n");
	void* p3 = MallocAllocator_alloc(100000);
	if(p3) printf("allocazione p3 riuscita\n");
	
	MallocAllocator_destroy(allocator);
}
