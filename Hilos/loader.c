#include <stdio.h>
#include <unistd.h>
#include "../Funciones/processQueue.c"
#include "../Estructuras/thread_args.h"
#include <pthread.h>
#include "../Funciones/machine.c"

void* loader(void* args) {
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
    t_loader_args *loader_args=args;
    init_pcb_queue(&process_queue,loader_args->max_size);
    __uint64_t id=1;
    float prob;
    t_pcb pcb;
    while(1){
        pthread_cond_wait(&cond_loader,&mutex_loader);        
        pcb.id=id;
        pcb.ciclos_usados=0;
        pcb.quantum=0;
        pcb.fin=0;
        pcb.partido=0;
        prob = rand() / (double)RAND_MAX;
        if(loader_args->verbose)printf("prob = %f, prob_partido = %f\n", prob, loader_args->prob_partido);
        if(prob<loader_args->prob_partido){ 
            pcb.partido=1;
            pcb.paciencia=loader_args->paciencia;
        }
        //CARGAR EN MEMORIA
        if(enqueue_pcb(&process_queue,pcb)){
            if(pcb.partido)printf("pcb del partido %d añadido\n",pcb.id);
            else printf("pcb %d añadido\n",pcb.id);
            id++;
            //pthread_cond_signal((void *)procgen_args->cond_sch);
        }
        else{
            printf("pcb error, processs_queue llena\n");
        }
    }
    
}

