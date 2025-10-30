#include <stdlib.h>
#ifndef _pcb_
#define _pcb_

#include "pcb.h"

#endif
int pcb_max_size;

typedef struct{
    t_pcb* pcb;
    int first;
    int last;
    int size;
} t_pcb_queue;

void init_pcb_queue(t_pcb_queue* pcb_queue, int size){
    pcb_queue->pcb = (t_pcb*)malloc(sizeof(t_pcb)*pcb_max_size);
    pcb_queue->first=0;
    pcb_queue->last=-1;
    pcb_queue->size=0;
}

int is_empty_pcb(t_pcb_queue* pcb_queue){
    return pcb_queue->size==0;
}

int is_full_pcb(t_pcb_queue* pcb_queue){
    return pcb_queue->size==pcb_max_size;
}

int enqueue_pcb(t_pcb_queue* pcb_queue,t_pcb pcb){
    if(is_full_pcb(pcb_queue)){
        return 1;    
    }
    pcb_queue->last = (pcb_queue->last+1) %pcb_max_size;
    pcb_queue->pcb[pcb_queue->last]=pcb;
    pcb_queue->size++;
    return 0;
}

int dequeue_pcb(t_pcb_queue* pcb_queue, t_pcb* pcb){

    if(is_empty_pcb(pcb_queue)){
        return 1;
    }
    
    *pcb = pcb_queue->pcb[pcb_queue->first];
    pcb_queue->first= (pcb_queue->first+1) % pcb_max_size;
    pcb_queue->size--;
    return 0;     
}

int peek_pcb(t_pcb_queue* pcb_queue, t_pcb* pcb){
    if(is_empty_pcb(pcb_queue)){
        return 1;
    }
    *pcb=pcb_queue->pcb[pcb_queue->first];
    return 0;
}
