#pragma once
#include "structMatrix.h"

int input_matrix(matrix **A);//ok
void output_matrix(matrix*A);//ok
void mul_matrix(matrix *A, matrix *B, matrix **C);//ok
void free_matrix (matrix **A,int quantity);//ok
void sum_matrix(matrix *A, matrix *B, matrix **C);//ok
void sub_matrix(matrix *A, matrix *B, matrix **C);//ok
void power_matrix(matrix *A,matrix **C, int n); //ok
int Gauss_matrix(matrix *A);//ok
int inverse_matrix(matrix *B,matrix **C);//ok
int get_rank_matrix(matrix A);//ok

void Strassen_mul_matrix(matrix *A, matrix *B, matrix **C);
void square_mul_matrix(matrix *A, matrix *B, matrix **C);//recurs
int abs_compare(double a,double b);
