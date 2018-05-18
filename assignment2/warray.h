#ifndef WARRAY_H
#define WARRAY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef INITIAL_SIZE
#define INITIAL_SIZE 128
#endif // INITIAL_SIZE

typedef struct {
    int cap;
    int written;
    char **data;
} warray_t;

warray_t *new_warray();

void warray_append(warray_t *, char *);

void free_warray(warray_t *);


#endif // WARRAY_H