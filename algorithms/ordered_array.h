#ifndef ORDERED_ARRAY_H
#define ORDERED_ARRAY_H

#include "../utils/common.h"

typedef void * type_t;
typedef int8_t (*lessthan_predicate_t)(type_t, type_t);

typedef struct {
    type_t * array;
    uint32_t size;
    uint32_t max_size;
    lessthan_predicate_t less_than;
} ordered_array_t;

/* Check if item is less than */
int8_t standard_lessthan_predicate(type_t a, type_t b);

/** Create an ordered array */
ordered_array_t create_ordered_array(uint32_t max_size, lessthan_predicate_t less_than);
ordered_array_t place_ordered_array(void *addr, uint32_t max_size, lessthan_predicate_t less_than);


/** Destroy an ordered array */
void destroy_ordered_array(ordered_array_t *array);

/** Insert item to ordered array */
void insert_ordered_array(type_t item, ordered_array_t *array);

/** Look up item at index i */
type_t lookup_ordered_array(uint32_t i, ordered_array_t *array);


/** Delete item at index i */
void remove_ordered_array(uint32_t i, ordered_array_t * array);

#endif // ORDERED_ARRAY_H