#include <stdio.h>
#include <unistd.h>
#ifndef _thread_args_
#define _thread_args_

#include "../Estructuras/thread_args.h"
#include <pthread.h>

#endif
void* clock_thread(void* args) {
    __uint128_t i=0;
    pthread_mutex_init(&mutex,NULL);
    t_clock_args *clock_args=args;
    done=0;
    pthread_cond_init(&cond,NULL);
    pthread_cond_init(&cond2,NULL);
    printf("Reloj iniciado\n");
    
    while(1){
        printf("ciclo %d\n",i);
        pthread_mutex_lock(&mutex);
        while(done<N_TEMP){
            pthread_cond_wait(&cond,&mutex);
        }
        done=0;
        pthread_cond_broadcast(&cond2);
        pthread_mutex_unlock(&mutex);
        usleep(clock_args->frec); //usa microsegundos, 1 seg=1000000
        i++;
        

        
    }
}

