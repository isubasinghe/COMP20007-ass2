#include <stdio.h>
#include <stdlib.h>
#include "lshtein.h"

int main(int argc, char *argv[]) {

    if(argc==3) {
        //ldist(argv[1], argv[2]);
        printf("%d\n", ldist(argv[1], argv[2]));
    }
    return 0;
}