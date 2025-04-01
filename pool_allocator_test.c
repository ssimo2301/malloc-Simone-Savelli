#include <stdio.h>
#include "pool_allocator.h"

#define item_size 4096
#define num_items 16
#define buffer_size num_items*(item_size+sizeof(int))

char buffer[buffer_size];
PoolAllocator allocator;

int main(){
	printf("initializing...");
	PoolAllocatorResult init_result = PoolAllocator_init(&allocator,item_size,num_items,buffer,buffer_size);
	printf("%s\n", PoolAllocator_sterror(init_result));

	void* blocks[num_items+10];

	//allocation memory
	for(int i=0; i<num_items+10; i++){
		void* block = PoolAllocator_getBlock(&allocator);
		blocks[i] = block;
		printf("allocation %d, block %p, size %d\n", i, block, allocator.size);
	}
	
	//release all memory
	for(int i=0; i<num_items+10; i++){
		void* block = blocks[i];
		if(block){
			printf("releasing...idx: %d, block %p, free %d ...", i, block, allocator.size);
			PoolAllocatorResult release_result = PoolAllocator_releaseBlock(&allocator, block);
			printf("%s\n", PoolAllocator_sterror(release_result));
		}
	}

	//release all memory (again)
	for(int i=0; i<num_items+10; i++){
		void* block = blocks[i];
		if(block){
			printf("releasing...idx: %d, block %p, free %d ...", i, block, allocator.size);
			PoolAllocatorResult release_result = PoolAllocator_releaseBlock(&allocator, block);
			printf("%s\n", PoolAllocator_sterror(release_result));
		}
	}

	//allocate half of memory, release it in reverse order
	for(int i=0; i<num_items-5; i++){
		void* block = PoolAllocator_getBlock(&allocator);
		blocks[i] = block;
		printf("allocation %d, block %p, size %d\n", i, block, allocator.size);
	}
	for(int i=num_items-1; i>=0; i--){
		void* block = blocks[i];
		if(block){
			printf("releasing...idx: %d, block %p, free %d ...", i, block, allocator.size);
			PoolAllocatorResult release_result = PoolAllocator_releaseBlock(&allocator, block);
			printf("%s\n", PoolAllocator_sterror(release_result));
		}
	}

	//uguale a sopra ma con tutta la memoria
	for(int i=0; i<num_items; i++){
		void* block = PoolAllocator_getBlock(&allocator);
		blocks[i] = block;
		printf("allocation %d, block %p, size %d\n", i, block, allocator.size);
	}
	for(int i=num_items-1; i>=0; i-=2){
		void* block = blocks[i];
		if(block){
			printf("releasing...idx: %d, block %p, free %d ...", i, block, allocator.size);
			PoolAllocatorResult release_result = PoolAllocator_releaseBlock(&allocator, block);
			printf("%s\n", PoolAllocator_sterror(release_result));
		}
	}
	for(int i=num_items-2; i>=0; i-=2){
		void* block = blocks[i];
		if(block){
			printf("releasing...idx: %d, block %p, free %d ...", i, block, allocator.size);
			PoolAllocatorResult release_result = PoolAllocator_releaseBlock(&allocator, block);
			printf("%s\n", PoolAllocator_sterror(release_result));
		}
	}
}
		
		
