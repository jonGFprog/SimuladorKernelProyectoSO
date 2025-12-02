#include <pthread.h>
#include <stdlib.h>
#include "Hilos/clock.c"
#include "Hilos/timer.c"
#include "Hilos/processGenerator.c"
#include "Hilos/scheduler.c"
#include <string.h>

int main (int argc, char *argv[]) {
    //valores por defecto
    int timer_procgen_frec=32; //(ciclos de reloj para que el timer interrumpa)
    int procgen_max_size=512;
    int procgen_verb=0;
    int clk_frec=100000;
    int clk_verb=0;
    int timer_scheduler_frec=1;
    int scheduler_verb=0;

    
    for(int i=1;i<argc;i++){
        if(strcmp(argv[i],"--clock-frec")==0||strcmp(argv[i],"-cf")==0){
            i++;
            clk_frec=atoi(argv[i]);
        }
        else if(strcmp(argv[i],"--clock-verbose")==0||strcmp(argv[i],"-cV")==0){
            clk_verb=1;
        }
        else if(strcmp(argv[i],"--procgen-frec")==0||strcmp(argv[i],"-pf")==0){
            i++;
            timer_procgen_frec=atoi(argv[i]);
        }
        else if(strcmp(argv[i],"--procgen-max-size")==0||strcmp(argv[i],"-pS")==0){
            i++;
            procgen_max_size=atoi(argv[i]);
        }
        else if(strcmp(argv[i],"--procgen-verbose")==0||strcmp(argv[i],"-pV")==0){
            procgen_verb=1;
        }
        else if(strcmp(argv[i],"--scheduler-frec")==0||strcmp(argv[i],"-sf")==0){
            i++;
            timer_scheduler_frec=atoi(argv[i]);
        }
        else if(strcmp(argv[i],"--scheduler-verbose")==0||strcmp(argv[i],"-sV")==0){
            scheduler_verb=1;
        }
        
    }

    pthread_t clock_id;
    pthread_t timer_procgen_id;
    pthread_t procgen_id;
    pthread_t timer_scheduler_id;
    pthread_t scheduler_id;
    printf("Parametros iniciales\nclk_frec: %d\ntimer_procgen_frec: %d\tprocgen_max_size: %d\tprocgen_verb: %d\ntimer_scheduler_frec: %d\tscheduler_verb: %d\n"
           ,clk_frec,timer_procgen_frec,procgen_max_size,procgen_verb,timer_scheduler_frec,scheduler_verb);
    
    t_clock_args clock_args;
    clock_args.frec=clk_frec; //esta en milisegundos
    clock_args.verbose=clk_verb;

    t_procgen_args procgen_args;
    procgen_args.max_size=procgen_max_size;
    procgen_args.verbose=procgen_verb;

    t_timer_args timer_procgen_args;
    timer_procgen_args.ciclos=timer_procgen_frec;
    timer_procgen_args.msg="timer procgen";
    timer_procgen_args.cond_timer=(uintptr_t)&cond_procgen;
    timer_procgen_args.mutex_timer=(uintptr_t)&mutex_procgen;
    timer_procgen_args.verbose=0;
    
    t_scheduler_args scheduler_args;
    scheduler_args.verbose=scheduler_verb;

    t_timer_args timer_scheduler_args;
    timer_scheduler_args.ciclos=timer_scheduler_frec;
    timer_scheduler_args.msg="timer scheduler";
    timer_scheduler_args.cond_timer=(uintptr_t)&cond_scheduler;
    timer_scheduler_args.mutex_timer=(uintptr_t)&mutex_scheduler;
    timer_scheduler_args.verbose=0;
    

    pthread_create(&clock_id,NULL,clock_thread, &clock_args);
    pthread_create(&timer_procgen_id,NULL,timer_thread, &timer_procgen_args);
    pthread_create(&procgen_id,NULL,procgen_thread, &procgen_args);
    pthread_create(&timer_scheduler_id,NULL,timer_thread, &timer_scheduler_args);    
    pthread_create(&scheduler_id,NULL,scheduler_thread, &scheduler_args);
    
    
    char buf[512];
    while(1){
        if(fgets(buf, sizeof(buf), stdin)!=NULL){
            buf[strcspn(buf, "\n")] = 0;
            if (strcmp(buf, "quit") == 0) {
                break;
            }
        }
    }
    printf("Parando Kernel...\n");
    pthread_cancel(scheduler_id);
    pthread_join(scheduler_id,NULL);
    printf("scheduler detenido...\n");

    pthread_cancel(procgen_id);
    pthread_join(procgen_id,NULL);
    printf("processGenerator detenido...\n");

    pthread_cancel(timer_procgen_id);
    pthread_join(timer_procgen_id,NULL);
    printf("timer del processGenerator detenido...\n");

    pthread_cancel(timer_scheduler_id);
    pthread_cond_broadcast(&cond_clock2);
    pthread_mutex_unlock(&mutex_clock);
    pthread_join(timer_scheduler_id,NULL);
    printf("timer del scheduler detenido...\n");
  
    pthread_cancel(clock_id);
    pthread_join(clock_id,NULL);
    printf("clock detenido...\n");
    
}