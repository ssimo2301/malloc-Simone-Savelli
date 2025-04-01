#define PAGE_SIZE 4096

typedef struct {
	void* ptr;
	size_t size;
} MmapAllocator;


//crea un nuovo allocatore di memoria mmap
MmapAllocator* MmapAllocator_create(size_t size);

//distruggi l'allocatore di memoria mmap
void MmapAllocator_destroy(MmapAllocator* allocator);

//alloca la memoria per un mmap
void* MmapAllocator_alloc(MmapAllocator* allocator, size_t size);

//libera la memoria di una mmap
void MmapAllocator_free(MmapAllocator* allocator, void* mem);


