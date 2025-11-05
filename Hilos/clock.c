#include <stdio.h>
#include <unistd.h>
#ifndef _thread_args_
#define _thread_args_

#include "../Estructuras/thread_args.h"
#include <pthread.h>

#endif
void* clock_thread(void* args) {
    __uint128_t i=0;
    pthread_mutex_init(&mutex_clock,NULL);
    t_clock_args *clock_args=args;
    done=0;
    pthread_cond_init(&cond_clock,NULL);
    pthread_cond_init(&cond_clock2,NULL);
    printf("Reloj iniciado\n");
    
    while(1){
        printf("ciclo %d\n",i);
        pthread_mutex_lock(&mutex_clock);
        while(done<N_TEMP){
            pthread_cond_wait(&cond_clock,&mutex_clock);
        }
        done=0;
        pthread_cond_broadcast(&cond_clock2);
        pthread_mutex_unlock(&mutex_clock);
        usleep(clock_args->frec); //usa microsegundos, 1 seg=1000000
        i++;
        

        
    }
}

