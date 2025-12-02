typedef struct
{
    __uint64_t id;
    __uint8_t partido; //0 si no es parte del partido, 1 si lo es
    __uint16_t ciclos_asignados; //ciclos maximos antes de su ejecucion publica
    __uint16_t ciclos_usados;  
    __uint16_t quantum; //tiempo de cpu asignado por el lider
    __uint16_t paciencia; //solo importante si es un proceso del partido
} t_pcb;

