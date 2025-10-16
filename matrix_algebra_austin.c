#include "matrix_algebra.h"
#include <stdlib.h>
//define a struct to represent an n by m matrix. 
// the entries of this matrix should be doubles.
struct matrix 
{

	int n; 
	int m; 
	double** entries;

};


mat* create_matrix(int n, int m)
{
	//Fill this function to return an n x m matrix of zeros.
	//The matrix should be allocated on the heap (that is, you return a mat* pointer)
	if (n <= 0 || m <= 0) return NULL;

	mat* A = malloc(sizeof(mat));
	if (A == NULL) return NULL;
	A->n = n;
	A->m = m;
	A->entries = malloc(n * sizeof(double*));
	if (A->entries == NULL) { free(A); return NULL; }
	for (int i = 0; i < n; i++) {
		A->entries[i] = malloc(m * sizeof(double));
		if (A->entries[i] == NULL) {
			
			for (int r = 0; r < i; r++) free(A->entries[r]);
			free(A->entries);
			free(A);
			return NULL;
		}
		for (int j = 0; j < m; j++) {
			A->entries[i][j] = 0.0;
		}
	}
	return A;
}

mat* matrix_read(char* filename)
{
	//given a filename, read the next matrix stored in that file.
	// remember, matrices are stored in binary files in the following format:
	// int n, int m, nxm doubles, where n is the num of rows, m the num of columns and the following doubles are the n rows of m elements in the matrix.
	// if reading the matrix fails for whatever reason, you should return NULL.
	if (filename == NULL) return NULL;

	FILE* file = fopen(filename, "rb");
	if (file == NULL) {
		return NULL;
	}

	int n, m;
	if (fread(&n, sizeof(int), 1, file) != 1) { fclose(file); return NULL; }
	if (fread(&m, sizeof(int), 1, file) != 1) { fclose(file); return NULL; }
	if (n <= 0 || m <= 0) { fclose(file); return NULL; }

	mat* A = create_matrix(n, m);
	if (A == NULL) { fclose(file); return NULL; }

	for (int i = 0; i < n; i++) {
		size_t read = fread(A->entries[i], sizeof(double), m, file);
		if (read != (size_t)m) {
			
			matrix_free(A);
			fclose(file);
			return NULL;
		}
	}

	fclose(file);
	return A;
}

mat* matrix_multiply(mat* A, mat*B)
{
	//fill this function to return a new matrix AB, the product of A and B. Return NULL if the product does not exist.
	if (A == NULL || B == NULL) return NULL;
	if (A->m != B->n) {
		return NULL;
	}
	mat* C = create_matrix(A->n, B->m);
	if (C == NULL) return NULL;
	for (int i = 0; i < A->n; i++) {
		for (int j = 0; j < B->m; j++) {
			double sum = 0.0;
			for (int k = 0; k < A->m; k++) {
				sum += A->entries[i][k] * B->entries[k][j];
			}
			C->entries[i][j] = sum;
		}
	}
	return C;
}

mat* matrix_add(mat* A, mat* B)
{
	//fill this function to return the matrix A+B, the addition of A and B. Return NULL if the addition does not exist.
	if (A == NULL || B == NULL) return NULL;
	if (A->n != B->n || A->m != B->m) {
		return NULL;
	}
	mat* C = create_matrix(A->n, A->m);
	if (C == NULL) return NULL;
	for (int i = 0; i < A->n; i++) {
		for (int j = 0; j < A->m; j++) {
			C->entries[i][j] = A->entries[i][j] + B->entries[i][j];
		}
	}
	return C;
}

void matrix_free(mat* A)
{
	//fill in this funciton to free the matrix A.
	if (A == NULL) return;
	if (A->entries != NULL) {
		for (int i = 0; i < A->n; i++) {
			if (A->entries[i] != NULL) free(A->entries[i]);
		}
		free(A->entries);
	}
	free(A);
}

int matrix_write(char* filename, mat* A)
{
	// write A to the binary file filename. If this fails for whatever reason, return 0.
	if (filename == NULL || A == NULL) return 0;

	FILE* file = fopen(filename, "wb");
	if (file == NULL) {
		return 0;
	}

	if (fwrite(&A->n, sizeof(int), 1, file) != 1) { fclose(file); return 0; }
	if (fwrite(&A->m, sizeof(int), 1, file) != 1) { fclose(file); return 0; }

	for (int i = 0; i < A->n; i++) {
		if (fwrite(A->entries[i], sizeof(double), A->m, file) != (size_t)A->m) { fclose(file); return 0; }
	}

	fclose(file);
	return 1;
}

// fill this function to modify A into cA, that is, to multiply each entry of A by c.
mat* matrix_scale(double c, mat* A)
{
	if (A == NULL) return NULL;
	mat* B = create_matrix(A->n, A->m);
	if (B == NULL) return NULL;
	for (int i = 0; i < A->n; i++) {
		for (int j = 0; j < A->m; j++) {
			B->entries[i][j] = A->entries[i][j] * c;
		}
	}
	return B;
}
