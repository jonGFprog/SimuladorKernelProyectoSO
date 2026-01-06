#include <stdio.h>
#include <unistd.h>
#include "../Estructuras/thread_args.h"
#include <pthread.h>
#include "../Funciones/machine.c"

void* machine_thread(void* args) {
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
    int cpu,core,thread;
    int ciclos_q=0;

    //t_timer_args *timer_args=args;
    while(1){
        
        for(int i=0;i<machine.total_threads;i++){
            cpu=i/(machine.cores_count*machine.threads_count);
            core=(i/machine.threads_count)%machine.cores_count;
            thread=i%machine.threads_count;
            if(machine.cpus[cpu].cores[core].threads[thread].process.id!=0&&!machine.cpus[cpu].cores[core].threads[thread].process.partido){
                pthread_mutex_lock(&mutex_dispacher);
                machine.cpus[cpu].cores[core].threads[thread].process.quantum++;
                machine.cpus[cpu].cores[core].threads[thread].process.ciclos_usados++;
                pthread_mutex_unlock(&mutex_dispacher);
            }
            //TEMPORAL, por el momento se considerara que un proceso del partido ha acabado cuando llegue a los ciclos asignados. QUITAR EN LA PARTE3
                if(machine.cpus[cpu].cores[core].threads[thread].process.partido){
                    pthread_mutex_lock(&mutex_dispacher);
                    machine.cpus[cpu].cores[core].threads[thread].process.ciclos_usados++; 
                    if(machine.cpus[cpu].cores[core].threads[thread].process.ciclos_usados==machine.ciclos_maximos_asignados){
                        machine.cpus[cpu].cores[core].threads[thread].process.fin=1;
                    }
                    pthread_mutex_unlock(&mutex_dispacher);
                }
            ciclos_q++;
            if(ciclos_q>=machine.ciclos_cambio_quantum){
                ciclos_q=0;
                cambio_quantum(machine.margen_rnd_quantum);
            }
           
            //EJECUTAR
        }
        //printf("quantum++ \n");
        done++;
        pthread_cond_signal(&cond_clock);
        pthread_cond_wait(&cond_clock2,&mutex_clock);
    }
        
}