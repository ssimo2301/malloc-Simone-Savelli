#include "buddy_allocator.h"
#include <stdio.h>

#define BUFFER_SIZE 102400
#define BUDDY_LEVELS 9
#define MEMORY_SIZE (1024*1024)
#define MIN_BUCKET_SIZE (MEMORY_SIZE>>(BUDDY_LEVELS))


char buffer[BUFFER_SIZE];
char memory[MEMORY_SIZE];

BuddyAllocator alloc;


int main(){
	int req_size = BuddyAllocator_calcSize(BUDDY_LEVELS);
	printf("size requested for initialization %d/BUFFER_SIZE\n", req_size);
	printf("init...\n");
	BuddyAllocator_init(&alloc, BUDDY_LEVELS, buffer, BUFFER_SIZE, memory, MIN_BUCKET_SIZE);
	printf("done\n");

	printf("getting buddy of depth 7\n");
	BuddyListItem* item7_1 = BuddyAllocator_getBuddy(&alloc, 7);
	printf("getting another buddy of depth 7\n");
	BuddyListItem* item7_2 = BuddyAllocator_getBuddy(&alloc, 7);

	printf("getting buddy of depth 6\n");
	BuddyListItem* item6_1 = BuddyAllocator_getBuddy(&alloc, 6);
	printf("getting another buddy of depth 6\n");
	BuddyListItem* item6_2 = BuddyAllocator_getBuddy(&alloc, 6);

	printf("releasing a buddy of depth 7\n");
	BuddyAllocator_releaseBuddy(&alloc, item7_1);
	printf("releasing another buddy of depth 7\n");
	BuddyAllocator_releaseBuddy(&alloc, item7_2);
	printf("getting another buddy of depth 6\n");
	BuddyListItem* item6_3 = BuddyAllocator_getBuddy(&alloc, 6);

	printf("releasing a buddy of depth 6\n");
	BuddyAllocator_releaseBuddy(&alloc, item6_1);
	printf("releasing another buddy of depth 6\n");
	BuddyAllocator_releaseBuddy(&alloc, item6_2);
	printf("releasing another buddy of depth 6\n");
	BuddyAllocator_releaseBuddy(&alloc, item6_3);

	printf("getting buddy of depth 7\n");
	item7_1 = BuddyAllocator_getBuddy(&alloc, 7);
	printf("releasing a buddy of depth 7\n");
	BuddyAllocator_releaseBuddy(&alloc, item7_1);

}
