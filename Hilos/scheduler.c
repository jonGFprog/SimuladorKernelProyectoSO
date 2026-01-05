#include <stdio.h>
#include <unistd.h>
#include "../Funciones/machine.c"
#include "../Funciones/processQueue.c"
#include "../Estructuras/thread_args.h"
#include <pthread.h>


void dispacher(int cpu, int core, int thread, t_pcb pcb, t_pcb *exit_pcb, int verbose){
    
    *exit_pcb=machine.cpus[cpu].cores[core].threads[thread].process;
    pthread_mutex_lock(&mutex_dispacher);
    machine.cpus[cpu].cores[core].threads[thread].process=pcb;
    pthread_mutex_unlock(&mutex_dispacher);
    
    if(verbose) printf("PCB id:%d asignado a %d,%d,%d\n",machine.cpus[cpu].cores[core].threads[thread].process.id,cpu,core,thread);

}

void asignar_trabajo(t_pcb *pcb, uint8_t partido, int verbose){
    int min=INT32_MAX;
    int pos=-1;
    int cpu,core,thread;
    for(int i=0;i<machine.total_threads;i++){
        if(machine.libres[i]==0&&machine.libres[machine.total_threads+i]==0){
            pos=i;
            break;
        }
        else{
            if(machine.libres[partido*machine.total_threads+i]<min){
                pos=i;
                min=machine.libres[partido*machine.total_threads+i];
            }
        }
    }

    cpu=pos/(machine.cores_count*machine.threads_count);
    core=(pos/machine.threads_count)%machine.cores_count;
    thread=pos%machine.threads_count;
    if(partido){
        if(enqueue_pcb(&machine.cpus[cpu].cores[core].threads[thread].partido,*pcb)){
            machine.libres[partido*machine.total_threads+pos]++;
            if(verbose)printf("pcb %d añadido al partido (%d,%d,%d)\n",pcb->id,cpu,core,thread); 
        }
        else{
            printf("ERROR, queue del partido (%d,%d,%d) llena, pcb %d NO ha sido añadido\n",cpu,core,thread,pcb->id);
        }
        
    }
    else{
        if(enqueue_pcb(&machine.cpus[cpu].cores[core].threads[thread].queue,*pcb)){
            machine.libres[partido*machine.total_threads+pos]++;
            if(verbose)printf("pcb %d añadido a la queue (%d,%d,%d)\n",pcb->id,cpu,core,thread);
        }
        else{
            printf("ERROR, queue (%d,%d,%d) llena, pcb %d NO ha sido añadido\n",cpu,core,thread,pcb->id);
        }
        
    }
}

