#include <stdint.h>
#include "tlb.h"
#ifndef MMU_H
#define MMU_H

typedef struct 
{
    t_tlb tlb;
}t_mmu;

void traduccion(t_mmu *mmu, uint32_t dir); 
#endif


