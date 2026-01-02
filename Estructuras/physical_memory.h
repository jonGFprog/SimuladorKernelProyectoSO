#include <stdlib.h>
#ifndef PHYSICAL_MEMORY_H
#define PHYSICAL_MEMORY_H

typedef struct{
    u_int32_t *palabra; //posiciones del array de 4bytes
    int reserva_tabla; //reservadas las direcciones de memoria desde 0 a reserva_tabla
} t_physical_memory;

t_physical_memory memory;


#endif