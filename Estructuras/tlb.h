
#include <stdint.h>
#ifndef TLB_H
#define TLB_H
#define TLB_SIZE 64
#define TLB_MISS -1
#define HASH_SIZE 256
//TLB va a ser una hashtable con lru para el remplazo
typedef struct{
    uint32_t frame;
    uint32_t page;
    struct t_nodo_tlb* next_colision;
    struct t_nodo_tlb* next_lru; //Lista doblemente enlazada ordenada en funcion del uso de los nodos
    struct t_nodo_tlb* prev_lru;
}t_nodo_tlb;

typedef struct{
    t_nodo_tlb* hash_table[HASH_SIZE];
    t_nodo_tlb* mru; //Nodo mas usado  recientemente 
    t_nodo_tlb* lru; //Nodo menos usado recientemente
    int max_size;
    int size;
    int hits; //igual sobra
    int misses; //igual sobra
}t_tlb;

void init_tlb(t_tlb *tlb);
unsigned int tlb_hash(uint32_t page);
uint32_t tlb_find(t_tlb* tlb, uint32_t page);
void tlb_insert(t_tlb *tlb, uint32_t page, uint32_t frame);
void lru_remove(t_tlb *tlb);
void to_mru(t_tlb *tlb,t_nodo_tlb *nodo);

#endif
