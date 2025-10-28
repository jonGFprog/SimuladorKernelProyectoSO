#include <pthread.h>
#include "Hilos/clock.c"
int main (int argc, char *argv[]) {
    pthread_t clock_id;
    pthread_create(&clock_id,NULL,clock_thread, NULL);
    pthread_join(clock_id,NULL);
}