void* scheduler_thread(void* args) { 
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
    t_scheduler_args *scheduler_args=args;
    t_pcb pcb;
    t_select select;
    int cpu,core,thread;
    float prob;
    while(1){

        pthread_cond_wait(&cond_scheduler,&mutex_scheduler);
        if(scheduler_args->verbose){printf("scheduler activado\n");} 
        while(!is_empty_pcb(&process_queue)){
            dequeue_pcb(&process_queue,&pcb);
            asignar_trabajo(&pcb,pcb.partido,scheduler_args->verbose);            
        }
        
        for(int i=0;i<machine.total_threads;i++){ 
            cpu=i/(machine.cores_count*machine.threads_count);
            core=(i/machine.threads_count)%machine.cores_count;
            thread=i%machine.threads_count;

            //TEMPORAL, por el momento se considerara que un proceso del partido ha acabado cuando llegue a los ciclos asignados
            if(machine.cpus[cpu].cores[core].threads[thread].process.partido){
                machine.cpus[cpu].cores[core].threads[thread].process.ciclos_usados+=scheduler_args->ciclos_timer; 
            }

            if(is_empty_pcb(&machine.cpus[cpu].cores[core].threads[thread].queue) && is_empty_pcb(&machine.cpus[cpu].cores[core].threads[thread].partido) && machine.cpus[cpu].cores[core].threads[thread].process.id==0)continue;
            
            
            if(machine.cpus[cpu].cores[core].threads[thread].process.quantum>=machine.quantum //Si se acaba el quantum 
                ||machine.cpus[cpu].cores[core].threads[thread].process.id==0 //o pcb nulo
                || (machine.cpus[cpu].cores[core].threads[thread].process.ciclos_usados>=machine.ciclos_maximos_asignados) // o ha llegado a los ciclos_asignados
                ){ 
                if(!is_empty_pcb(&machine.cpus[cpu].cores[core].threads[thread].partido)){
                    dequeue_pcb(&machine.cpus[cpu].cores[core].threads[thread].partido, &pcb);
                }
                else if(!is_empty_pcb(&machine.cpus[cpu].cores[core].threads[thread].queue)){
                   dequeue_pcb(&machine.cpus[cpu].cores[core].threads[thread].queue, &pcb); 
                }
                else{
                    if(machine.cpus[cpu].cores[core].threads[thread].process.ciclos_usados<machine.ciclos_maximos_asignados)continue; //no sacarlo de ejecucion si nadie quiere entrar y aun no se le acaban los ciclos asignados. 
                    pcb=pcbnulo;
                }
                dispacher(cpu,core,thread,pcb,&pcb,scheduler_args->verbose);
                if(pcb.id==0)continue; //si es el pcb nulo, no hacer nada mas
                if(pcb.ciclos_usados<machine.ciclos_maximos_asignados){
                    pcb.quantum=0;
                    enqueue_pcb(&machine.cpus[cpu].cores[core].threads[thread].queue, pcb);
                    if(scheduler_args->verbose){printf("reasignando pcb %d a la queue (%d,%d,%d)\n",pcb.id,cpu,core,thread);}
                }
                else{
                    machine.libres[pcb.partido*machine.total_threads+i]--;
                    if(scheduler_args->verbose) printf("(queue) machine.libres[%d]-- (%d)\n",i,machine.libres[pcb.partido*machine.total_threads+i]);
                }
            }//Expulsion
            else if(!machine.cpus[cpu].cores[core].threads[thread].process.partido && !is_empty_pcb(&machine.cpus[cpu].cores[core].threads[thread].partido)){ //partido quiere entrar, no partido en ejecucion
                dequeue_pcb(&machine.cpus[cpu].cores[core].threads[thread].partido, &pcb);
                dispacher(cpu,core,thread,pcb,&pcb,scheduler_args->verbose);
                printf("expulsado pcb %d del thread (%d,%d,%d)\n",pcb.id,cpu,core,thread);
                if(pcb.ciclos_usados<machine.ciclos_maximos_asignados){


                    pcb.quantum=0;


                    enqueue_pcb(&machine.cpus[cpu].cores[core].threads[thread].queue, pcb);
                    if(scheduler_args->verbose){printf("reasignando pcb %d a la queue (%d,%d,%d)\n",pcb.id,cpu,core,thread);}
                }
                else{ //muy improbable pero en teoria podria pasar
                    machine.libres[pcb.partido*machine.total_threads+i]--;
                    if(scheduler_args->verbose) printf("(queue) machine.libres[%d]-- (%d)\n",i,machine.libres[pcb.partido*machine.total_threads+i]);
                }           
            }
            else if(machine.cpus[cpu].cores[core].threads[thread].process.partido && !is_empty_pcb(&machine.cpus[cpu].cores[core].threads[thread].partido)){ //partido quiere entrar, partido en ejecucion
                machine.cpus[cpu].cores[core].threads[thread].partido.pcb[machine.cpus[cpu].cores[core].threads[thread].partido.first].ciclos_usados+=scheduler_args->ciclos_timer; //usar ciclos_usados para contar cuantos ciclos lleva esperando.
                peek_pcb(&machine.cpus[cpu].cores[core].threads[thread].partido,&pcb);
                if(pcb.ciclos_usados>pcb.paciencia){
                    dequeue_pcb(&machine.cpus[cpu].cores[core].threads[thread].partido, &pcb);
                    prob = rand() / (double)RAND_MAX; //entre 0.0 y 1.0
                    if(prob<machine.prob_purga){ //proceso en cpu purgado
                        pcb.ciclos_usados=0;
                        if(scheduler_args->verbose) printf("Acusacion verdadera, pcb %d ha sido purgado\n",machine.cpus[cpu].cores[core].threads[thread].process.id);
                        dispacher(cpu,core,thread,pcb,&pcb,scheduler_args->verbose);
                    }
                    else{ //proceso en cola purgado
                        if(scheduler_args->verbose) printf("Acusacion falsa, pcb %d ha sido purgado\n",pcb.id);
                    }
                    machine.libres[pcb.partido*machine.total_threads+i]--;
                    if(scheduler_args->verbose) printf("(partido) machine.libres[%d]-- (%d)\n",i,machine.libres[pcb.partido*machine.total_threads+i]);
                    
                }

            }
        }
   
    }
            
}

