#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "buddy_allocator.h"

int levelIdx(size_t idx){
	return (int)floor(log2(idx));
};

int buddyIdx(int idx){
	if(idx&0x1)
		return idx-1;
	return idx+1;
}

int parentIdx(int idx){
	return idx/2;
}

int startIdx(int idx){
	return (idx-(1<<levelIdx(idx)));
}



int BuddyAllocator_calcSize(int num_levels){
	int list_items = 1<<(num_levels+1);
	int list_alloc_size = (sizeof(BuddyListItem)+sizeof(int))*list_items;
	return list_alloc_size;
}


BuddyListItem* BuddyAllocator_createListItem(BuddyAllocator* alloc, int idx, BuddyListItem* parent_ptr){
	BuddyListItem* item = (BuddyListItem*)PoolAllocator_getBlock(&alloc->list_allocator);
	item->idx = idx;
	item->level = levelIdx(idx);
	item->start = alloc->memory + ((idx-(1<<levelIdx(idx)))<<(alloc->num_levels-item->level))*alloc->min_bucket_size;
	item->size = (1<<(alloc->num_levels-item->level))*alloc->min_bucket_size;
	item->parent_ptr = parent_ptr;
	item->buddy_ptr = 0;
	List_pushBack(&alloc->free[item->level], (ListItem*)item);
	printf("Creating Item. idx: %d, level: %d, start: %p, size: %d\n", item->idx, item->level, item->start, item->size);
	return item;
}
void BuddyAllocator_destroyListItem(BuddyAllocator* alloc, BuddyListItem* item){
	int level = item->level;
	List_detach(&alloc->free[level], (ListItem*)item);
	printf("Destroying Item. level: %d, idx: %d, start: %p, size: %d\n", item->level, item->idx, item->start, item->size);
	PoolAllocatorResult release_result = PoolAllocator_releaseBlock(&alloc->list_allocator, item);
	assert(release_result == Success);
}


void BuddyAllocator_init(BuddyAllocator* alloc, int num_levels, char* buffer, int buffer_size, char* memory, int min_bucket_size){
	alloc->num_levels = num_levels;
	alloc->memory = memory;
	alloc->min_bucket_size = min_bucket_size;
	assert(num_levels < MAX_LEVELS);
	assert(buffer_size >= BuddyAllocator_calcSize(num_levels));
	int list_items = 1<<(num_levels+1);
	int list_alloc_size=(sizeof(BuddyListItem)+sizeof(int))*list_items;
	printf("BUDDY INITIALIZING\n");
	printf("\tlevels: %d", num_levels);
	printf("\tmax list entries %d bytes\n", (1<<num_levels)*min_bucket_size);
	char *list_start = buffer;
	PoolAllocatorResult init_result = PoolAllocator_init(&alloc->list_allocator, sizeof(BuddyListItem), list_items, 							     list_start, list_alloc_size);
	printf("%s\n", PoolAllocator_sterror(init_result));
	for(int i=0; i<MAX_LEVELS; i++)
		List_init(alloc->free+i);
	BuddyAllocator_createListItem(alloc, 1, 0);
}


BuddyListItem* BuddyAllocator_getBuddy(BuddyAllocator* alloc, int level){
	if(level < 0)
		return 0;
	assert(level <= alloc->num_levels);
	if(!alloc->free[level].size){
		BuddyListItem* parent_ptr = BuddyAllocator_getBuddy(alloc, level-1);
		if(!parent_ptr)
			return 0;
		int left_idx = parent_ptr->idx<<1;
		int right_idx = left_idx+1;
		printf("split l: %d, left_idx: %d, right_idx: %d\r", level, left_idx, right_idx);
		BuddyListItem* left_ptr = BuddyAllocator_createListItem(alloc, left_idx, parent_ptr);
		BuddyListItem* right_ptr = BuddyAllocator_createListItem(alloc, right_idx, parent_ptr);
		left_ptr->buddy_ptr = right_ptr;
		right_ptr->buddy_ptr = left_ptr;	
	}
	if(alloc->free[level].size){
		BuddyListItem* item = (BuddyListItem*)List_popFront(alloc->free+level);
		return item;
	}
	assert(0);
	return 0;
}


void BuddyAllocator_releaseBuddy(BuddyAllocator* alloc, BuddyListItem* item){
	BuddyListItem* parent_ptr = item->parent_ptr;
	BuddyListItem* buddy_ptr = item->buddy_ptr;
	List_pushFront(&alloc->free[item->level], (ListItem*)item);
	if(!parent_ptr)
		return;
	if(buddy_ptr->list.prev==0 && buddy_ptr->list.next==0)
		return;
	printf("merge %d\n", item->level);
	BuddyAllocator_destroyListItem(alloc, item);
	BuddyAllocator_destroyListItem(alloc, buddy_ptr);
	BuddyAllocator_releaseBuddy(alloc, parent_ptr);
}


void* BuddyAllocator_malloc(BuddyAllocator* alloc, int size){
	int mem_size = (1<<alloc->num_levels)*alloc->min_bucket_size;
	int level = floor(log2(mem_size/(size+8)));
	if(level>alloc->num_levels)
		level = alloc->num_levels;
	printf("requested: %d bytes, level %d\n", size, level);
	BuddyListItem* buddy = BuddyAllocator_getBuddy(alloc, level);
	if(!buddy)
		return 0;
	BuddyListItem** target = (BuddyListItem**)(buddy->start);
	*target = buddy;
	return buddy->start+8;
}


void BuddyAllocator_free(BuddyAllocator* alloc, void* mem){
	printf("freeing %p", mem);
	char *p = (char*) mem;
	p = p-8;
	BuddyListItem** buddy_ptr = (BuddyListItem**)p;
	BuddyListItem* buddy = *buddy_ptr;
	assert(buddy->start==p);
	BuddyAllocator_releaseBuddy(alloc, buddy);
}
