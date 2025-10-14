#include "matrix_algebra.h"
#include <stdlib.h>

//define a struct to represent an n by m matrix. 
// the entries of this matrix should be doubles.
struct matrix 
{
   int n;
   int m;
   double **array;
};


mat* create_matrix(int n, int m)
{
	//Fill this function to return an n x m matrix of zeros.
	//The matrix should be allocated on the heap (that is, you return a mat* pointer)
	mat* matrix = malloc(sizeof(mat));
	if (!matrix) return NULL;
	
	matrix->n = n;
	matrix->m = m;

	matrix->array = malloc(n * sizeof(double*));
	if (!matrix->array) {
		free(matrix);
		return NULL;
	}
	
	for(int i = 0; i < n; i++) {
		matrix->array[i] = calloc(m, sizeof(double));
		if (!matrix->array[i]) {
            for (int j = 0; j < i; j++)
                free(matrix->array[j]);
            free(matrix->array);
            free(matrix);
            return NULL;
        }
	}
	return matrix;
}

mat* matrix_read(char* filename)
{
	//given a filename, read the next matrix stored in that file.
	// remember, matrices are stored in binary files in the following format:
	// int n, int m, nxm doubles, where n is the num of rows, m the num of columns and the following doubles are the n rows of m elements in the matrix.
	// if reading the matrix fails for whatever reason, you should return NULL.
	FILE* file = fopen(filename, "rb");
	if (file == NULL)
	{
		return NULL;
	}
	int n;
	int m; 

	if (fread(&n, sizeof(int), 1, file) != 1 || fread(&m, sizeof(int), 1, file) != 1)
	{
		fclose(file);
		return NULL;
	}
	mat* matrix = create_matrix(n, m);
	if (!matrix) {
		fclose(file);
		return NULL;
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (fread(&matrix->array[i][j], sizeof(double), 1, file) != 1)
			{
				matrix_free(matrix);
				fclose(file);
				return NULL;
			}
		}
	}
	fclose(file);
	return (matrix);
}

mat* matrix_multiply(mat* A, mat*B)
{
	//fill this function to return a new matrix AB, the product of A and B. Return NULL if the product does not exist.
	if (A->m != B->n) {
		return NULL;
	}
	double sum;
	mat* matrix_AB = create_matrix(A->n, B->m);
	if (!matrix_AB) return NULL;

	for (int i = 0; i < A->n; i++) {
		for (int j = 0; j < B->m; j++) {
			sum = 0.0;
			for(int cntr = 0; cntr < A->m; cntr++)
			{
				sum += A->array[i][cntr] * B->array[cntr][j];
			}
			matrix_AB->array[i][j] = sum;
		}
	}
	return matrix_AB;
}

mat* matrix_add(mat* A, mat* B)
{
	//fill this function to return the matrix A+B, the addition of A and B. Return NULL if the addition does not exist.
	if (A->m != B->m || A->n != B->n) {
		return NULL;
	}
	mat* matrix_sum = create_matrix(A->n, A->m);
	if(!matrix_sum) return NULL;

	for (int i = 0; i < A->n; i++) {
		for (int j = 0; j < B->m; j++) {
			matrix_sum->array[i][j] = A->array[i][j] + B->array[i][j];
		}
	}
	return matrix_sum;
}

void matrix_free(mat* A)
{
	//fill in this funciton to free the matrix A.
	if (!A) return;
	for (int i = 0; i < A->n; i++)
	{
		free(A->array[i]);
	}
	free(A->array);
	free(A);
}

int matrix_write(char* filename, mat* A)
{
	// write A to the binary file filename. If this fails for whatever reason, return 0.
	FILE *file = fopen(filename, "wb");
	if (file == NULL) {
		return 0;
	}
	
	if (fwrite(&A->n, sizeof(int), 1, file) != 1 ||
        fwrite(&A->m, sizeof(int), 1, file) != 1) {
        fclose(file);
        return 0;
    }

    for (int i = 0; i < A->n; i++) {
		if (!A->array[i]) {
			fclose(file);
			return 0;
		}
        if (fwrite(A->array[i], sizeof(double), A->m, file) != (size_t)A->m) {
            fclose(file);
            return 0;
        }
    }	
	
	fclose(file);
	return 1;
}

// fill this function to modify A into cA, that is, to multiply each entry of A by c.
mat* matrix_scale(double c, mat* A)
{
	
	mat* matrix_cA = create_matrix(A->n, A->m);
    if (!matrix_cA) return NULL;

	
	for (int i = 0; i < A->n; i++) {
		for (int j = 0; j < A->m; j++) {
			matrix_cA->array[i][j] = c * A->array[i][j];
		}
	}
	return matrix_cA;
}

