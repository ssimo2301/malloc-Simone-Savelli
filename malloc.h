#pragma once
#include <stdlib.h>

#include "buddy_allocator.h"
#include "mmap_allocator.h"

#define PAGE_SIZE 4096


typedef struct {
	MmapAllocator mmap;
	BuddyAllocator buddy;
} MallocAllocator;





void MallocAllocator_create();

void MallocAllocator_destroy();

void* MallocAllocator_alloc(size_t size);

char MallocAllocator_free(void* ptr);

