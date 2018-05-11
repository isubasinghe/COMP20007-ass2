#include <stdio.h>
#include <stdlib.h>

#include "lshtein.h"
#include "gedit.h"


int main(int argc, char *argv[]) {
    if(argc ==2) {
        warray_t leven1 = gen_edit_one(argv[1]);
        for(int i=0; i < leven1.written; i++) {
            warray_t leven2 = gen_edit_one(leven1.data[i]);
            for(int j=0; j < leven2.written; j++) {
                warray_t leven3 = gen_edit_one(leven2.data[j]);
                for(int k=0; k < leven3.written; k++) {
                    printf("%s\n", leven3.data[k]);
                }
                free_warray(&leven3);
            }
            free_warray(&leven2);
        }
        free_warray(&leven1);
    }
    return 0;
}