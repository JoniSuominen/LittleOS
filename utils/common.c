#include "common.h"
#include "../io/io.h"
#include "string.h"

void ASSERT(int check, char * function) {
    char * fail = "ASSERT FAILED ";
    if (check == -1) {      
        printf(fail, TYPE_FRAMEBUFFER, strlen(fail));
        printf(function, TYPE_FRAMEBUFFER, strlen(function));
        while(1);
    }
}