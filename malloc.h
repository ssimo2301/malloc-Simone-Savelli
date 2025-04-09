#pragma once

#include "buddy_allocator.h"
#include "mmap_allocator.h"
#include "bit_map.h"

#define BUDDY_MEMORY_SIZE (1024*1024) //1MB
#define PAGE_QUARTER (PAGE_SIZE/4)


typedef struct {
	BitMap bitmap;	
	BuddyAllocator buddy;	
	int bitmap_buffer[BitMap_getBytes(BUDDY_MEMORY_SIZE / PAGE_QUARTER) /sizeof(int)];
	MmapAllocator* mmap;
	char buddy_memory[BUDDY_MEMORY_SIZE];
	char buddy_meta_buffer[0x10000];
} MallocAllocator;





void MallocAllocator_init(MallocAllocator* allocator);

void* MallocAllocator_malloc(MallocAllocator* allocator, size_t size);

void MallocAllocator_free(MallocAllocator* allocator, void* ptr);

void MallocAllocator_destroy(MallocAllocator* allocator);

