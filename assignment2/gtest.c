#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


#include "gedit.h"
#include "lshtein.h"


int main(int argc, char *argv[]) {
    warray_t w = gen_edit_one("helloworld");

    free_warray(&w);

    return 0;
}