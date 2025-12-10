#include <stdlib.h>
#include "pcb.h"
#ifndef PROCESS_QUEUE_H
#define PROCESS_QUEUE_H

typedef struct{
    t_pcb* pcb;
    int first;
    int last;
    int size;
    int max_size;
} t_pcb_queue;

t_pcb_queue process_queue;

void init_pcb_queue(t_pcb_queue* pcb_queue, int size);
int is_empty_pcb(t_pcb_queue* pcb_queue);
int is_full_pcb(t_pcb_queue* pcb_queue);
int enqueue_pcb(t_pcb_queue* pcb_queue,t_pcb pcb);
int dequeue_pcb(t_pcb_queue* pcb_queue, t_pcb* pcb);
int peek_pcb(t_pcb_queue* pcb_queue, t_pcb* pcb);

#endif