#include <stddef.h>
#ifndef PHYSICAL_MEMORY_H
#define PHYSICAL_MEMORY_H
#define MAX_PALABRAS 0xFFFFFF
#define RESERVA_KERNEL 0x3FFFFF


typedef struct{
    uint32_t palabra[MAX_PALABRAS]; //posiciones del array de 4bytes. Entra una linea entera de los ficheros generados por prometheus
    int reserva_tabla; //reservadas las direcciones de memoria desde 0 a reserva_tabla
} t_physical_memory;

t_physical_memory memory;
void init_memoria(t_physical_memory *memoria);
void insertar_palabra(); //copiar la palabra, marcar como usado en el bitarray y en la tabla de paginas
void borrar_palabra(); //marcar como no usado en el bitarray y en la tabla de paginas

#endif