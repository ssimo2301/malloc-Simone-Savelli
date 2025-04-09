#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "malloc.h"




int main(){
	MallocAllocator allocator;
	printf("init...\n");
	MallocAllocator_init(&allocator);

	printf("\n--TEST DI ALLOCAZIONE PICCOLA--\n");
	void* small1 = MallocAllocator_malloc(&allocator, 512);
	void* small2 = MallocAllocator_malloc(&allocator, 1024);
	if(small1 && small2){
		printf("\nallocazioni piccole riuscite: %p, %p\n", small1, small2);
		strcpy((char*)small1, "ciao");
		strcpy((char*)small2, "mondo");
		printf("\ncontenuto: %s %s\n", (char*)small1, (char*)small2);
	}
	else{
		fprintf(stderr, "\nallocazione piccola fallita\n");
	}
	MallocAllocator_free(&allocator, small1);
	MallocAllocator_free(&allocator, small2);

	printf("\n--TEST DI ALLOCAZIONE GRANDE--\n");
	void* large1 = MallocAllocator_malloc(&allocator, PAGE_SIZE);
	void* large2 = MallocAllocator_malloc(&allocator, PAGE_SIZE*2);
	if(large1 && large2){
		printf("\nallocazione grande riuscita %p %p\n", large1, large2);
		memset(large1, 0xAA, PAGE_SIZE);
		memset(large2, 0xBB, PAGE_SIZE*2);
		printf("\nscrittura in memoria grande effettuata\n");
	} else {
		fprintf(stderr, "\nallocazione grande fallita\n");
	}
	MallocAllocator_free(&allocator, large1);
	MallocAllocator_free(&allocator, large2);
	printf("\n--TEST DI ALLOCAZIONI MISTE--\n");
	void* mixed[10];
	for(int i=0; i<10; i++){
		size_t size = (i%2==0) ? 128 : PAGE_SIZE;
		mixed[i] = MallocAllocator_malloc(&allocator, size);
		if(!mixed[i]){
			fprintf(stderr, "\nallocazione mista fallita\n");
		}
	}
	for(int i=0; i<10; i++){
		MallocAllocator_free(&allocator, mixed[i]);
	}
	printf("\ntutti i test completati con successo\n");
	return 0;
}
