#include "memory.h"
#include "pages.h"
#include "../utils/common.h"
#include "../algorithms/ordered_array.h"

#define KHEAP_START         0x400080
#define KHEAP_INITIAL_SIZE  0x100000
#define HEAP_INDEX_SIZE   0x20000
#define HEAP_MAGIC        0x123890AB
#define HEAP_MIN_SIZE     0x70000

typedef struct
{
    uint32_t magic; // magic number for error handling
    uint8_t is_hole; // 1 if hole, 0 if block
    uint32_t size; // size of block
} header_t;

typedef struct
{
    uint32_t magic;
    header_t *header; // points to a block
} footer_t;

typedef struct
{
    ordered_array_t index;
    uint32_t start_address; // start of allocated space
    uint32_t end_address; // end of our allocated space
    uint32_t max_address; // max address the heap can be expanded to
    uint8_t supervisor;  // Should extra pages requested by us be mapped as supervisor-only?
    uint8_t readonly;    // Should extra pages requested by us be mapped as read-only?
} heap_t;

// Create a new heap
heap_t *create_heap(uint32_t start, uint32_t end, uint32_t max, uint8_t supervisor, uint8_t readonly);

// allocate a contigious region of memory ("size") in size, if page align is one, the block is page aligned
void *alloc(uint32_t size, uint8_t page_align, heap_t *heap);


// Release a block allocated with "alloc"
void free(void *p, heap_t *heap);
