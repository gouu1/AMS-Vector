#include <stdio.h>
#include <stdlib.h>
#include "dbl_vector.h" 

void dv_init( dbl_vector_t* vec ) {
    vec->capacity = DV_INITIAL_CAPACITY;
    vec->size = 0;
    vec->data = malloc(vec->capacity * sizeof(double));
}

void dv_ensure_capacity( dbl_vector_t* vec, size_t new_size ) {
    if (new_size > vec->capacity) {

        // find the max of the two capacities
        size_t old_capacity = vec->capacity * DV_GROWTH_FACTOR; 
        size_t new_capacity = (old_capacity > new_size) ? old_capacity : new_size;

        vec->capacity = new_capacity;
        vec->data = realloc(vec->data, new_capacity * sizeof(double));
    }
}

void dv_destroy( dbl_vector_t* vec ) {
    vec->capacity = 0;
    vec->size = 0;
    free(vec->data);
    vec->data = NULL;
}

void dv_copy( dbl_vector_t* vec, dbl_vector_t* dest ) {
    if (vec == dest) {
        // stop right there criminal scum
        return;
    }

    dest->size = vec->size;
    dv_ensure_capacity(dest, vec->size);

    for (int i = 0; i < vec->size; i++) {
        dest->data[i] = vec->data[i];
    }
}

void dv_clear( dbl_vector_t* vec ) {
    vec->size = 0;
}

void dv_push( dbl_vector_t* vec, double new_item ) {
    size_t old_size = vec->size;

    dv_ensure_capacity(vec, old_size + 1);
    vec->size = old_size + 1;

    vec->data[old_size] = new_item;
}

void dv_pop( dbl_vector_t* vec ) {
    if (vec->size > 0) { // do something if there is data
        vec->size -= 1; // "remove" the trailing element
    } else vec->size = 0;
}

double dv_last( dbl_vector_t* vec ) {
    double result = NAN;

    if (vec->size > 0) result = vec->data[vec->size - 1];

    return result;
}

void dv_insert_at( dbl_vector_t* vec, size_t pos, double new_item ) {
    size_t old_size = vec->size;
    size_t loc = (pos < old_size) ? pos : old_size; // MIN func 

    dv_ensure_capacity(vec, old_size + 1);
    vec->size = old_size + 1;

    double first = vec->data[loc];
    double temp; // init for the swap about to happen
    vec->data[loc] = new_item; // add new value at loc

    for (int i = loc + 1; i < vec->size; i++) { // only need to add from loc

        temp = vec->data[i];

        vec->data[i] = first;

        first = temp;
    }
}

void dv_remove_at( dbl_vector_t* vec, size_t pos ) {
    size_t old_size = vec->size;
    size_t loc = (pos < old_size) ? pos : old_size; // MIN func

    if (pos < old_size) {
        for (int i = loc; i < vec->size - 1; i++) {
            vec->data[i] = vec->data[i+1];
        }
        vec->size -= 1;
    }
}

void dv_foreach( dbl_vector_t* vec, void (*callback)(double, void*), void* info ) {
    for (int i = 0; i < vec->size; i++) {
        callback(vec->data[i], info);
    }
}
