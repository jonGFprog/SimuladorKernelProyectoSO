#include <pthread.h>
#include <stdlib.h>
#include "Hilos/clock.c"
#include "Hilos/timer.c"
#include "Hilos/processGenerator.c"
#include "Hilos/scheduler.c"
#include "Hilos/machine_thread.c"
#include <string.h>

int main (int argc, char *argv[]) {
    pcbnulo.id=0;
    pcbnulo.quantum=0;
    pcbnulo.fin=7;
    pcbnulo.ciclos_usados=0;
    //valores por defecto
    int timer_procgen_frec=32; //(ciclos de reloj para que el timer interrumpa)
    int procgen_max_size=512;
    int procgen_verb=0;
    int procgen_paciencia=850;
    float procgen_prob_partido=0.1;
    int clk_frec=100000;
    int clk_verb=0;
    int timer_scheduler_frec=30;
    int scheduler_verb=0;
    //machine
    int cpus=2;
    int cores=2;
    int threads=2;

    int queue_size=150;
    float prob_purga=0.5;
    int ciclos_cambio=4500;
    int margen_rnd_quantum[2]={90,150};
    int ciclos_maximos=750;
    
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
        else if(strcmp(argv[i],"--cpu-count")==0||strcmp(argv[i],"-Cc")==0){
            i++;
            cpus=atoi(argv[i]);
            if (cpus<1){
                printf("El numero de cpus debe ser mayor que 0");
                exit(1);
            }
        }
        else if(strcmp(argv[i],"--cores-count")==0||strcmp(argv[i],"-cc")==0){
            i++;
            cores=atoi(argv[i]);
            if (cores<1){
                printf("El numero de cores debe ser mayor que 0");
                exit(1);
            }
        }
        else if(strcmp(argv[i],"--threads-count")==0||strcmp(argv[i],"-tc")==0){
            i++;
            threads=atoi(argv[i]);
            if (threads<1){
                printf("El numero de hilos debe ser mayor que 0");
                exit(1);
            }
        }
        else if(strcmp(argv[i],"--queue-size")==0||strcmp(argv[i],"-qS")==0){
            i++;
            queue_size=atoi(argv[i]);
        }
        else if(strcmp(argv[i],"--prob-purga")==0||strcmp(argv[i],"-pp")==0){
            i++;
            prob_purga=atof(argv[i]);
        }
        else if(strcmp(argv[i],"--ciclos-cambio-quantum")==0||strcmp(argv[i],"-ccq")==0){
            i++;
            ciclos_cambio=atoi(argv[i]);
        }
        else if(strcmp(argv[i],"--margen-quantum")==0||strcmp(argv[i],"-mq")==0){
            i++;
            margen_rnd_quantum[0]=atoi(argv[i]);
            i++;
            margen_rnd_quantum[1]=atoi(argv[i]);
        }
        else if(strcmp(argv[i],"--ciclos-maximos")==0||strcmp(argv[i],"-cm")==0){
            i++;
            ciclos_maximos=atoi(argv[i]);
        }
        else if(strcmp(argv[i],"--procgen-paciencia")==0||strcmp(argv[i],"-p")==0){
            i++;
            procgen_paciencia=atoi(argv[i]);
        }
        else if(strcmp(argv[i],"--procgen-prob-partido")==0||strcmp(argv[i],"-ppp")==0){
            i++;
            procgen_prob_partido=atof(argv[i]);
        }
    }
    
    init_machine(&machine, cpus,cores,threads,queue_size,prob_purga,ciclos_cambio,margen_rnd_quantum,ciclos_maximos); 
    pthread_mutex_init(&mutex_pausa,NULL);
    pthread_cond_init(&cond_pausa,NULL);
    pthread_mutex_init(&mutex_dispacher,NULL);
    pausa=0;

    pthread_t clock_id;
    pthread_t timer_procgen_id;
    pthread_t procgen_id;
    pthread_t timer_scheduler_id;
    pthread_t scheduler_id;
    pthread_t machine_thread_id;
    printf("Parametros iniciales\nclk_frec: %d\ntimer_procgen_frec: %d\tprocgen_max_size: %d\tprocgen_verb: %d\ntimer_scheduler_frec: %d\tscheduler_verb: %d\n"
           ,clk_frec,timer_procgen_frec,procgen_max_size,procgen_verb,timer_scheduler_frec,scheduler_verb);
    
    t_clock_args clock_args;
    clock_args.frec=clk_frec; //esta en milisegundos
    clock_args.verbose=clk_verb;

    t_procgen_args procgen_args;
    procgen_args.max_size=procgen_max_size;
    procgen_args.verbose=procgen_verb;
    procgen_args.paciencia=procgen_paciencia;
    procgen_args.prob_partido=procgen_prob_partido;

    t_timer_args timer_procgen_args;
    timer_procgen_args.ciclos=timer_procgen_frec;
    timer_procgen_args.msg="timer procgen";
    timer_procgen_args.cond_timer=(uintptr_t)&cond_procgen;
    timer_procgen_args.mutex_timer=(uintptr_t)&mutex_procgen;
    timer_procgen_args.verbose=0;
    
    t_scheduler_args scheduler_args;
    scheduler_args.verbose=scheduler_verb;
    scheduler_args.ciclos_timer=timer_scheduler_frec;

    t_timer_args timer_scheduler_args;
    timer_scheduler_args.ciclos=timer_scheduler_frec;
    timer_scheduler_args.msg="timer scheduler";
    timer_scheduler_args.cond_timer=(uintptr_t)&cond_scheduler;
    timer_scheduler_args.mutex_timer=(uintptr_t)&mutex_scheduler;
    timer_scheduler_args.verbose=0;
    

    pthread_create(&clock_id,NULL,clock_thread, &clock_args);
    usleep(100); //creo que arregla el problema de que a veces no se inicia el clock. 
    pthread_create(&timer_procgen_id,NULL,timer_thread, &timer_procgen_args);
    pthread_create(&procgen_id,NULL,procgen_thread, &procgen_args);
    pthread_create(&timer_scheduler_id,NULL,timer_thread, &timer_scheduler_args);    
    pthread_create(&scheduler_id,NULL,scheduler_thread, &scheduler_args);
    pthread_create(&machine_thread_id,NULL,machine_thread, NULL);
    
    
    char buf[512];
    while(1){
        if(fgets(buf, sizeof(buf), stdin)!=NULL){
            buf[strcspn(buf, "\n")] = 0;
            if (strcmp(buf, "quit") == 0) {
                break;
            }
            else if(strcmp(buf, "print") == 0){
                print_machine(&machine);
            }
            else if(strcmp(buf, "pinfo") == 0){
                print_process_info(&machine);
            }
            else if(strcmp(buf, "minfo") == 0){
                print_machine_info(&machine);
            }
            else if(strcmp(buf, "p") == 0){
                if(pausa==1){
                    printf("\nya esta pausado\n");
                    continue;
                }
                printf("\nPAUSA\n");
                pthread_mutex_lock(&mutex_pausa);
                pausa=1;
            }
            else if(strcmp(buf, "c") == 0){
                printf("\nCONTINUE\n");
                pausa=0;
                pthread_mutex_unlock(&mutex_pausa);
                pthread_cond_broadcast(&cond_pausa);
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
  
    pthread_mutex_unlock(&mutex_dispacher);
    pthread_cancel(machine_thread_id);
    pthread_join(machine_thread_id,NULL);
    printf("machine detenido...\n");

    pthread_cancel(clock_id);
    pthread_join(clock_id,NULL);
    printf("clock detenido...\n");
    
}