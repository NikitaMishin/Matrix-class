#pragma once

typedef struct matrix
{
	int **table;
	int col;
	int row;
}matrix;

int input_matrix(matrix **A);//ok
void output_matrix(matrix*A);//ok
void mul_matrix(matrix *A, matrix *B, matrix **C);//ok
void free_matrix (matrix **A,int quantity);//ok
void sum_matrix(matrix *A, matrix *B, matrix **C);//ok
void sub_matrix(matrix *A, matrix *B, matrix **C);//ok
void power_matrix(matrix *A,matrix **C, int n); //ok
void Strassen_mul_matrix(matrix *A, matrix *B, matrix **C);
void power_matrix(matrix *A,matrix **C, int n);
void square_mul_matrix(matrix *A, matrix *B, matrix **C);//recurs
int det_matrix(matrix *A);//two ways add also transpomirovanie
void Gauss_matrix(matrix *A);

void inverse_matrix(matrix *A,matrix **C);
