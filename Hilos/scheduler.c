#include <stdio.h>
#include <unistd.h>
#include "../Funciones/machine.c"
#include "../Estructuras/thread_args.h"
#include <pthread.h>

void dispacher(int cpu, int core, int thread, t_pcb pcb){
    machine.cpus[cpu].cores[core].threads[thread].process=pcb;
}

void* scheduler_thread(void* args) {
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
    t_scheduler_args *scheduler_args=args;
    while(1){
        pthread_cond_wait(&cond_scheduler,&mutex_scheduler);
        if(scheduler_args->verbose){
            printf("scheduler activado\n");
        } 
        
    }
            
}

