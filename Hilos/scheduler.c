#include <stdio.h>
#include <unistd.h>
#include "../Funciones/machine.c"
#include "../Funciones/processQueue.c"
#include "../Estructuras/thread_args.h"
#include <pthread.h>


void dispacher(int cpu, int core, int thread, t_pcb pcb, t_pcb *exit_pcb, int verbose){
    /*  machine.cpus[cpu].cores[core].threads[thread].process=pcb;
    if(machine.libres[cpu*core*thread-1]>0){
        machine.libres[cpu*core*thread-1]--;
    }*/
    *exit_pcb=machine.cpus[cpu].cores[core].threads[thread].process;
    machine.cpus[cpu].cores[core].threads[thread].process=pcb;
    if(verbose) printf("PCB id:%d asignado a %d,%d,%d\n",machine.cpus[cpu].cores[core].threads[thread].process.id,cpu,core,thread);

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

void* scheduler_thread(void* args) { //quizas cambiar el scheduler de hilo a funcion
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
    t_scheduler_args *scheduler_args=args;
    t_pcb pcb;
    t_select select;
    int cpu,core,thread;
    while(1){

        pthread_cond_wait(&cond_scheduler,&mutex_scheduler);
        if(scheduler_args->verbose){printf("scheduler activado\n");} 
        while(!is_empty_pcb(&process_queue)){
            dequeue_pcb(&process_queue,&pcb);
            asignar_trabajo(&select,pcb.partido);
            if(pcb.partido){
                enqueue_pcb(&machine.cpus[select.cpu].cores[select.core].threads[select.thread].partido,pcb);
                if(scheduler_args->verbose){printf("pcb %d añadido al partido (%d,%d,%d)\n",pcb.id,select.cpu,select.core,select.thread);} 
            }
            else{
                enqueue_pcb(&machine.cpus[select.cpu].cores[select.core].threads[select.thread].queue,pcb);
                if(scheduler_args->verbose){printf("pcb %d añadido a la queue (%d,%d,%d)\n",pcb.id,select.cpu,select.core,select.thread);}
            }
            
        }
        for(int i=0;i<machine.total_threads;i++){ //falta que hacer si es del partido
            cpu=i/(machine.cores_count*machine.threads_count);
            core=(i/machine.threads_count)%machine.cores_count;
            thread=i%machine.threads_count;
            if(!machine.cpus[cpu].cores[core].threads[thread].process.id==0) machine.cpus[cpu].cores[core].threads[thread].process.quantum+=scheduler_args->ciclos_timer;//TEMPORAL, TIENE QUE AUMENTAR EL QUANTUM EN LA EJECUCION NO EN EL SCHEDULER
            if(is_empty_pcb(&machine.cpus[cpu].cores[core].threads[thread].queue) && is_empty_pcb(&machine.cpus[cpu].cores[core].threads[thread].partido) && machine.cpus[cpu].cores[core].threads[thread].process.id==0)continue;
            if(machine.cpus[cpu].cores[core].threads[thread].process.quantum>=machine.quantum){ //Si se acaba el quantum
                if(!is_empty_pcb(&machine.cpus[cpu].cores[core].threads[thread].queue)){
                   dequeue_pcb(&machine.cpus[cpu].cores[core].threads[thread].queue, &pcb); 
                }
                else{
                    pcb=pcbnulo;
                }
                dispacher(cpu,core,thread,pcb,&pcb,scheduler_args->verbose);
                if(pcb.ciclos_asignados<pcb.ciclos_usados){
                    enqueue_pcb(&machine.cpus[cpu].cores[core].threads[thread].queue, pcb);
                    if(scheduler_args->verbose){printf("reasignando pcb %d a la queue (%d,%d,%d)\n",pcb.id,cpu,core,thread);}
                }
            }
            
        }
   
    }
            
}

