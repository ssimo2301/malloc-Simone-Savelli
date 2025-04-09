#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "malloc.h"




int main(){
	printf("init...\n");
	if(MallocAllocator_init() != 0){
		fprintf(stderr, "errore durante l'inizializzazione dell'allocatore\n");
		return -1;
	}
	printf("--TEST DI ALLOCAZIONE PICCOLA--\n");
	void* small1 = MallocAllocator_malloc(512);
	void* small2 = MallocAllocator_malloc(1024);
	if(small1 && small2){
		printf("allocazioni piccole riuscite: %p, %p\n", small1, small2);
		strcpy((char*)small1, "ciao");
		strcpy((char*)small2, "mondo");
		printf("contenuto: %s %s\n", (char*)small1, (char*)small2);
	}
	else{
		fprintf(stderr, "allocazione piccola fallita\n");
	}
	MallocAllocator_free(small1);
	MallocAllocator_free(small2);

	printf("--TEST DI ALLOCAZIONE GRANDE--\n");
	void* large1 = MallocAllocator_malloc(PAGE_SIZE);
	void* large2 = MallocAllocator_malloc(PAGE_SIZE*2);
	if(large1 && large2){
		printf("allocazione grande riuscita %p %p\n", large1, large2);
		memset(large1, 0xAA, PAGE_SIZE);
		memset(large2, 0xBB, PAGE_SIZE*2);
		printf("scrittura in memoria grande effettuata\n");
	} else {
		fprintf(stderr, "allocazione grande fallita\n");
	}
	MallocAllocator_free(large1);
	MallocAllocator_free(large2);
	printf("--TEST DI ALLOCAZIONI MISTE--\n");
	void* mixed[10];
	for(int i=0; i<10; i++){
		size_t size = (i%2==0) ? 128 : PAGE_SIZE;
		mixed[i] = MallocAllocator_malloc(size);
		if(!mixed[i]){
			fprintf(stderr, "allocazione mista fallita\n");
		}
	}
	for(int i=0; i<10; i++){
		MallocAllocator_free(mixed[i]);
	}
	printf("tutti i test completati con successo\n");
	return 0;
}
