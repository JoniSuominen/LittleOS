#ifndef INCLUDE_STRING
#define INCLUDE_STRING
#include "common.h"

unsigned int strlen(char *string);
char* itoa(int val, int base);
void memset(void *dest, unsigned char val, unsigned int len);

void memcpy(uint8_t *dest, const uint8_t *src, uint32_t len);
void strcpy(uint8_t *dest, const char *src);

int strcmp(char *str1, char *str2);
#endif /** INCLUDE_STRING */