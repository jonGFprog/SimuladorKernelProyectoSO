#include "pcb.h"
#include "processQueue.h"
#ifndef MACHINE_H
#define MACHINE_H

typedef struct{
    int cpu;
    int core;
    int thread;
}t_select;
typedef struct 
{
    t_pcb process;
    t_pcb_queue partido;
    t_pcb_queue queue;
    
}t_thread;

typedef struct 
{
    t_thread* threads;
    int count;
}t_core;

typedef struct 
{
    t_core* cores;
    int count;
}t_cpu;

typedef struct 
{
    t_cpu* cpus;
    int count;
    int *libres;
    int libres_size; //cpu*cores*threads
} t_machine;

t_machine machine;
void init_machine(t_machine *machine, int cpus, int cores, int threads);
#endif
