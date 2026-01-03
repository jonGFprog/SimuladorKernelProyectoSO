#include <stdint.h>
#include "tlb.h"
#ifndef MMU_H
#define MMU_H

typedef struct 
{
    t_tlb tlb;
}t_mmu;

void traduccion(t_mmu *mmu, uintptr_t ptbr, uint32_t dir); 
void buscar_en_memoria(uint32_t dir);
#endif


