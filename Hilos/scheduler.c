#include <stdio.h>
#include <unistd.h>
#include "../Funciones/machine.c"
#include "../Funciones/processQueue.c"
#include "../Estructuras/thread_args.h"
#include <pthread.h>


void dispacher(int cpu, int core, int thread, t_pcb pcb, t_pcb *exit_pcb){
    /*  machine.cpus[cpu].cores[core].threads[thread].process=pcb;
    if(machine.libres[cpu*core*thread-1]>0){
        machine.libres[cpu*core*thread-1]--;
    }*/
    *exit_pcb=machine.cpus[cpu].cores[core].threads[thread].process;
    machine.cpus[cpu].cores[core].threads[thread].process=pcb;

}

void asignar_trabajo(t_select *select, uint8_t partido){
    int min=INT32_MAX;
    int pos=-1;
    int cpu,core,thread;
    if (partido){
        for(int i=0;i<machine.total_threads;i++){
            cpu=i/(machine.cores_count*machine.threads_count);
            core=(i/machine.threads_count)%machine.cores_count;
            thread=i%machine.threads_count;
            if(machine.cpus[cpu].cores[core].threads[thread].partido.size==0){
                select->cpu=cpu;
                select->core=core;
                select->thread=thread;
                return;
            }
            else{
                if(machine.cpus[cpu].cores[core].threads[thread].partido.size<min){
                    pos=i;
                }
            }
        }
    }else{
        for(int i=0;i<machine.total_threads;i++){
            cpu=i/(machine.cores_count*machine.threads_count);
            core=(i/machine.threads_count)%machine.cores_count;
            thread=i%machine.threads_count;
            if(machine.cpus[cpu].cores[core].threads[thread].queue.size==0){
                select->cpu=cpu;
                select->core=core;
                select->thread=thread;
                return;
            }
            else{
                if(machine.cpus[cpu].cores[core].threads[thread].queue.size<min){
                    pos=i;
                }
            }
        }
    }
}

void* scheduler_thread(void* args) {
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
    t_scheduler_args *scheduler_args=args;
    t_pcb pcb;
    t_select select;
    int quantum=0;
    while(1){

        pthread_cond_wait(&cond_scheduler,&mutex_scheduler);
        if(scheduler_args->verbose){printf("scheduler activado\n");} 
        while(!is_empty_pcb(&process_queue)){
            dequeue_pcb(&process_queue,&pcb);//falta comprobar si es del partido y asignarlo a la cola del partido si lo es
            asignar_trabajo(&select,pcb.partido);
            enqueue_pcb(&machine.cpus[select.cpu].cores[select.core].threads[select.thread].queue,pcb);
        }
        for(int i=0;i<machine.total_threads;i++){

        }
        /*if(quantum>=machine.quantum){
            dispacher(select.cpu,select.core,select.thread,pcb,&pcb); //t_pcb pcb pasa de ser el pcb que entra en la cpu por el que sale
            quantum=0;
            if(pcb.ciclos_usados >= pcb.ciclos_asignados){
                continue;
            }
            if(pcb.fin==0){
                pcb.ciclos_usados+=machine.quantum;
                enqueue_pcb(&machine.cpus[select.cpu].cores[select.core].threads[select.thread].queue,pcb);
            }

        }
        else quantum++;*/
        
            /*
            cpu=cpu % machine.count;
            core=core % machine.cpus[0].count;
            thread=thread % machine.cpus[0].cores[0].count;
            dispacher(cpu,core,thread,pcb);*/
            
        
        
    }
            
}

