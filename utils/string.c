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