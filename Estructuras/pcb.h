#include <stdint.h>
#ifndef PCB_H
#define PCB_H

typedef struct 
{
    uintptr_t code;
    uintptr_t data;
    uintptr_t pgb;
}t_mm;

typedef struct
{/**/
    uint64_t id; //el proceso nulo tiene id 0
    uint8_t partido; //0 si no es parte del partido, 1 si lo es
    //uint16_t ciclos_asignados; //ciclos maximos antes de su ejecucion publica; movido a machine
    uint16_t ciclos_usados;  
    uint16_t paciencia; //solo importante si es un proceso del partido*/
    uint8_t fin; //fin=0 representa que aun no ha terminado el proceso, fin=1 representa que el proceso ha terminado
    uint16_t quantum; //contador del quantum, compararlo con machine.quantum
    //fase3 
    t_mm mm;
} t_pcb;

t_pcb pcbnulo;
#endif


