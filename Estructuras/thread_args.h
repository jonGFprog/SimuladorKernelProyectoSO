#include <pthread.h>
#include <stdint.h>
pthread_mutex_t mutex_clock;
pthread_mutex_t mutex_procgen;
int N_TEMP=1;
int done;
pthread_cond_t cond_clock;
pthread_cond_t cond_clock2;
pthread_cond_t cond_procgen;

#define SIGPROCGEN SIGUSR1

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
} t_procgen_args;
