#include "gedit.h"

char *delete_gen(char *s, int slen, int i) {
    // Allocate memory in order to store the string
    char *data = malloc((slen+1)*sizeof(char));
    // Ensure the null byte is set this way
    memset(data, 0, (slen+1));
    int w=0;

    for(int j=0; j < slen; j++) {
        // It isn't the deletion character
        // so copy
        if(i != j) {
            data[w] = s[j];
            w++;
        }
    }

    // Once again make sure the last written is the NULL byte
    data[w] = 0;
    return data;
}

char *edit_gen(char *s, int slen, int i, char c) {
    // Memory for the string.
    char *data = malloc((slen+1)*sizeof(char));
    memcpy(data, s, strlen(s)+ 1);
    // Change the value to the character
    data[i] = c;
    return data;
}

char *insert_gen(char *s, int slen, int i, char c) {
    // Allocate memory for string.
    // plus 2 since memory size of s + 1
    char *data = malloc((slen + 2)*sizeof(char));
    // Ensure NULL bytes
    memset(data, 0, slen + 2);

    // This is the edge case where we want to insert to
    // the end of the string
    if(i == slen) {
        memcpy(data, s, slen);
        // set the character at thg end
        data[slen] = c;
        return data;
    }

    // We need to know where we can insert the rest of the string from
    int copyfrom = 0;

    for(int j=0; j < slen; j++) {
        if(j!=i) {
            // We can insert
            data[j] = s[j];
        }else {
            // Reached the point where we have copied all we can
            data[j] = c;
            copyfrom = j;
            // We need to stop now
            break;
        }
    }
    // Copy the rest of the string
    memcpy(data+copyfrom+1, s+copyfrom, slen - copyfrom);

    return data;
}

warray_t *gen_edit_one(char *s) {
    // Create a new char ** array to store strings in
    warray_t *warray = new_warray();
    int slen = strlen(s);
    // Iterate for all the string length
    for(int i=0; i < slen; i++) {
        // Delete at position i
        warray_append(warray, delete_gen(s, slen, i));
        // Iterate from a to z
        for(int j=ASCII_START; j <= ASCII_END; j++) {
            // Insert at position i a j character
            warray_append(warray, insert_gen(s, slen, i, j));
            // Chnage at position i to a j character
            warray_append(warray, edit_gen(s, slen, i, j));
        }
    }
    
    for(int i=ASCII_START; i <= ASCII_END; i++) {
        // Append a i character at the end of the string.
        warray_append(warray, insert_gen(s, slen, slen, i));
    }
    return warray;
}