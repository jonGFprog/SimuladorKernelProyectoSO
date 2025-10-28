#include <stdio.h>
#include <unistd.h>
void* clock_thread(void* arg) {
    __uint128_t i=0;
    printf("Reloj iniciado\n");
    while(1){
        int *hz_clock=arg;
        usleep(hz_clock[0]); //usa microsegundos, 1 seg=1000000
        i++;
        printf("ciclo %d\n",i);
    }
}

