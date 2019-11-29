#include "memory.h"
#include "kheap.h"

extern unsigned int end;

unsigned int placement_address = (unsigned int)&end;
extern heap_t *kheap;


void kfree(void *p) {
    free(p, kheap);
}
unsigned int kmalloc_a(unsigned int sz, int align) {
    if (align == 1 &&(placement_address & 0xFFFFF000)) {
        placement_address &= 0xFFFFF000;
        placement_address += 0x1000;
    }

    unsigned int tmp = placement_address;
    placement_address += sz;
    return tmp;
}

unsigned int kmalloc(unsigned int sz) {
    if (kheap != 0)
    {
        void *addr = alloc(sz, 0, kheap);
        return (uint32_t) addr;

    } else {
    unsigned int tmp = placement_address;
    placement_address += sz;
    return tmp;
    }
}


unsigned int kmalloc_ap(unsigned int sz, int align, unsigned int *phys) {
    
        if (align == 1 &&(placement_address & 0xFFFFF000)) {
            placement_address &= 0xFFFFF000;
            placement_address += 0x1000;
        }

        if(phys){
            *phys = placement_address;

        }

        unsigned int tmp = placement_address;
        placement_address += sz;
        return tmp;
    
}


unsigned int kmalloc_p(unsigned int sz, unsigned int *phys) {

    if(phys){
        *phys = placement_address;
    }

    unsigned int tmp = placement_address;
    placement_address += sz;
    return tmp;
}

