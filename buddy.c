#include "linked_list.h"

typedef struct BuddyListItem{
	ListItem list;
	size_t tree_node;
	int level;
	int start;
	int end;
	struct BuddyListItem* buddy_ptr;
	struct Buddy;
} BuddyListItem;

inline int level(size_t tree_node){
	return (int)floor(log2(tree_node));
}

inline int buddy(int tree_node){
	if(tree_node & 0x1)
		return tree_node - 1;
	return tree_node + 1;
}

inline int parent(int tree_node){
	return tree_node/2;
} 

BuddyListItem* BuddyListItem_alloc(BuddyAllocator* allocator);

void BuddyListItem_free(BuddyAllocator* allocator, BuddyListItem* item);

BuddyListItem* BuddyListItem_alloc(int level, int start){
	BuddyListItem* item = (BuddyListItem*)malloc(sizeof(BuddyListItem));
	item->list.prev = 0;
	item->list.next = 0;
	item->level = level;
	item->start = start;
	item->end = 1<<(NUM_BUDDY_LEVELS - level - 1) + start;
	return item;
}

void BuddyListItem_free(BuddyListItem* item){
	free(item);
}

BuddyAllocator_init(BuddyAllocator* allocator){
	for(int i=0; i<NUM_BUDDY_LEVELS; i++)
		List_init(allocator->levels+i);
	BuddyListItem* root = BuddyListItem_alloc(0,0);
	List_insert(allocator->levels, NULL, root);
}

BuddyListItem* BuddyAllocator_get(BuddyAllocator* allocator, int level){
	if(allocator->levels[level].size){
		ListItem* item = List_detach(allocator->levels+level, allocator->levels[level].first);
		return (BuddyListItem*) item;
	}
	BuddyListItem* upper = BuddyAllocator_get(allocator, level-1);
	if(!upper)
		return 0;
	BuddyListItem* first_item = BuddyListItem_alloc(level, upper.start);
	BuddyListItem* second_item = BuddyListItem_alloc(level, first_item.end);
	BuddyListItem_free(upper);
	List_insert(allocator->levels+level, allocator->levels[level].last);
	return first_item;
}
