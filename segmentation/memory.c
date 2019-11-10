#include "memory.h"

extern unsigned int end;

unsigned int placement_address = (unsigned int)&end;

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
    unsigned int tmp = placement_address;
    placement_address += sz;
    return tmp;
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

