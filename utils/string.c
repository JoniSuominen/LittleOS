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

void memset(void *b, int c, int len)
{
  int           i;
  unsigned char *p = b;
  i = 0;
  while(len > 0)
    {
      *p = c;
      p++;
      len--;
    }
  return(b);
}