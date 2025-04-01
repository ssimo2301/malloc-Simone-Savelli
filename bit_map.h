#pragma once
#include <stdio.h>

typedef struct {
	int *buffer;
	int buffer_size;
	int num_bits;
} BitMap;



int BitMap_getBytes(int bits);

void BitMap_init(BitMap* bit_map, int num_bits, int* buffer);

void BitMap_setBit(BitMap* bit_map, int bit_num, int status);

int BitMap_bit(const BitMap* bit_map, int bit_num);
