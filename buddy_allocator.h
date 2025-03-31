#include "pool_allocator.h"
#include "linked_list.h"

#define MAX_LEVELS 16

typedef struct BuddyListItem{
	ListItem list;
	int idx;
	int level;
	char* start;
	int size;
	struct BuddyListItem* buddy_ptr;
	struct BuddyListItem* parent_ptr;
} BuddyListItem;

typedef struct {
	ListHead free[MAX_LEVELS];
	int num_levels;
	PoolAllocator list_allocator;
	char* memory;
	int min_bucket_size;
} BuddyAllocator;





int BuddyAllocator_calcSize(int num_levels);

void BuddyAllocator_init(
	BuddyAllocator* alloc, int num_levels, char* buffer, int buffer_size, char* memory, int min_bucket_size);

BuddyListItem* BuddyAllocator_getBuddy(BuddyAllocator* alloc, int level);

void BuddyAllocator_releaseBuddy(BuddyAllocator* alloc, BuddyListItem* item);

void* BuddyAllocator_malloc(BuddyAllocator* alloc, int size);

void BuddyAllocator_free(BuddyAllocator* alloc, void* mem);


