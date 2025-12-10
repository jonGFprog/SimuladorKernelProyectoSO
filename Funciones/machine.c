#include "../Estructuras/machine.h"

void init_machine(t_machine *machine, int cpus, int cores, int threads){
    machine->count=cpus;
    for(int i=0;i<cpus;i++){
        machine->cpus=malloc(cpus*sizeof(t_cpu));
        for(int j=0;j<cores;j++){
            machine->cpus[i].cores=malloc(cores*sizeof(t_core));
            machine->cpus[i].count=cores;
            for(int k=0;k<threads;k++){
                machine->cpus[i].cores[j].threads=malloc(threads*sizeof(t_thread));
                machine->cpus[i].cores[j].count=threads;
            }   
        }
    }
}
