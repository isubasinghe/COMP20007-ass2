#include "gedit.h"

char *delete_gen(char *s, int slen, int i) {
    char *data = malloc((slen+1)*sizeof(char));
    memset(data, 0, (slen+1));
    int w=0;

    for(int j=0; j < slen; j++) {
        if(i != j) {
            data[w] = s[j];
            w++;
        }
    }
    data[w] = 0;
    return data;
}

char *edit_gen(char *s, int slen, int i, char c) {
    char *data = malloc((slen+1)*sizeof(char));
    memcpy(data, s, strlen(s)+ 1);
    data[i] = c;
    return data;
}

char *insert_gen(char *s, int slen, int i, char c) {
    char *data = malloc((slen + 2)*sizeof(char));
    memset(data, 0, slen + 2);

    if(i == slen) {
        memcpy(data, s, slen);
        data[slen] = c;
        return data;
    }

    int copyfrom = 0;

    for(int j=0; j < slen; j++) {
        if(j!=i) {
            data[j] = s[j];
        }else {
            data[j] = c;
            copyfrom = j;
            break;
        }
    }
    memcpy(data+copyfrom+1, s+copyfrom, slen - copyfrom);

    return data;
}

warray_t *gen_edit_one(char *s) {
    warray_t *warray = new_warray();
    int slen = strlen(s);
    for(int i=0; i < slen; i++) {
        warray_append(warray, delete_gen(s, slen, i));
        for(int j=ASCII_START; j <= ASCII_END; j++) {
            warray_append(warray, insert_gen(s, slen, i, j));
            warray_append(warray, edit_gen(s, slen, i, j));
        }
    }
    for(int i=ASCII_START; i <= ASCII_END; i++) {
        warray_append(warray, insert_gen(s, slen, slen, i));
    }
    return warray;
}

warray_t *gen_edit_over(warray_t *warray) {
    for(int i=0; i < warray->written; i++) {
        warray_t *warray2 = gen_edit_one(warray->data[i]);
        for(int j=0; j < warray2->written; j++) {
            warray_append(warray, warray2->data[j]);
        }
        free_warray(warray2);
    }
    return warray;
}