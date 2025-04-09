#include "malloc.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


void MallocAllocator_init(MallocAllocator* allocator){
	int num_levels = 8;
	int min_bucket_size = BUDDY_MEMORY_SIZE >> num_levels;
	BitMap_init(&allocator->bitmap, BUDDY_MEMORY_SIZE/PAGE_QUARTER,allocator->bitmap_buffer);
	BuddyAllocator_init(&allocator->buddy, num_levels, allocator->buddy_meta_buffer, sizeof(allocator->buddy_meta_buffer), allocator->buddy_memory, min_bucket_size);
	allocator->mmap = MmapAllocator_create(PAGE_SIZE*10);
}


void* MallocAllocator_malloc(MallocAllocator* allocator, size_t size){
	if(size < PAGE_QUARTER){
		void* ptr = BuddyAllocator_malloc(&allocator->buddy, size);
		if(!ptr) return NULL;
		size_t offset = (uintptr_t)ptr - (uintptr_t)allocator->buddy_memory;
		int index = offset / PAGE_QUARTER;
		BitMap_setBit(&allocator->bitmap, index, 1);
		return ptr;
	} else {
		return MmapAllocator_alloc(allocator->mmap, size);
	}
}


void MallocAllocator_free(MallocAllocator* allocator, void* ptr){
	uintptr_t p = (uintptr_t)ptr;
	uintptr_t base = (uintptr_t)allocator->buddy_memory;
	if(p>=base && p<base+BUDDY_MEMORY_SIZE){
		size_t offset = p-base;
		int index = offset/PAGE_QUARTER;
		if(BitMap_bit(&allocator->bitmap, index)){
			BitMap_setBit(&allocator->bitmap, index, 0);
			BuddyAllocator_free(&allocator->buddy, ptr);
		}
	} else {
		//nessuna mmap_free perchè nel nostro design è un unico grande blocco
	}
}


void MallocAllocator_destroy(MallocAllocator* allocator){
	MmapAllocator_destroy(allocator->mmap);
}

