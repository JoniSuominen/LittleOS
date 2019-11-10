#ifndef INCLUDE_MEMORY_H
#define INCLUDE_MEMORY_H


unsigned int kmalloc(unsigned int sz);
unsigned int kmalloc_a(unsigned int sz, int align);
unsigned int kmalloc_p(unsigned int sz, unsigned int *phys);
unsigned int kmalloc_ap(unsigned int sz, int align, unsigned int *phys);



extern void loadPageDirectory(unsigned int * val);
extern void enablePaging();

#endif /** INCLUDE_MEMORY_H */