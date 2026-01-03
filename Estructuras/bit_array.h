#include <stdint.h>
#ifndef BIT_ARRAY_H
#define BIT_ARRAY_H

typedef struct{
    uint8_t *bits;
    uint32_t num_bits;
    uint32_t num_bytes;
}t_bit_array;

void init_bit_array(t_bit_array* bit_array,uint32_t numframe);
uint32_t bytes_necesarios(uint32_t num_bits);
void bit_array_set(t_bit_array* bit_array, uint32_t bit);
void bit_array_clear(t_bit_array* bit_array, uint32_t bit);
uint8_t bit_array_get(t_bit_array* bit_array, uint32_t bit);
uint32_t bit_array_find_first(t_bit_array* bit_array, uint32_t bit);
uint32_t bit_array_libres(t_bit_array* bit_array);

#endif