#ifndef INCLUDE_FRAMES_H
#define INCLUDE_FRAMES_H

void alloc_frame(page_t *page, int is_kernel, int is_writeable);
void free_frame(pate_t  *page);

#endif