#include <stdio.h>
#include <stdlib.h>
#include <buddy_allocator.h>


//allocatore di memoria
void* BuddyAllocator_malloc(*BuddyAllocator* alloc, int size){
  int mem_size = (1<<alloc->num_levels)*alloc->min_bucket_size;
  int level = floor(log2(mem_size/(size+8)));
  if(level > alloc->num_levels)
    level = alloc->num_levels;

  BuddyListItem* buddy = BuddyAllocator_getBuddy(alloc, level);
  if(!buddy) return 0;

  BuddyListItem** target = (BuddyListItem**)(buddy->start);
  *target = buddy;
  return buddy->start+8;
}



 //restituisce il buddy
BuddyListItem* BuddyAllocator_getBuddy(BuddyAllocator* alloc, int level){
  if(level < 0)
    return 0;
  if(!alloc->free[level].size){
    BuddyListItem* parent_ptr = BuddyAllocator_getBuddy(alloc, level-1);
    if(!parent_ptr)
      return 0;

    int left_idx = parent_ptr->idx<<1;
    int right_idx = left_idx+1;

    BuddyListItem* left_ptr = BuddyAllocator_createListItem(alloc, left_idx, parent_ptr);
    BuddyListItem* right_ptr = BuddyAllocator_createListItem(alloc, right_idx, parent_ptr);

    left_ptr->buddy_ptr = right_ptr;
    right_ptr->buddy_ptr = left_ptr;
  }
  if(alloc->free[level].size){
    BuddyListItem* item = (BuddyListItem*)list_popFront(alloc->free+level);
    return item;
  }
  return 0;
}



//rilascia il buddy
void BuddyAllocator_releaseBuddy(BuddyAllocator* alloc, BuddyListItem* item){
  BuddyListItem* parent_ptr = item->parent_ptr;
  BuddyListItem *buddy_ptr = item->buddy_ptr;

  List_pushFront(&alloc->free[item->level], (ListItem*)item);
  if(!parent_ptr)
    return;
  if(buddy_ptr->list.prev==0 && buddy_ptr->list.next==0)
    return;

  BuddyAllocator_destroyListItem(alloc, item);
  BuddyAllocator_destroyListItem(alloc, buddy_ptr);
  buddyAllocator_releaseBuddy(alloc, parent_ptr);
}



//free del buddy
void BuddyAllocator_free(BuddyAllocator* alloc, void* mem){
  char* p = (char*)mem;
  p=p-8;
  BuddyListItem** buddy_ptr = (BuddyListItem**)p;
  BuddyListItem* buddy = *buddy_ptr;
  assert(buddy->start==p);
  BuddyAllocator_releaseBuddy(alloc, buddy);
}



//inizializzazione del buddy
void BuddyAllocator_init(BuddyAllocator* alloc, int num_levels, char* buffer, int buffer_size, char* memory, int min_bucket_size){
  alloc->num_levels = num_levels;
  alloc->min_bucket_size = min_bucket_size;
  
}
