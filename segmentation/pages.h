#ifndef INCLUDE_PAGES_H
#define INCLUDE_PAGES_H

#include "../utils/common.h"
typedef struct page
{
    unsigned int present: 1; // Is the page present in memory
    unsigned int rw: 1;     // RO if clear, RW if set
    unsigned int user: 1;   // Is the page user accessible 
    unsigned int accessed: 1; // Has the page been accessed since last refresh
    unsigned int dirty: 1;  // Has the page been written to since last refresh;
    unsigned int unused: 7; // Unused and reserved bits
    unsigned int frame: 20; // Physical address of the frame
} page_t;

typedef struct page_table
{
    page_t pages[1024];
} page_table_t;


typedef struct page_directory
{
    /*
    * Array of pointers to the pagetables
    */
    page_table_t *tables[1024];
    
    /*
    * Array of pointers to the physical addresses of pagetables
    */
    unsigned int tablesPhysical[1024];

    /*
    * Physical address of the page directory
    */
    unsigned int physicalAddr;
}  page_directory_t;

void initialize_paging();


void switch_page_directory(page_directory_t *new);

page_t *get_page(unsigned int address, int make, page_directory_t *dir, int isHigherHalf);

void alloc_frame(page_t *page, int is_kernel, int is_writeable);
void free_frame(page_t  *page);


extern void loadPageDirectory(uint32_t val);
extern void enablePaging();

#endif /** INCLUDE_PAGES_H */