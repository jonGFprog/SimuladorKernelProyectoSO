#include <pthread.h>
#include <stdlib.h>
#include "Hilos/clock.c"
#include "Hilos/timer.c"
#include "Estructuras/processQueue.h"
#include <string.h>

int main (int argc, char *argv[]) {
    if(argc!=6){
        printf("Numero incorrecto de argumentos.\n");
        exit(1);
    }
    pcb_max_size=512;
    pthread_t clock_id;
    pthread_t timer_id;
    pthread_t timer2_id;
    t_clock_args clock_args;
    clock_args.frec=atoi(argv[1]); //esta en milisegundos

    t_timer_args timer_args;
    timer_args.ciclos=atoi(argv[3]);
    timer_args.msg=malloc(strlen(argv[2]));
    strcpy(timer_args.msg,argv[2]);
    
    t_timer_args timer2_args;
    timer2_args.ciclos=atoi(argv[5]);
    timer2_args.msg=malloc(strlen(argv[4]));
    strcpy(timer2_args.msg,argv[4]);
    
    pthread_create(&clock_id,NULL,clock_thread, &clock_args);
    pthread_create(&timer_id,NULL,timer_thread, &timer_args);
    pthread_create(&timer2_id,NULL,timer_thread, &timer2_args);    

    pthread_join(timer_id,NULL);
    pthread_join(timer2_id,NULL);    
    pthread_join(clock_id,NULL);
}