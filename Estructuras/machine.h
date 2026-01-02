#include "pcb.h"
#include "processQueue.h"
#include "mmu.h"
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
    int pc; 
    uintptr_t ptbr; //puntero a tabla de paginas
    uint32_t ir; //instruction register
    t_mmu mmu;
}t_thread;

typedef struct 
{
    t_thread* threads;
}t_core;

typedef struct 
{
    t_core* cores;
}t_cpu;

typedef struct 
{
    t_cpu* cpus;
    int cpus_count;
    int cores_count;
    int threads_count;
    int *libres;
    int total_threads; //cpu*cores*threads
    __uint16_t quantum; //tiempo de cpu asignado por el lider
    int ciclos_cambio_quantum; //ciclos antes de que el lider decida el nuevo quantum; Se encargara temporalmente el scheduler (y definitivamente si se me olvida o no da el tiempo)
    int margen_rnd_quantum[2]; 
    float prob_purga;
    int ciclos_maximos_asignados;

} t_machine;

t_machine machine;
void init_machine(t_machine *machine, int cpus, int cores, int threads, int queue_size,float prob_purga, int ciclos_cambio, int margen_rnd_quantum[2],int ciclos_maximos);
void cambio_quantum(int margen[2]);
void print_machine(t_machine *machine);
void print_process_info(t_machine *machine);
void print_machine_info(t_machine *machine);
#endif
