#include <stdio.h>
#include <unistd.h>
#include "../Estructuras/processQueue.h"
#ifndef _thread_args_
#define _thread_args_

#include "../Estructuras/thread_args.h"
#include <pthread.h>

#endif
void* procgen_thread(void* args) {
    t_procgen_args *procgen_args=args;
    t_pcb_queue process_queue;
    init_pcb_queue(&process_queue,procgen_args->max_size);
    __uint64_t id=0;
    t_pcb pcb;
    while(1){
        usleep((int)procgen_args->frec*0.8+(rand()%procgen_args->frec*0.4));
        pcb.id=id;
        if(enqueue_pcb(&process_queue,pcb)){
            printf("pcb %d añadido\n",pcb.id);
            id++;
        }
        else{
            printf("pcb error\n");
        }
        
    }
}

