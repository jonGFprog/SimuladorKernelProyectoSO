#include <stdio.h>
#include <unistd.h>
#ifndef _thread_args_
#define _thread_args_

#include "../Estructuras/thread_args.h"
#include <pthread.h>

#endif
void* timer_thread(void* args) {
    __uint32_t cont=0;
    t_timer_args *timer_args=args;
    pthread_cond_init((void *)timer_args->cond_timer,NULL);
    pthread_mutex_init((void *)timer_args->mutex_timer,NULL);
    int ciclos=0;
    while(1){
        if(ciclos==timer_args->ciclos){
            if(timer_args->verbose){
                printf("%s\n",timer_args->msg);
            }
            pthread_cond_signal((void *)timer_args->cond_timer);
            ciclos=0;
        }
        done++;
        ciclos++;
        pthread_cond_signal(&cond_clock);
        pthread_cond_wait(&cond_clock2,&mutex_clock);


    }
}

