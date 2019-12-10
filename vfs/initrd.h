#ifndef  INITRD_H
#define INITRD_H

#include "../utils/common.h"
#include "vfs.h"

typedef struct
{
    uint32_t nfiles; // number of files in ramdisk
} initrd_header_t;

typedef struct
{
    uint8_t magic;
    int8_t name[64];
    uint32_t offset;
    uint32_t length;
} initrd_file_header_t;

fs_node_t *initialize_initrd(uint32_t location);

#endif