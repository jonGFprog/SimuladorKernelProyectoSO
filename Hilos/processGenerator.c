#include <stdio.h>
#include <unistd.h>
#include "../Funciones/processQueue.c"
#include "../Estructuras/thread_args.h"
#include <pthread.h>

void* procgen_thread(void* args) {
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
    t_procgen_args *procgen_args=args;
    init_pcb_queue(&process_queue,procgen_args->max_size);
    __uint64_t id=0;
    t_pcb pcb;
    while(1){
        pthread_cond_wait(&cond_procgen,&mutex_procgen);
        pcb.id=id;
        if(enqueue_pcb(&process_queue,pcb)){
            printf("pcb %d añadido\n",pcb.id);
            id++;
            //pthread_cond_signal((void *)procgen_args->cond_sch);
        }
        else{
            printf("pcb error\n");
        }
    }
    
}

