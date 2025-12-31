#include <stdio.h>
#include <unistd.h>
#include "../Funciones/processQueue.c"
#include "../Estructuras/thread_args.h"
#include <pthread.h>
#include "../Funciones/machine.c"

void* procgen_thread(void* args) {
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
    t_procgen_args *procgen_args=args;
    init_pcb_queue(&process_queue,procgen_args->max_size);
    __uint64_t id=1;
    float prob;
    t_pcb pcb;
    while(1){
        pthread_cond_wait(&cond_procgen,&mutex_procgen);        
        pcb.id=id;
        pcb.ciclos_usados=0;
        pcb.quantum=0;
        pcb.fin=0;
        pcb.partido=0;
        prob = rand() / (double)RAND_MAX;
        if(procgen_args->verbose)printf("prob = %f, prob_partido = %f\n", prob, procgen_args->prob_partido);
        if(prob<procgen_args->prob_partido){ 
            pcb.partido=1;
            pcb.paciencia=procgen_args->paciencia;
        }
        if(enqueue_pcb(&process_queue,pcb)){
            if(pcb.partido)printf("pcb del partido %d añadido\n",pcb.id);
            else printf("pcb %d añadido\n",pcb.id);
            id++;
            //pthread_cond_signal((void *)procgen_args->cond_sch);
        }
        else{
            printf("pcb error\n");
        }
    }
    
}

