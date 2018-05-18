#ifndef GEDIT_H
#define GEDIT_H

#define ASCII_START 'a'
#define ASCII_END 'z'

#define ALPHABET_SIZE 26
#define INSERTION_SIZE 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "warray.h"


warray_t *gen_edit_one(char *);

warray_t *gen_edit_over(warray_t *);


char *delete_gen(char *, int, int );

char *insert_gen(char *, int, int , char );

char *edit_gen(char *s, int, int , char );

void free_warray(warray_t *);




#endif // GEDIT_H