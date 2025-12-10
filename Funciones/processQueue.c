#include "../Estructuras/processQueue.h"

void init_pcb_queue(t_pcb_queue* pcb_queue, int size){
    pcb_queue->pcb = (t_pcb*)malloc(sizeof(t_pcb)* size);
    pcb_queue->first=0;
    pcb_queue->last=-1;
    pcb_queue->size=0;
    pcb_queue->max_size=size;
}

int is_empty_pcb(t_pcb_queue* pcb_queue){
    return pcb_queue->size==0;
}

int is_full_pcb(t_pcb_queue* pcb_queue){
    return pcb_queue->size==pcb_queue->max_size;
}

int enqueue_pcb(t_pcb_queue* pcb_queue,t_pcb pcb){
    if(is_full_pcb(pcb_queue)){
        return 0;    
    }
    pcb_queue->last = (pcb_queue->last+1) % pcb_queue->max_size;
    pcb_queue->pcb[pcb_queue->last]=pcb;
    pcb_queue->size++;
    return 1;
}

int dequeue_pcb(t_pcb_queue* pcb_queue, t_pcb* pcb){

    if(is_empty_pcb(pcb_queue)){
        return 0;
    }
    
    *pcb = pcb_queue->pcb[pcb_queue->first];
    pcb_queue->first= (pcb_queue->first+1) % pcb_queue->max_size;
    pcb_queue->size--;
    return 1;     
}

int peek_pcb(t_pcb_queue* pcb_queue, t_pcb* pcb){
    if(is_empty_pcb(pcb_queue)){
        return 0;
    }
    *pcb=pcb_queue->pcb[pcb_queue->first];
    return 1;
}
