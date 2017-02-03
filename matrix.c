#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

int  input_matrix(matrix **A)
{
	int quantity,row,col;
	printf("Type quantity of input matrix");
	printf("Quantity of matrix : ");
	scanf("%d",&quantity);
	while (quantity < 1)
	{
		printf("Try again. Wrong quantity\n");
		scanf ("%d",&quantity);
	}
	*A = (matrix*)malloc(sizeof(matrix)*quantity);
	for(int k = 0; k < quantity; k++)
	{
		printf("Write dimension of matrix №%d \nRow then Collum\n", k+1);
		scanf ("%d %d",&row, &col);
		while(row < 1 || col < 1)
		{
			printf("Try again. Wrong dimension\n");
			scanf ("%d %d",&row, &col);
		}
		(*A)[k].col = col;
		(*A)[k].row = row;
		(*A)[k].table = (int**)malloc(sizeof(int*) * row);
		for (int i = 0; i < row ;i++ )
		{
			(*A)[k].table[i] = (int *)malloc(sizeof(int) * col);
			for (int j = 0; j < col ;j++ )
			{
				scanf("%d",&((*A)[k].table[i][j]));
			}
		}
	}
	return quantity;
}

void output_matrix(matrix *A)
{
	if(A  == NULL) return;
	int **m = A->table;
	int row = A->row;
	int col = A->col;
	for( int i = 0; i < row;i++)
	{
		printf("\n");
		for(int j = 0 ;j < col; j++)
		{
			printf("%d  ",m[i][j]);
		}
	}
}

void free_matrix(matrix **A,int quantity)
{
	if(quantity == 0) return;
	int row;
	for (int k = 0 ; k < quantity;k++)
	{
		row = (*A)[k].row;
		for (int i = 0; i < row ;i++ )
		{
			free( (*A)[k].table[i] );
		}
		free( (*A)[k].table );

	}
	free(*A);
}

void mul_matrix(matrix *A, matrix *B, matrix **C)
{
	if ( A->col != B->row)
	{
		printf("Can't mul Row != Col. Try something different");
		(*C) = NULL;
		return;
	}
	int **a = A->table;
	int row_a = A->row;
	int col_a = A->col;
	int **b = B->table;
	int row_b = B->row;
	int col_b = B->col;
	*C = (matrix*)malloc(sizeof(matrix));
	(*C)[0].table = (int**)malloc(sizeof(int*)*row_a);
	for (int i = 0; i < row_a;i++)
	{
		(*C)[0].table[i] = (int*)malloc(sizeof(int)*col_b);
		for (int j = 0; j < col_b;j++)
		{
			(*C)[0].table[i][j] = 0;
			for( int k = 0; k < row_b;k++)
			{
				(*C)[0].table[i][j] += a[i][k] * b[k][j];
			}
		}
	}
	(*C)[0].row =row_a;
	(*C)[0].col =col_b;
}
