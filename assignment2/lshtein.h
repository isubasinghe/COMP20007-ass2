#ifndef LSHTEIN_H
#define LSHTEIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int **data;
    int m,n;
} mat_t;

mat_t new_matrix(int , int );

int wmati(mat_t *, int, int , int ); // write mat index

int rmati(mat_t *, int, int); // read mat index

void free_matrix(mat_t *);

int ldist(char *, char *);

#endif // LSHTEIN_H