#include <pthread.h>
#include <stdlib.h>
#include "Hilos/clock.c"
#include "Hilos/timer.c"
#include "Hilos/processGenerator.c"
#include <string.h>

int main (int argc, char *argv[]) {
    //valores por defecto
    int timer_procgen_frec=32; //(ciclos de reloj para que el timer interrumpa)
    int procgen_max_size=512;
    int procgen_verb=0;
    int clk_frec=100000;
    int clk_verb=0;
    int timer2_ciclos=1;
    
    for(int i=1;i<argc;i++){
        if(strcmp(argv[i],"--clock-frec")==0||strcmp(argv[i],"-f")==0){
            i++;
            clk_frec=atoi(argv[i]);
        }
        else if(strcmp(argv[i],"--clock-verbose")==0||strcmp(argv[i],"-cV")==0){
            clk_verb=1;
        }
        else if(strcmp(argv[i],"--procgen-frec")==0||strcmp(argv[i],"-F")==0){
            i++;
            timer_procgen_frec=atoi(argv[i]);
        }
        else if(strcmp(argv[i],"--procgen-max-size")==0||strcmp(argv[i],"-S")==0){
            i++;
            procgen_max_size=atoi(argv[i]);
        }
        else if(strcmp(argv[i],"--procgen-verbose")==0||strcmp(argv[i],"-pV")==0){
            procgen_verb=1;
        }
        /*else if(strcmp(argv[i],"--timer2-ciclos")==0||strcmp(argv[i],"-c2")==0){
            i++;
            timer2_ciclos=atoi(argv[i]);
        }*/
    }

    pthread_t clock_id;
    pthread_t timer_procgen_id;
    pthread_t procgen_id;
    pthread_t timer2_id;
    printf("Parametros iniciales\nclk_frec: %d\nt_procgen_frec: %d\tprocgen_max_size: %d\tprocgen_verb: %d\ntimer2_ciclos: %d\n"
        ,clk_frec,timer_procgen_frec,procgen_max_size,procgen_verb,timer2_ciclos);
    
    t_clock_args clock_args;
    clock_args.frec=clk_frec; //esta en milisegundos
    clock_args.verbose=clk_verb;

    t_timer_args timer_procgen_args;
    timer_procgen_args.ciclos=timer_procgen_frec;
    timer_procgen_args.msg="timer procgen";
    timer_procgen_args.cond_timer=(uintptr_t)&cond_procgen;
    timer_procgen_args.mutex_timer=(uintptr_t)&mutex_procgen;
    timer_procgen_args.verbose=1;
/*    
    t_timer_args timer2_args;
    timer2_args.ciclos=timer2_ciclos;
    timer2_args.msg="timer 2";
*/
    t_procgen_args procgen_args;
    procgen_args.max_size=procgen_max_size;
    procgen_args.verbose=procgen_verb;

    pthread_create(&clock_id,NULL,clock_thread, &clock_args);
    pthread_create(&timer_procgen_id,NULL,timer_thread, &timer_procgen_args);
    //pthread_create(&timer2_id,NULL,timer_thread, &timer2_args);    
    pthread_create(&procgen_id,NULL,procgen_thread, &procgen_args);
    
    
    pause();
    /*pthread_join(timer_id,NULL);
    pthread_join(timer2_id,NULL);    
    pthread_join(clock_id,NULL);
    pthread_join(procgen_id,NULL);*/
}