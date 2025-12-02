#include <pthread.h>
#include <stdint.h>
#include <signal.h> 
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
} t_procgen_args;

typedef struct 
{
    int verbose;
    //fase2
    int partido; //0 si no es parte del partido, 1 si lo es
    int ciclos_asignados; //ciclos maximos antes de su ejecucion publica
    int ciclos_usados;  
    int quantum; //tiempo de cpu asignado por el lider
    int paciencia; //solo importante si es un proceso del partido
    

} t_scheduler_args;
