#include "lshtein.h"


// function inlining is important here
// for speed.

inline int min3(int a, int b, int c){
    // Return the minimum of 3 variables
    return a < b ? (a < c ? a : c) : (b < c ? b : c);
}

int ldist(char *a, char *b) {
    int alen = strlen(a);
    int blen = strlen(b);
    // Memory needed for a (alen) by (blen) matrix 
    // represented by a vector
    int memsize = (alen + 1)*(blen + 1);
    // Using a vector allows memory to
    // get cached.
    int *mat = malloc(memsize* sizeof(int));
    
    
    for(int i=0; i <= alen; i++) {
        // Access the (i, 0)
        // a multiplication has to be done
        // in order to get the position in 
        // the vector
        mat[i*(blen + 1)] = i;
    }

    for(int j=1; j <= blen; j++) {
        // Access the (0, j)
        mat[j] = j;
    }

    for(int i=1; i <= alen; i++) {
        for(int j=1; j <= blen; j++) {
            // Check if the characters are the same
            int p = !(a[i-1] == b[j-1]);

            // Current writing position
            int pos = i*(blen+1) + j;

            // Check the neighbours for 
            // the minumum edit distance

            // Check (i-1, j-1)
            int pos1 = (i-1)*(blen+1) + (j-1);
            // Check (i-1, j)
            int pos2 = (i-1)*(blen+1) + j;
            // Check (i, j-1)
            int pos3 = (i)*(blen+1) + (j-1);

            // Write the minumum to the 
            // current writing position
            mat[pos] = min3(
                mat[pos1] + p,
                mat[pos2] + 1,
                mat[pos3] + 1
            );
        }
    }
    // Obtain the last values of the matrix
    int dist = mat[memsize-1];
    free(mat);
    return dist;

}