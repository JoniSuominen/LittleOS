#ifndef INCLUDE_STRING
#define INCLUDE_STRING
typedef unsigned int   uint32_t;
typedef uint32_t 		size_t;

unsigned int strlen(char *string);
char* itoa(int val, int base);
void memset(unsigned char *dest, unsigned char val, unsigned int len);

#endif /** INCLUDE_STRING */