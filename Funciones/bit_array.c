#include <stdint.h>
#include <stddef.h>
#include "../Estructuras/bit_array.h"
#ifndef BIT_ARRAY_C
#define BIT_ARRAY_C

void init_bit_array(t_bit_array* bit_array, uint32_t bit){
    bit_array->num_bits=bit;
    bit_array->num_bytes=bytes_necesarios(bit);
    bit_array->bits=calloc(bit_array->num_bytes,sizeof(uint8_t));
}
uint32_t bytes_necesarios(uint32_t num_bits){
    return (num_bits+7)/8;
}
void bit_array_set(t_bit_array* bit_array, uint32_t bit){
    if(!bit_array||bit>=bit_array->bits){
        return 1;
    }
    uint32_t i=bit/8;
    uint8_t bit_pos=bit%8;    
    bit_array->bits[i] |= (1 << bit_pos);
}
void bit_array_clear(t_bit_array* bit_array, uint32_t bit){
    if(!bit_array||bit>=bit_array->bits){
        return 1;
    }
    uint32_t i=bit/8;
    uint8_t bit_pos=bit%8;    
    bit_array->bits[i] &= ~(1 << bit_pos);
}
uint8_t bit_array_get(t_bit_array* bit_array, uint32_t bit){
    if(!bit_array||bit>=bit_array->bits){
        return 1;
    }
    uint32_t i=bit/8;
    uint8_t bit_pos=bit%8;    
    return (bit_array->bits[i] >>bit_pos)&1;
}
uint32_t bit_array_find_first(t_bit_array* bit_array, uint32_t bit){
    if(!bit_array||bit>=bit_array->bits){
        return 1;
    }
    
    for(uint32_t i=bit;i<bit_array->num_bits;i++){
        if(!bit_array_get(bit_array, i)){
            return i;
        }
    }
    return -1;
}
uint32_t bit_array_libres(t_bit_array* bit_array){ //numero de bits libres
    if(!bit_array)return 1;
    uint32_t libres=0;
    for(uint32_t i=0; i<bit_array->num_bits;i++){
        if(!bitarray_get(bit_array, i)) {
            libres++;
        }
    }
    return libres;
}
#endif