#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

/*  @requires numbers of rows and columns of the matrix
    @assigns nothing
    @ensures returns the matrix */
Matrix create_matrix(int row, int col) {
    // initialize a res matrix with the right number of rows and columns :
    Matrix res;
    res.row = row;
    res.column = col;
    // allocate the memory for each row :
    res.tab = calloc(row, sizeof(int*));
    // check if the memory was correctly allocated :
    if (res.tab == NULL) {
        printf("Memory allocation error.\n");
        exit(1);
    }
    int i; // for loop variable
    for (i = 0; i < row; i += 1) {
        // allocate the memory for each column :
        res.tab[i] = calloc(col, sizeof(int));
        // check if the memory was correctly allocated :
        if (res.tab == NULL) {
            printf("Memory allocation error.\n");
            exit(2);
        }
    }
    return res;
}

/*  @requires M is a valid matrix
    @assigns nothing
    @ensures prints the matrix M */
void print_matrix(Matrix M) {
    int i, j; // for loop variables
    for (i = 0; i < M.row; i += 1) {
        for (j = 0; j < M.column; j += 1) {
            // print each cell of the matrix :
            printf("%i ", M.tab[i][j]);
        }
        printf("\n");
    }
}

/*  @requires M is a valid matrix
    @assigns free the memory allocated during the creating of the matrix M
    @ensures nothing */
void free_matrix(Matrix M) {
    int i; // for loop variable
    for (i = 0; i < M.row; i += 1) {
        // free each row of the matrix :
        free(M.tab[i]);
    }
    // free all the matrix :
    free(M.tab);
}
