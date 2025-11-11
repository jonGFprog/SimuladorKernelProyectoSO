#include "pcb.h"


typedef struct 
{
    t_cpu* cpus;
    int count;
} t_machine;

typedef struct 
{
    t_core* threads;
    int count;
}t_cpu;

typedef struct 
{
    t_thread* threads;
    int count;
}t_core;

typedef struct 
{
    t_pcb process;
}t_thread;
