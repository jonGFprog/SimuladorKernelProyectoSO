#include <pthread.h>
#include <stdint.h>
#include <signal.h> 

#ifndef THREAD_ARGS_H
#define THREAD_ARGS_H

#define SIGFIN SIGUSR1 
pthread_mutex_t mutex_clock;
pthread_mutex_t mutex_procgen;
pthread_mutex_t mutex_scheduler;
int N_TEMP=2;
int done;

pthread_cond_t cond_clock;
pthread_cond_t cond_clock2;
pthread_cond_t cond_procgen;
pthread_cond_t cond_scheduler;


typedef struct 
{
    int frec;
    int verbose;
} t_clock_args;

typedef struct
{
    int ciclos;
    uintptr_t cond_timer;
    uintptr_t mutex_timer;
    __uint8_t* msg;
    int verbose;
} t_timer_args;

typedef struct 
{
    int max_size;
    int verbose;
    uintptr_t cond_sch;
} t_procgen_args;

typedef struct 
{
    int verbose;
    //fase2
    int ciclos_cambio_quantum; //ciclos antes de que el lider decida el nuevo quantum
    int margen_rnd_quantum[2];



} t_scheduler_args;

#endif