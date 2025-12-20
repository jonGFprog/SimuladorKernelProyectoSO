#include "../Estructuras/machine.h"
#ifndef MACHINE_C
#define MACHINE_C
void init_machine(t_machine *machine, int cpus, int cores, int threads, int queue_size){
    machine->cpus_count=cpus;
    machine->cores_count=cores;
    machine->threads_count=threads;
    int size=cpus*cores*threads;
    machine->total_threads=size;
    machine->cpus=malloc(cpus*sizeof(t_cpu));
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

void print_machine(t_machine *machine){
    for(int i=0;i<machine->cpus_count;i++){
        for(int j=0;j<machine->cores_count;j++){
            for(int k=0;k<machine->threads_count;k++){
                printf("\n+-------------------------------------------------+\n");
                printf("|                     thread %d                   |\n",(i+1)*(j+1)*(k+1));
                printf("|              core %d         cpu %d             |\n",i,j);
                printf("|         pcb ejecucion id %d                     |\n",machine->cpus[i].cores[j].threads[k].process.id);
                printf("|                     queue:                      |\n");
                for(int l=0;l<machine->cpus[i].cores[j].threads[k].queue.size;l++){
                printf("|         pcb cola id %d                          |\n",machine->cpus[i].cores[j].threads[k].queue.pcb[l].id);
                }
                printf("|                     partido:                    |\n");
                for(int l=0;l<machine->cpus[i].cores[j].threads[k].partido.size;l++){
                printf("|         pcb cola id %d                          |\n",machine->cpus[i].cores[j].threads[k].partido.pcb[l].id);
                }
                printf("+-------------------------------------------------+\n");
            }   
        }
    }
}
#endif