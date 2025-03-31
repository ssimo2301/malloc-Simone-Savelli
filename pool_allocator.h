typedef enum {
	Success = 0x0,
	NotEnoughMemory = -1,
	UnalignedFree = -2,
	OutOfRange = -3,
	DoubleFree = -4
} PoolAllocatorResult;

typedef stuct PoolAllocator{
	char* buffer;
	int* free_list;
	int buffer_size;

	int size;
	int size_max;
	int item_size;

	int first_idx;
	int bucket_size;
} PoolAllocator;



PoolAllocatorResult PoolAllocator_init(
	PoolAllocator* allocator, int item_size, int num_items, char* memory_block, int memory_size);

void* PoolAllocator_getBlock(
	PoolAllocator* allocator);

PoolAllocatorResult PoolAllocator_releaseBlock(
	PoolAllocator* allocator, void* block);

const char* PoolAllocator_sterror(
	PoolAllocatorResult result);
