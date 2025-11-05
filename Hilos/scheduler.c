#include <stdio.h>
#include <unistd.h>
#ifndef _thread_args_
#define _thread_args_

#include "../Estructuras/thread_args.h"
#include <pthread.h>

#endif
void* scheduler_thread(void* args) {
    t_scheduler_args *scheduler_args=args;
    while(1){
        pthread_cond_wait(&cond_scheduler,&mutex_scheduler);
        if(scheduler_args->verbose){
            printf("scheduler activado\n");
        }
        
    }
}

