#ifndef INCLUDE_PAGES_H
#define INCLUDE_PAGES_H


void init_page_directory();
void init_page_table();


extern void loadPageDirectory(unsigned int * val);
extern void enablePaging();

#endif /** INCLUDE_PAGES_H */