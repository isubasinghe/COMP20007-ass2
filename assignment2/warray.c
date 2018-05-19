#include "warray.h"

warray_t *new_warray() {
    // Create a new array structure in the heap
    warray_t *warray = (warray_t *)malloc(sizeof(warray_t));
    // Add some memory to it
    warray->cap = INITIAL_SIZE;
    warray->data = malloc(warray->cap * sizeof(char *));
    warray->written = 0;
    return warray;
}

void warray_append(warray_t *w, char *s) {
    if(w->written >= w->cap) {
        // Run out of memory so realloc some more
        w->cap *= 2;
        w->data = realloc(w->data, w->cap*sizeof(char *));
    }
    // Write to the next spot
    w->data[w->written] = s;
    w->written++;
}

void free_warray(warray_t *w) {
    for(int i=0; i < w->written; i++) {
        free(w->data[i]);
    }
    free(w->data);
    free(w);
}

