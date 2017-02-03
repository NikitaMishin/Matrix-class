#pragma once

typedef struct matrix
{
	int **table;
	int col;
	int row;
}matrix;

int input_matrix(matrix **A);
void output_matrix(matrix*A);
void mul_matrix(matrix *A, matrix *B, matrix **C);
void free_matrix (matrix **A,int quantity);
