#include <pthread.h>
pthread_mutex_t mutex;
int N_TEMP=1;
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
} t_timer_args;
