#ifndef MATRIX_H
#define MATRIX_H

/* implementation of matrix using two dimension array with a specific size */
struct matrix {
    int row;
    int column;
    int **tab;
};
typedef struct matrix Matrix;

/*  @requires number of rows and columns
    @assigns nothing
    @ensures returns a matrix with the right number of row and column */
Matrix create_matrix(int row, int column);

/*  @requires M is a valid matrix
    @assigns nothing
    @ensures prints the matrix M */
void print_matrix(Matrix);

/*  @requires M is a valid matrix
    @assigns free the memory allocated by the creation of a the matrix M
    @ensures nothing */
void free_matrix(Matrix);

#endif
