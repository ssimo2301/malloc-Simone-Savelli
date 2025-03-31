#include "pool_allocator.h"

static const int NullIdx = -1;
static const int DetachIdx = -2;

static const char* PoolAllocator_sterrors[]=
	 {"Success", "NotEnoughMemory", "UnalignedFree", "OutOfRange", "DoubleFree", 0};





PoolAllocatorResult PoolAllocator_init(
		PoolAllocator* allocator, int item_size, int num_items, char* memory_block, int memory_size){
	int requested_size = num_items*(item_size+sizeof(int));
	if(memory_size < requested_size)
		return NotEnoughMemory;
	allocator->item_size = item_size;
	allocator->size = num_items;
	allocator->buffer_size = item_size*num_items;
	allocator->size_max = num_items;
	allocator->buffer = memory_block;
	allocator->free_list = (int*)(memory_block + item_size * num_items);

	for(int i=0; i<allocator->size-1; i++){
		allocator->free_list[i] = i+1;
	}
	allocator->free_list[allocator->size-1] = NullIdx;
	allocator->first_idx = 0;
	return Success;
}



void* PoolAllocator_getBlock(PoolAllocator* allocator){
	if(allocator->first_idx == -1)
		return 0;
	int detached_idx = allocator->first_idx;
	allocator->first_idx = allocator->free_list[allocator->first_idx];
	--allocator->size;
	allocator->free_list[detached_idx] = DetachedIdx;
	char* block_address = allocator->buffer + (detached_idx * allocator->item_size);
	return block_address;
}



PoolAllocatorResult PoolAllocator_releaseBlock(PoolAllocator* allocator, void* block){
	char* block = (char*)block_;
	int offset = block - allocator->buffer;
	if(offset % allocator->item_size)
		return UnalignedFree;
	int idx = offset / allocator->item_size;
	if(idx<0 || idx>=allocator->size_max)
		return OutOfRange;
	if(allocator->free_list[idx] != DetachedIdx)
		return DoubleFree;
	allocator->free_list[idx] = allocator->first_idx;
	allocator->first_idx = idx;
	++a->size;
	return Success;
}



const char* PoolAllocator_sterror (PoolAllocatorResult result){
	return PoolAllocator_sterrors[-result];
}
