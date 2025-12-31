#include "../Estructuras/machine.h"
#ifndef MACHINE_C
#define MACHINE_C
void init_machine(t_machine *machine, int cpus, int cores, int threads, int queue_size,float prob_purga, int ciclos_cambio, int margen_rnd_quantum[2],int ciclos_maximos){
    machine->cpus_count=cpus;
    machine->cores_count=cores;
    machine->threads_count=threads;
    int size=cpus*cores*threads;
    machine->libres=calloc(2*size,sizeof(int));
    machine->total_threads=size;
    machine->quantum=150;
    machine->cpus=malloc(cpus*sizeof(t_cpu));
    machine->prob_purga=prob_purga;
    machine->ciclos_cambio_quantum=ciclos_cambio;
    machine->margen_rnd_quantum[0]=margen_rnd_quantum[0];
    machine->margen_rnd_quantum[1]=margen_rnd_quantum[1];
    cambio_quantum(margen_rnd_quantum);
    machine->ciclos_maximos_asignados=ciclos_maximos;
    for(int i=0;i<cpus;i++){
        machine->cpus[i].cores=malloc(cores*sizeof(t_core));
        for(int j=0;j<cores;j++){
            machine->cpus[i].cores[j].threads=malloc(threads*sizeof(t_thread));
            for(int k=0;k<threads;k++){
                machine->cpus[i].cores[j].threads[k].process=pcbnulo;
                init_pcb_queue(&machine->cpus[i].cores[j].threads[k].queue,queue_size);
                init_pcb_queue(&machine->cpus[i].cores[j].threads[k].partido,queue_size);
            }   
        }
    }
}

void cambio_quantum(int margen[2]){
    int quantum=margen[0]+ rand()% (margen[1]-margen[0]);
    machine.quantum=quantum;
}

void print_machine(t_machine *machine){
    int cpu,core,thread;
    for(int i=0;i<machine->cpus_count;i++){
        for(int j=0;j<machine->cores_count;j++){
            for(int k=0;k<machine->threads_count;k++){
                printf("\n+-------------------------------------------------+\n");
                printf("|         cpu %d      core %d    thread %d          |\n",i,j,k);
                printf("|           pcb ejecucion id %d                     |\n",machine->cpus[i].cores[j].threads[k].process.id);
                printf("|                       queue:                      |\n");
                for(int l=0;l<machine->cpus[i].cores[j].threads[k].queue.size;l++){
                printf("|           pcb cola id %d                          |\n",machine->cpus[i].cores[j].threads[k].queue.pcb[machine->cpus[i].cores[j].threads[k].queue.first + l].id);
                }
                printf("|                      partido:                     |\n");
                for(int l=0;l<machine->cpus[i].cores[j].threads[k].partido.size;l++){
                printf("|           pcb cola id %d                          |\n",machine->cpus[i].cores[j].threads[k].partido.pcb[machine->cpus[i].cores[j].threads[k].partido.first + l].id);
                }
                printf("+-------------------------------------------------+\n");
            }   
        }
    }
}

void print_process_info(t_machine *machine){
    int cpu,core,thread;
    for(int i=0;i<machine->cpus_count;i++){
        for(int j=0;j<machine->cores_count;j++){
            for(int k=0;k<machine->threads_count;k++){
                printf("\n+-------------------------------------------------+\n");
                printf("|         cpu %d      core %d    thread %d          |\n",i,j,k);
                printf("|           pcb ejecucion id %d                     |\n",machine->cpus[i].cores[j].threads[k].process.id);
                printf("|                   patido: %d                      |\n",machine->cpus[i].cores[j].threads[k].process.partido);
                if(machine->cpus[i].cores[j].threads[k].process.partido){
                printf("|                paciencia: %d                      |\n",machine->cpus[i].cores[j].threads[k].process.paciencia);    
                }
                printf("|                  quantum: %d                      |\n",machine->cpus[i].cores[j].threads[k].process.quantum);
                printf("|            ciclos_usados: %d                      |\n",machine->cpus[i].cores[j].threads[k].process.ciclos_usados);
                printf("|         ciclos_asignados: %d                      |\n",machine->ciclos_maximos_asignados);
                printf("+-------------------------------------------------+\n");
            }   
        }
    }
}
void print_machine_info(t_machine *machine){
    printf("\n+-------------------------------------------------+\n");
    printf("|        cpus %d     cores %d   threads %d          |\n",machine->cpus_count,machine->cores_count,machine->threads_count);
    printf("|            total threads: %d                      |\n",machine->total_threads);
    printf("|                  quantum: %d                      |\n",machine->quantum);
    printf("+-------------------------------------------------+\n");
}
#endif