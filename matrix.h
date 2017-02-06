#pragma once
#include "structMatrix.h"

int input_matrix(matrix **A);//ok
void output_matrix(matrix*A);//ok
void mul_matrix(matrix *A, matrix *B, matrix **C);//ok
void free_matrix (matrix **A,int quantity);//ok
void sum_matrix(matrix *A, matrix *B, matrix **C);//ok
void sub_matrix(matrix *A, matrix *B, matrix **C);//ok
void power_matrix(matrix *A,matrix **C, int n); //ok

void Gauss_matrix(matrix *A);
void inverse_matrix(matrix *A,matrix **C);//gause plus smth
int get_rank_matrix(matrix *A);//use Gauss_matrix

void Strassen_mul_matrix(matrix *A, matrix *B, matrix **C);
void square_mul_matrix(matrix *A, matrix *B, matrix **C);//recurs
//another block det.h
int det_matrix(matrix *A);// use Gauss_matrix but remembr about div or recurs
//two ways add also transpomirovanie
//minor  alg dop
