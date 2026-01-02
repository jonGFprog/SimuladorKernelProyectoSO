#include <stdint.h>
#include <stddef.h> // para el null
#include "../Estructuras/tlb.h"
#ifndef TLB_C
#define TLB_C

void init_tlb(t_tlb *tlb){
    tlb->max_size=TLB_SIZE;
    tlb->size=0;
    tlb->hits=0;
    tlb->misses=0;
    tlb->lru = NULL;
    tlb->mru = NULL;
    for(int i=0;i<HASH_SIZE;i++){
        tlb->hash_table[i]=NULL;
    }
}
unsigned int tlb_hash(uint32_t page){
    return page % HASH_SIZE;
}
uint32_t tlb_find(t_tlb* tlb, uint32_t page){
    int i = tlb_hash(page);
    t_nodo_tlb *nodo = tlb->hash_table[i];

    while(nodo!=NULL){
        if(nodo->page==page){
            tlb->hits++;
            to_mru(tlb,nodo);
            return nodo->frame;
        }
        nodo=nodo->next_colision;
    }
    tlb->misses++;
    return TLB_MISS;
}
void tlb_insert(t_tlb *tlb, uint32_t page, uint32_t frame){
    if(tlb_find(tlb,page)!=TLB_MISS)return;
    if(tlb->size<tlb->max_size){ 
        
    }
    else{ //remplazar lru

    }
}
void lru_remove(t_tlb *tlb){

}
void to_mru(t_tlb *tlb,t_nodo_tlb *nodo){

}

#endif
