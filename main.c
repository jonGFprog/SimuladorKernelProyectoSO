#include <pthread.h>
#include <stdlib.h>
#include "Hilos/clock.c"
int main (int argc, char *argv[]) {
    if(argc!=2){
        printf("Numero incorrecto de argumentos.\n");
        exit(1);
    }
    pthread_t clock_id;
    int hz_clock=atoi(argv[1]); //esta en milisegundos
    pthread_create(&clock_id,NULL,clock_thread, &hz_clock);
    pthread_join(clock_id,NULL);
}