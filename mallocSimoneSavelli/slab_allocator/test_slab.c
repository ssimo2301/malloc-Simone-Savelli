#include <stdio.h>
#include <stdlib.h>

int main(){
  bitmap map;
  bitmap_init(&map, 128, malloc(4*sizeof(int)));
  slab slab;
  slab_init(
	    &slab,
	    malloc(128*sizeof(int)),
	    map,
	    128*sizeof(int),
	    sizeof(int));

  printf("test di allocazione");
  void* punt[32];
  for(int i=0; i<32; i++){
    punt[i] = PoolAllocator_init(&slab);
    printf("%p\n", punt[i]);
  }

  printf("test di deallocazione");
  for(int i=0; i<32; i++){
    int res = PoolAllocator_destroy(&slab, punt[31-i]);
    printf("iterazione %d\n", res);
  }
  return 0;
}
      
	    
