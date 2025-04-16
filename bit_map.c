#include <assert.h>
#include "bit_map.h"



int BitMap_getBytes(int bits){
	return bits/8 + (bits%8)!=0;
}


void BitMap_init(BitMap* bit_map, int num_bits, int* buffer){
	bit_map->buffer = buffer;
	bit_map->num_bits = num_bits;
	bit_map->buffer_size = BitMap_getBytes(num_bits);
}


void BitMap_setBit(BitMap* bit_map, int bit_num, int status){
	if(bit_num >= bit_map->buffer_size*8){
		fprintf(stderr, "Errore: bit_num %d fuori dal range della bitmap\n", bit_num);
		return;
	}	
	int byte_num = bit_num>>3;	
	assert(byte_num < bit_map->buffer_size);
	int bit_in_byte = byte_num&0x03;
	if(status)
		bit_map->buffer[byte_num] |= (1<<bit_in_byte);
	else
		bit_map->buffer[byte_num] &= ~(1<<bit_in_byte);
}


int BitMap_bit(const BitMap* bit_map, int bit_num){
	int byte_num = bit_num>>3;
	int bit_in_byte = byte_num&0x03;
	if(byte_num >= bit_map->buffer_size){
		fprintf(stderr, "Errore: bit_num=%d è fuori dai limiti della bitmap (buffer_size=%d bytes)\n", bit_num, bit_map->buffer_size);	
	}
	//assert(byte_num < bit_map->buffer_size);
	
	return (bit_map->buffer[byte_num] & (1<<bit_in_byte))!=0;
}
