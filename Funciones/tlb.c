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
    if(tlb->size>=tlb->max_size){ //remplazar lru
        lru_remove(tlb);
    }
    t_nodo_tlb *nodo=malloc(sizeof(t_nodo_tlb));
    nodo->frame=frame;
    nodo->page=page;
    
    int i= tlb_hash(page);
    nodo->next_colision=tlb->hash_table[i];
    tlb->hash_table[i]=nodo;
    nodo->prev_lru=NULL;
    nodo->next_lru=tlb->mru;

    if(tlb->mru!=NULL){
        tlb->mru->prev_lru=nodo;
    }
    tlb->mru=nodo;
    if(tlb->lru==NULL){
        tlb->lru=nodo;
    }
    tlb->size++;
}
void lru_remove(t_tlb *tlb){
    if(tlb->lru==NULL) return;
    t_nodo_tlb *nodo=tlb->lru;
    if(nodo->prev_lru !=NULL){
        nodo->prev_lru->next_lru=NULL;
    }
    if(tlb->mru==nodo) tlb->mru=NULL;

    int i=tlb_find(tlb,nodo->page);
    t_nodo_tlb *prev=NULL;
    t_nodo_tlb *actual=tlb->hash_table[i];
    while(actual!=NULL&& actual !=nodo){
        prev=actual;
        actual=actual->next_colision;
    }
    if(prev==NULL){
        tlb->hash_table[i]=nodo->next_colision;    
    }
    else{
        prev->next_colision=nodo->next_colision;
    }
    free(nodo);
    tlb->size--;
}
void to_mru(t_tlb *tlb,t_nodo_tlb *nodo){
    if(nodo=tlb->mru)return;
    if(nodo->prev_lru!=NULL){
        nodo->prev_lru->next_lru=nodo->next_lru;
    }
    if(nodo->next_lru!=NULL){
        nodo->next_lru->prev_lru=nodo->prev_lru;
    }
    if(nodo==tlb->lru){
        tlb->lru=nodo->prev_lru;
    }
    nodo->prev_lru=NULL;
    if(tlb->mru!=NULL){
        nodo->next_lru=tlb->mru;
    }
    tlb->mru=nodo;
    if(tlb->lru==NULL){
        tlb->lru=nodo;
    }
}

#endif
