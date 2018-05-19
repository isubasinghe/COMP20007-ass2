#include "lshtein.h"

// Matrix struct to make it easier to debug edit distance
mat_t new_matrix(int m, int n) {
    mat_t mat;
    mat.m = m;
    mat.n = n;
    mat.data = malloc(m*sizeof(int *));
    for(int i=0; i < m; i++) {
        int *row = malloc(n*sizeof(int));
        mat.data[i] = row;
    }
    return mat;
}

void free_matrix(mat_t *m) {
    for(int i=0; i < m->m; i++) {
        free(m->data[i]);
    }
    free(m->data);
}

int wmati(mat_t *m, int i, int j, int val) {
    // Check dimensions
    if (i >= m->m) {
        fprintf(stderr, "Matrix Dimensions out of bound in i:\n");
        fprintf(stderr, "\ti: %d accessed %d\n", m->m, i);
        return -1;
    }else if(j >= m->n) {
        fprintf(stderr, "Matrix Dimensions out of bound in j:\n");
        fprintf(stderr, "\tj: %d accessed %d\n", m->n, j);
        return -1;
    }else {
        // Valid indexes so write value
        m->data[i][j] = val;
        return 0;
    }
}

int rmati(mat_t *m, int i, int j) {
    // Check dimensions
    if (i >= m->m) {
        fprintf(stderr, "Matrix Dimensions out of bound in i:\n");
        fprintf(stderr, "\ti: %d accessed %d\n", m->m, i);
        return -1;
    }else if(j >= m->n) {
        fprintf(stderr, "Matrix Dimensions out of bound in j:\n");
        fprintf(stderr, "\tj: %d accessed %d\n", m->n, j);
        return -1;
    }else {
        // Return value
        return m->data[i][j];
    }
}

int min3(int a, int b, int c){
    // Return the minimum of 3 variables
    return a < b ? (a < c ? a : c) : (b < c ? b : c);
}

// Adapted from the lecture slides from COMP20007
int ldist(char *a, char *b) {
    int n = strlen(a);
    int m = strlen(b);
    mat_t mat = new_matrix(n+1, m+1);
    
    // Fill all the values with 0 first
    for(int i=0; i <= n; i++) {
        for(int j=0; j <= m; j++) {
            wmati(&mat, i, j, 0);
        }
    }

    // Set the the columns to 0

    for(int i=0; i<=n; i++) {
        wmati(&mat, i, 0, i);
    }

    // Set the rows to 0
    for(int j=1; j <=m; j++) {
        wmati(&mat, 0, j, j);
    }
    for(int i=1; i <= n; i++) {
        for(int j=1; j <=m; j++) {
            // Determine if they are not equal,
            // this incurs a cost
            int p = !(a[i-1] == b[j-1]);
            int cost = 1;

            // Write the minium of the three checks
            // to the matrix.
            wmati(&mat, i, j, 
                min3(
                    rmati(&mat, i-1, j-1) + p,
                    rmati(&mat, i-1, j) + cost,
                    rmati(&mat, i, j-1) + cost

                )
            );
        }
    }
    // Get the edit distance
    int dist = rmati(&mat, n, m);
    free_matrix(&mat);    
    return dist;
}