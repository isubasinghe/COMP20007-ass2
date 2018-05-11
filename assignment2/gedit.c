#include "gedit.h"

char *delete_gen(char *s, int i) {
    char *data = malloc((strlen(s)+1)*sizeof(char));
    memset(data, 0, (strlen(s)+1));
    int w=0;

    for(int j=0; j < strlen(s); j++) {
        if(i != j) {
            data[w] = s[j];
            w++;
        }
    }
    data[w] = 0;
    return data;
}

char *edit_gen(char *s, int i, char c) {
    char *data = malloc((strlen(s)+1)*sizeof(char));
    memcpy(data, s, strlen(s)+ 1);
    data[i] = c;
    return data;
}

char *insert_gen(char *s, int i, char c) {
    char *data = malloc((strlen(s) + 2)*sizeof(char));
    memset(data, 0, strlen(s) + 2);

    if(i == strlen(s)) {
        memcpy(data, s, strlen(s));
        data[strlen(s)] = c;
        return data;
    }

    int copyfrom = 0;

    for(int j=0; j < strlen(s); j++) {
        if(j!=i) {
            data[j] = s[j];
        }else {
            data[j] = c;
            copyfrom = j;
            break;
        }
    }
    memcpy(data+copyfrom+1, s+copyfrom, strlen(s) - copyfrom);

    return data;
}

void warray_append(warray_t *w, char *s) {
    if(w->cap <= w->written) {
        w->cap *= 2;
        w->data = realloc(w->data, w->cap*sizeof(char));
    }
    w->data[w->written] = s;
    w->written++;
}

warray_t gen_edit_one(char *s) {
    int slen = strlen(s);
    warray_t warray;
    warray.cap = slen + ALPHABET_SIZE*(slen+INSERTION_SIZE) + 26*slen;
    warray.data = (char **) malloc(warray.cap*sizeof(char *));
    warray.written = 0;
    
    for(int i=0; i < slen; i++) {
        warray_append(&warray, delete_gen(s, i));
        for(int j=ASCII_START; j <= ASCII_END; j++) {
            warray_append(&warray, insert_gen(s, i, j));
            warray_append(&warray, edit_gen(s, i,j));
        }
    }

    for(int i=ASCII_START; i <= ASCII_END; i++) {
        warray_append(&warray, insert_gen(s, slen, i));
    }

    return warray;
    
}


void free_warray(warray_t *w) {
    for(int i=0; i < w->written; i++) {
        free(w->data[i]);
    }
    free(w->data);
}
