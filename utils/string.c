#include "string.h"

/**
 * Returns the length of given string
 * @param string - pointer of char-variables
 */
unsigned int strlen(char *string) {
  unsigned int len = 0;
  unsigned int i = 0;
  while (string[i] != '\0') { 
    len++;
    i++;
  }
  return len;
}

char* itoa(int val, int base){

    static char buf[32] = {0};

    int i = 30;

    for(; val && i ; --i, val /= base)

        buf[i] = "0123456789abcdef"[val % base];

    return &buf[i+1];

}

void memset(void *dest, unsigned char val, unsigned int len) {
  for (unsigned char * temp = dest; len != 0; len--) {
    *temp = val;
  }
}

void memcpy(uint8_t *dest, const uint8_t *src, uint32_t len)
{
    const uint8_t *sp = (const uint8_t *)src;
    uint8_t *dp = (uint8_t *)dest;
    for(; len != 0; len--) *dp++ = *sp++;
}

void strcpy(uint8_t *dest, const char *src)
{
  while (*src != 0) {
    *dest++ = *src++;
  }
}

int strcmp(char *str1, char *str2) {
  {
    int i = 0;
    while(str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) {
            if (str1[i] < str2[i]) {
              return -1;
            } else {
              return 1;
            }
        }
    }

    return 0;
}
}