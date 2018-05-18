#include "warray.h"

warray_t *new_warray() {
    warray_t *warray = (warray_t *)malloc(sizeof(warray_t));
    warray->cap = INITIAL_SIZE;
    warray->data = malloc(warray->cap * sizeof(char *));
    warray->written = 0;
    return warray;
}

void warray_append(warray_t *w, char *s) {
    if(w->written >= w->cap) {
        w->cap *= 2;
        w->data = realloc(w->data, w->cap*sizeof(char *));
    }
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

