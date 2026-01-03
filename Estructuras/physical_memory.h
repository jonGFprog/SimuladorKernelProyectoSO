#include <stdlib.h>
#ifndef PHYSICAL_MEMORY_H
#define PHYSICAL_MEMORY_H
#define MAX_PALABRAS 0xFFFFFF
#define RESERVA_KERNEL 0x3FFFFF


typedef struct{
    u_int32_t palabra[MAX_PALABRAS]; //posiciones del array de 4bytes. Entra una linea entera de los ficheros generados por prometheus
    int reserva_tabla=RESERVA_KERNEL; //reservadas las direcciones de memoria desde 0 a reserva_tabla
} t_physical_memory;

t_physical_memory memory;


#endif