#include <stdio.h>
#include <unistd.h>
#include "../Funciones/machine.c"
#include "../Funciones/processQueue.c"
#include "../Estructuras/thread_args.h"
#include <pthread.h>


void dispacher(int cpu, int core, int thread, t_pcb pcb){
    machine.cpus[cpu].cores[core].threads[thread].process=pcb;
}

void asignar_trabajo(t_select *select){
    int min;
    int pos;
    for(int i=0;i<machine.libres_size;i++){
        if(machine.libres[i]==0){
            //TODO matematicas para calcular a que hilo corresponde
            select->cpu/(machine.cpus[0].count*machine.cpus[0].cores[0].count);
            select->core;
            select->thread;
            break;
        }
    }
}

void* scheduler_thread(void* args) {
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
    t_scheduler_args *scheduler_args=args;
    int cpu;
    int core;
    int thread;
    t_pcb pcb;
    t_select select;
    while(1){

        pthread_cond_wait(&cond_scheduler,&mutex_scheduler);
        if(scheduler_args->verbose){
            printf("scheduler activado\n");
            while(!is_empty_pcb(&process_queue)){
                dequeue_pcb(&process_queue,&pcb);
                asignar_trabajo(&select);
                
            }
            /*
            cpu=cpu % machine.count;
            core=core % machine.cpus[0].count;
            thread=thread % machine.cpus[0].cores[0].count;
            dispacher(cpu,core,thread,pcb);*/
            
        } 
        
    }
            
}

