#include <stdint.h>
#include <stddef.h>
#include "../Estructuras/lista_huecos.h"
#ifndef LISTA_HUECOS_C
#define LISTA_HUECOS_C
void init_lista_huecos(t_lista_huecos* lista_huecos, uint32_t max_frames){
    t_nodo_lista_huecos *nodo=malloc(sizeof(t_nodo_lista_huecos));
    nodo->frame=0;
    nodo->numframes=max_frames;
    nodo->next=NULL;
    lista_huecos->first=nodo;
}
int add_frames(t_lista_huecos* lista_huecos,int numframes,uint32_t *frames_libres){ //si devuelve algo distinto de 0, ignorar el resultado en frames_libres
    t_nodo_lista_huecos *tmp=lista_huecos->first;
    int frames_libres=0;
    while(tmp!=NULL && (frames_libres<numframes)){ //mirar si hay huecos suficientes
        frames_libres+=tmp->numframes;
        
        tmp=tmp->next;
    }
    if(frames_libres<numframes)return 1;



}
void borrar_hueco(t_lista_huecos* lista_huecos, uint32_t frame, int numframes);
uint32_t primer_hueco(t_lista_huecos* lista_huecos); //devuelve el primer frame libre
#endif