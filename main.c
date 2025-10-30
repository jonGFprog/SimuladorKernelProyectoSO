#include <pthread.h>
#include <stdlib.h>
#include "Hilos/clock.c"
#include "Hilos/timer.c"
#include <string.h>

int main (int argc, char *argv[]) {
    if(argc!=4){
        printf("Numero incorrecto de argumentos.\n");
        exit(1);
    }
    pthread_t clock_id;
    pthread_t timer_id;
    t_clock_args clock_args;
    clock_args.frec=atoi(argv[1]); //esta en milisegundos

    t_timer_args timer_args;
    timer_args.ciclos=atoi(argv[3]);
    timer_args.msg=malloc(strlen(argv[2]));
    strcpy(timer_args.msg,argv[2]);
    pthread_create(&clock_id,NULL,clock_thread, &clock_args);
 
    pthread_create(&timer_id,NULL,timer_thread, &timer_args);
    
    pthread_join(timer_id,NULL);    
    pthread_join(clock_id,NULL);
}