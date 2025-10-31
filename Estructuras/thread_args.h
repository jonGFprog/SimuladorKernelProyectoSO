#include <pthread.h>
pthread_mutex_t mutex;
int N_TEMP=2;
int done;
pthread_cond_t cond;
pthread_cond_t cond2;

typedef struct 
{
    int frec;
} t_clock_args;

typedef struct
{
    int ciclos;
    __uint8_t* msg;
} t_timer_args;

typedef struct 
{
    int frec;
    int max_size;

} t_procgen_args;
