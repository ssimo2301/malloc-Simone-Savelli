#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "buddy_allocator.h"

#define MIN_BLOCK_SIZE 16

static Buddy *free_list[32]; //array di liste libere
static int total_memory_size;

//funzione per calcolare la cella
static int ceil_log2(int n){
	return (int)ceil(log2(n));
}
//funzione per dividere un blocco in due parti
static void split(Buddy *block){
	int size = block->size / 2;
	block->size = size;
	Buddy *buddy = (Buddy*)((char*)block+size);
	buddy->size = size;
	buddy->is_free = 1;
	buddy->next = free_list[ceil_log2(size)];
	free_list[ceil_log2(size)] = buddy;
}

//funzione per cercare un blocco libero di dimensione sufficente
static Buddy *find_block(int size){
	int i = ceil_log2(size);
	while(i < 32){
		Buddy *block = free_list[i];
		if(block !=NULL){
			free_list[i] = block->next;
			return block;
		}
		i++;
	}
	return NULL;
}

//funzione per unire 2 blocchi 
static Buddy *merge(Buddy *block){
	int size = block->size * 2;
	int buddy_id = ((char*)block - (char*)free_list[ceil_log2(size)]) / size;
	Buddy *buddy = (Buddy*)((char*)free_list[ceil_log2(size)] + buddy_id * size);
	if (buddy->is_free && buddy->size==size){
		if(buddy==free_list[ceil_log2(size)]){
			free_list[ceil_log2(size)] = buddy->next;
		} else {
			Buddy *curr = free_list[ceil_log2(size)];
			while(curr->next != buddy){
				curr = curr->next;
			}
			curr->next = buddy->next;
		}
		if(block > buddy){
			block = buddy;
		}
		block->size = size;
		block->is_free = 1;
		return block;
	}
	return NULL;
}



//inizializza il buddy
void buddyAllocator_init(int size){
	total_memory_size = size;
	int level = ceil_log2(size);
	free_list[level] = (Buddy*)malloc(size);
	free_list[level]->size = size;
	free_list[level]->is_free = 1;
	free_list[level]->next = NULL;
}


//allocatore di memoria
void* buddyAllocator_malloc(int size){
	if(size<0|| size>total_memory_size)
		return NULL;
	
	size = (int)pow(2, ceil_log2(size));
	
	int i = ceil_log2(size);
	while(i<32){
		Buddy *block = find_block(size);
		if(block != NULL){
			while(block->size > size){
				split(block);
			}
			block->is_free = 0;
			return (void*)block;
		}
	}
	return NULL;
}


//free del buddy
void buddyAllocator_free(void* mem){
	if(mem == NULL)
		return;
	
	Buddy *block = (Buddy *)mem;
	block->is_free = 1;
	
	while(block->size < total_memory_size){
		Buddy *merged_block = merge(block);
		if(merged_block == NULL)
			break;
		block = merged_block;
	}
	block->next = free_list[ceil_log2(block->size)];
	free_list[ceil_log2(block->size)] = block;
}
 

//stampa lo stato del buddy
void buddyAllocator_print(){
	printf("stato del buddy:\n");
	for(int i=4; i<total_memory_size; i++){
		Buddy *curr = free_list[ceil_log2(i)];
		printf("size: %d\n", i);
		while(curr != NULL){
			printf("block address: %p, free: %s\n", curr, curr->is_free? "yes" : "no");
			curr = curr->next;
		}
	}
}
