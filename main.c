#include <pthread.h>
#include <stdlib.h>
#include "Hilos/clock.c"
#include "Hilos/timer.c"
#include "Hilos/processGenerator.c"
#include <string.h>

int main (int argc, char *argv[]) {
    //valores por defecto
    int procgen_frec=600;
    int procgen_max_size=512;
    int clk_frec=100000;
    int timer1_ciclos=1;
    int timer2_ciclos=1;
    
    for(int i=1;i<argc;i++){
        if(strcmp(argv[i],"--clock-frec")==0||strcmp(argv[i],"-f")==0){
            i++;
            clk_frec=atoi(argv[i]);
        }
        else if(strcmp(argv[i],"--procgen-frec")==0||strcmp(argv[i],"-F")==0){
            i++;
            procgen_frec=atoi(argv[i]);
        }
        else if(strcmp(argv[i],"--procgen-max-size")==0||strcmp(argv[i],"-S")==0){
            i++;
            procgen_max_size=atoi(argv[i]);
        }
        else if(strcmp(argv[i],"--timer1-ciclos")==0||strcmp(argv[i],"-c1")==0){
            i++;
            timer1_ciclos=atoi(argv[i]);
        }
        else if(strcmp(argv[i],"--timer2-ciclos")==0||strcmp(argv[i],"-c2")==0){
            i++;
            timer2_ciclos=atoi(argv[i]);
        }
    }

    pthread_t clock_id;
    pthread_t timer_id;
    pthread_t procgen_id;
    pthread_t timer2_id;
    printf("Parametros iniciales\nclk_frec: %d\nprocgen_frec: %d\tprocgen_max_size: %d\ntimer1_ciclos: %d\ttimer1_ciclos: %d\n",clk_frec,procgen_frec,procgen_max_size,timer1_ciclos,timer2_ciclos);
    
    t_clock_args clock_args;
    clock_args.frec=clk_frec; //esta en milisegundos

    t_timer_args timer_args;
    timer_args.ciclos=timer1_ciclos;
    timer_args.msg="timer 1";
    
    t_timer_args timer2_args;
    timer2_args.ciclos=timer2_ciclos;
    timer2_args.msg="timer 2";

    t_procgen_args procgen_args;
    procgen_args.frec=procgen_frec*10000;
    procgen_args.max_size=procgen_max_size;

    pthread_create(&clock_id,NULL,clock_thread, &clock_args);
    pthread_create(&timer_id,NULL,timer_thread, &timer_args);
    pthread_create(&timer2_id,NULL,timer_thread, &timer2_args);    
    pthread_create(&procgen_id,NULL,procgen_thread, &procgen_args);
    
    
    
    pthread_join(timer_id,NULL);
    pthread_join(timer2_id,NULL);    
    pthread_join(clock_id,NULL);
    pthread_join(procgen_id,NULL);
}