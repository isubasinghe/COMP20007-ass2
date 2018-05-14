#include "hash.h"

unsigned int xorhash(char *s, int seed, int m) {
    unsigned int h = seed;
    char c;

    for(int i=0; (c = s[i]) != '\0'; i++) {
        h = h ^ ( (h << 5) + c + (h >> 2) );
    }
    return h%m;
}