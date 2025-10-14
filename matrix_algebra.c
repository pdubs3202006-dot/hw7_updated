#include "matrix_algebra.h"

//define a struct to represent an n by m matrix. 
// the entries of this matrix should be doubles.
struct matrix 
{

};


mat* create_matrix(int n, int m)
{
	//Fill this function to return an n x m matrix of zeros.
	//The matrix should be allocated on the heap (that is, you return a mat* pointer)
}

mat* matrix_read(char* filename)
{
	//given a filename, read the next matrix stored in that file.
	// remember, matrices are stored in binary files in the following format:
	// int n, int m, nxm doubles, where n is the num of rows, m the num of columns and the following doubles are the n rows of m elements in the matrix.
	// if reading the matrix fails for whatever reason, you should return NULL.

}

mat* matrix_multiply(mat* A, mat*B)
{
	//fill this function to return a new matrix AB, the product of A and B. Return NULL if the product does not exist.
}

mat* matrix_add(mat* A, mat* B)
{
	//fill this function to return the matrix A+B, the addition of A and B. Return NULL if the addition does not exist.
}

void matrix_free(mat* A)
{
	//fill in this funciton to free the matrix A.
}

int matrix_write(char* filename, mat* A)
{
	// write A to the binary file filename. If this fails for whatever reason, return 0.
}

// fill this function to modify A into cA, that is, to multiply each entry of A by c.
mat* matrix_scale(double c, mat* A)
{
	
}





