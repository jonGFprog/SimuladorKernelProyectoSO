#include <stdint.h>
#ifndef LISTA_HUECOS_H
#define LISTA_HUECOS_H

typedef struct t_nodo_lista_huecos{
    t_nodo_lista_huecos* next;
    uint32_t frame; //el frame en el que empieza el hueco
    int numframes; //numero de frames que tiene el hueco
}t_nodo_lista_huecos;

typedef struct{
    t_nodo_lista_huecos* first;
}t_lista_huecos;

void init_lista_huecos(t_lista_huecos* lista_huecos, uint32_t max_frames);
void add_frames(t_lista_huecos* lista_huecos,int numframes,uint32_t *frames);
void borrar_hueco(t_lista_huecos* lista_huecos, uint32_t frame, int numframes);
uint32_t primer_hueco(t_lista_huecos* lista_huecos); //devuelve el primer frame libre
#endif