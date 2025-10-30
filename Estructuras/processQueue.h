#include <stdlib.h>
#ifndef _pcb_
#define _pcb_

#include "pcb.h"

#endif

typedef struct{
    t_pcb* pcb;
    int first;
    int last;
    int size;
} t_pcb_queue;

void init_pcb_queue(t_pcb_queue* pcb_queue, int size){
    pcb_queue->pcb = (t_pcb*)malloc(sizeof(t_pcb)*size);
    pcb_queue->first=0;
    pcb_queue->last=-1;
    pcb_queue->size=size;
}

int is_empty(t_pcb_queue* pcb_queue){
    if(pcb_queue->first==0){
        return 1;
    }
    return 0;
}

int is_full(t_pcb_queue* pcb_queue){
    if(pcb_queue->last==pcb_queue->size){
        return 1;
    }
    return 0;
}

void enqueue(){
    
}

void dequeue(){

}