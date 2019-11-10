#include "pages.h"
#include "../io/io.h"
#include "../utils/string.h"
#include "memory.h"

unsigned int *frames;
unsigned int nframes;
/*
page_directory_t *kernel_directory	= 0;

// The current page directory
page_directory_t *current_directory	= 0;
*/

unsigned int * kernel_directory = 0;

extern unsigned int placement_address;

#define INDEX_FROM_BIT(a) (a/(8*4))
#define OFFSET_FROM_BIT(a) (a%(8*4))



static void set_frame(unsigned int frame_addr) {
    unsigned int frame = frame_addr/0x1000;
    unsigned int idx = INDEX_FROM_BIT(frame);
    unsigned int off = OFFSET_FROM_BIT(frame);
    frames[idx] |= (0x1 << off);
}

static void clear_frame(unsigned int frame_addr) {
    unsigned int frame =frame_addr / 1000;
    unsigned int idx = INDEX_FROM_BIT(frame);
    unsigned int off = OFFSET_FROM_BIT(frame);
    frames[idx] &=  ~(0x1 << off);
}
/*
static unsigned int test_frame(unsigned int frame_addr) {
    unsigned int frame = frame_addr / 0x1000;
    unsigned int idx = INDEX_FROM_BIT(frame);
    unsigned int off = OFFSET_FROM_BIT(frame);
    return (frames[idx] & (0x1 << off));
}
*/

static unsigned int first_frame() {
    unsigned int i, j;
    for (unsigned int i = 0; i < INDEX_FROM_BIT(nframes); i++) {
        if (frames[i] != 0xFFFFFFFF) {
            for (j = 0; j < 32; j++) {
                unsigned int toTest = 0x1 << j;
                if (!(frames[i]&toTest)) {
                    return i * 4 * 8 + j;
                }
            }
        }
    }
    return 0;
}

void alloc_frame(page_t *page, int is_kernel, int is_writeable) {
    if (page->frame != 0) {
        return;
    } else {
        unsigned int idx = first_frame();
        if (idx == (unsigned int) - 1)
        {
            char * panic = "No free frames!";
            printf(panic, TYPE_FRAMEBUFFER, strlen(panic));
            while(1);
        }
        set_frame(idx * 0x1000);
        page->present = 1;
        page->rw = (is_writeable)?1:0;
        page->user = (is_kernel)?0:1;
        page->frame = idx;
    }
}

void free_frame(page_t * page) {
    unsigned int frame;
    if (!(frame=page->frame)) {
        return;
    } else {
        clear_frame(frame);
        page->frame = 0x0;
    }
}

void initialize_paging() {
    unsigned int mem_end_page = 0x1000000;
    nframes = mem_end_page / 0x1000;
    printf(itoa(placement_address, 16), TYPE_FRAMEBUFFER, strlen(itoa(placement_address, 16)));
    frames = (unsigned int *) kmalloc(INDEX_FROM_BIT(nframes));
    printf("hei", TYPE_FRAMEBUFFER, strlen("hei"));
    kernel_directory = (page_directory_t*)kmalloc_a(sizeof(page_directory_t), 1);
    
    for (int i = 0; i < 1024; i++) {
        page_table_t* temp = (page_table_t *) 0;
        kernel_directory->tables[i] = temp;
    }
    
    kernel_directory->tables[768] = (page_table_t *) 0x83;
    //kernel_directory->tablesPhysical[768] =  (unsigned int) (((page_table_t*) 0x83) - 0xC0000000);
    switch_page_directory(kernel_directory);
    
    /*
   unsigned int i = 0;
   
   while (i < placement_address)
   {
       // Kernel code is readable but not writeable from userspace.
       alloc_frame( get_page(i, 1, kernel_directory), 0, 0);
       i += 0x1000;
   }
   kernel_directory->tables[768] = (page_table_t*) 0x83;

    
    switch_page_directory(kernel_directory);
    */

}

void switch_page_directory(page_directory_t  *dir) {
    current_directory = dir;
    page_directory_t * newDir = dir;
    newDir -= 0xC0000000;
    loadPageDirectory((unsigned int * )newDir->tables);
    enablePaging();
}

page_t *get_page(unsigned int address ,int make, page_directory_t *dir) {
    address /= 0x1000;
    unsigned int tables_idx = address / 1024;

    if (dir->tables[tables_idx]) {
        return &dir->tables[tables_idx]->pages[address % 1024];
    } else if (make) {
        unsigned int temp;
        dir->tables[tables_idx] = (page_table_t*)kmalloc_p(sizeof(page_table_t), &temp);
        memset((unsigned char *) dir->tables[tables_idx], 0, 0x1000);
        dir->tablesPhysical[tables_idx] = temp |= 0x7;
        return &dir->tables[tables_idx]->pages[address%1024];
    } else {
        return 0;
    }

}

