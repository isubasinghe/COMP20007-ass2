#ifndef GEDIT_H
#define GEDIT_H

#define ASCII_START 'a'
#define ASCII_END 'z'

#define ALPHABET_SIZE 26
#define INSERTION_SIZE 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char **data;
    int written;
    int cap;
} warray_t;

warray_t gen_edit_one(char *);

char *delete_gen(char *s, int i);

char *insert_gen(char *s, int i, char c);

char *edit_gen(char *s, int i, char c);

void free_warray(warray_t *w);


#endif // GEDIT_H