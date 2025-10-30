#include <stdio.h>
#include <unistd.h>
#ifndef _thread_args_
#define _thread_args_

#include "../Estructuras/thread_args.h"
#include <pthread.h>

#endif
void* timer_thread(void* args) {
    __uint32_t cont=0;
    while(1){
        done++;
        pthread_cond_signal(&cond);
        pthread_cond_wait(&cond2,&mutex);
        printf("tik\n");
    }
}

