#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "simpleTransformation.h"
#include <math.h>

#define EPS 0.0000001

int abs_compare(double a,double b)
{
	int flag = 0;
	if (a >= 0)
	{
		if (b < 0) { flag = (a > -b)?1:0;}
		else flag = (a > b)?1:0;
	}
	else
	{
		if (b < 0){ flag = (a < b)?1:0;}
		else  flag = (-a > b)?1:0;
	}
	return flag;
}

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
		(*A)[k].table = (double**)malloc(sizeof(double*) * row);
		for (int i = 0; i < row ;i++ )
		{
			(*A)[k].table[i] = (double *)malloc(sizeof(double) * col);
			for (int j = 0; j < col ;j++ )
			{
				scanf("%lf",&((*A)[k].table[i][j]));
			}
		}
	}
	return quantity;
}

void output_matrix(matrix *A)
{
	if(A  == NULL) return;
	double **m = A->table;
	int row = A->row;
	int col = A->col;
	for( int i = 0; i < row;i++)
	{
		printf("\n");
		for(int j = 0 ;j < col; j++)
		{
			printf("%10.6lf  ",m[i][j]);
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
	double **a = A->table;
	int row_a = A->row;
	int col_a = A->col;
	double **b = B->table;
	int row_b = B->row;
	int col_b = B->col;
	*C = (matrix*)malloc(sizeof(matrix));
	(*C)[0].table = (double**)malloc(sizeof(double*)*row_a);
	for (int i = 0; i < row_a;i++)
	{
		(*C)[0].table[i] = (double*)malloc(sizeof(double)*col_b);
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

void sum_matrix(matrix *A, matrix *B, matrix **C)
{
	if( (A->row != B->row) || (A->col != B->col) )
	{
		printf("Sorry, Can't sum these matrix.Wrong size. Try another matrix\n");
		return;
	}
	int row_a = A->row;
	int col_a = A->col;
	*C = (matrix*)malloc(sizeof(matrix));
	(*C)[0].table = (double**)malloc(sizeof(double*)*row_a);
	for (int i = 0; i < row_a;i++)
	{
		(*C)[0].table[i] = (double*)malloc(sizeof(double)*col_a);
		for (int j = 0; j < col_a;j++)
		{
			(*C)[0].table[i][j] = A->table[i][j] + B->table[i][j];
		}
	}
	(*C)[0].row =row_a;
	(*C)[0].col =col_a;
}

void sub_matrix(matrix *A, matrix *B, matrix **C)
{
	if( (A->row != B->row) || (A->col != B->col) )
	{
		printf("Sorry, Can't sub these matrix.Wrong size. Try another matrix\n");
		return;
	}
	int row_a = A->row;
	int col_a = A->col;
	*C = (matrix*)malloc(sizeof(matrix));
	(*C)[0].table = (double**)malloc(sizeof(double*)*row_a);
	for (int i = 0; i < row_a;i++)
	{
		(*C)[0].table[i] = (double*)malloc(sizeof(double)*col_a);
		for (int j = 0; j < col_a;j++)
		{
			(*C)[0].table[i][j] = A->table[i][j] - B->table[i][j];
		}
	}
	(*C)[0].row =row_a;
	(*C)[0].col =col_a;
}

void power_matrix(matrix *A,matrix **C, int n)
{
	if( A->row != A->col)
	{
		printf("Sorry, Can't power this matrix.Wrong size(col!=row).Try another matrix\n");
		return;
	}
	matrix *Tmp;
	double **a;
	if (n < 0)
	{
		if (inverse_matrix(A,&Tmp) == -1) return;
		n  = -n;
		a = Tmp->table;
	}
	else  a = A->table;;
	double **subN;
	double **N;
	double **tmp;
	int flag = (n%2);
	int row = A->row;
	*C = (matrix*)malloc(sizeof(matrix));
	(*C)[0].row = row;
	(*C)[0].col = row;
	(*C)[0].table = (double**)malloc(sizeof(double*) * row);
	N = (*C)[0].table;
	subN = (double**)malloc(sizeof(double*) * row);
	if (n == 0)
	{
		for (int i = 0 ;i < row;i++)
		{
			N[i] = (double*)calloc(row,sizeof(double));
			N[i][i] = 1;
		}
		free(subN);
		return;
	}
	for (int i = 0; i < row;i++)
	{
		N[i] = (double*)malloc(sizeof(double)*row);//
		subN[i] = (double*)malloc(sizeof(double)*row);
		for(int j = 0; j < row; j++)
		{
			subN[i][j] = a[i][j];
		}
	}
	while(--n)
	{
		for (int i = 0; i < row;i++)
		{
			for (int j = 0; j < row;j++)
			{
				N[i][j] = 0;
				for( int k = 0; k < row;k++)
				{
					N[i][j] += a[i][k] * subN[k][j];
				}
			}
		}
		tmp = N;
		N = subN;
		subN = tmp;
	}
	if (flag) (*C)[0].table = subN;
	for (int i = 0; i < row;i++)
	{
		free(N[i]);
	}
	free(N);
	free_matrix(&Tmp,1);
}

int Gauss_matrix(matrix *A)
{
	int col = A->col;
	int row = A->row;
	double **a = A->table;
	int current_row = 0;
	int current_col = 0;
	int i;
	int n = (col < row)? col:row;
	double bearing;
	int pos;
	for (current_col = 0 ; current_col < n; current_col++) //step in other words it's  a col
	{
		bearing = 0;
		pos = current_row;
		//find bearing element
		i = current_row;
		for (i = current_row;i < row;i++)//by bite do it
		{
			if (abs_compare(a[i][current_col],bearing) )
			{
				bearing = a[i][current_col];
				pos = i;
			}
		}
		if (fabs(bearing) > EPS  )
		{
			if (current_row != pos) swap_simpleTransformation(A,pos,current_row,'r');
			for (int j = 0;j < col; j++) a[current_row][j] /= bearing;
			for (int j = current_row + 1; j < row ;j++)
				add_simpleTransformation(A,j,current_row,-a[j][current_col],'r');
			current_row++;
		}
	}
	return current_row;
}

int get_rank_matrix(matrix A)
{
	return Gauss_matrix(&A);
}

int inverse_matrix(matrix *B,matrix**C)
{//copy matrix
	int col = B->col;
	int row = B->row;
	if(row != col)
	{
		printf("Sorry.The inverse_matrix didn't exist!");
		return -1;
	}
	matrix *A = (matrix*)malloc(sizeof(matrix));
	double **a ;//= A->table;
	int current_row = 0;
	int current_col = 0;
	int different = 0;
	int i;
	int n = (col < row)? col:row;
	double bearing;
	int pos;
	(*C) = (matrix*)malloc(sizeof(matrix));
	(*C)[0].table = (double**)malloc(sizeof(double*)*row);
	(*C)[0].row = n;
	(*C)[0].col = n;
	A->table = (double**)malloc(sizeof(double*)*row);
	A->row = n;
	A->col = n;
	for(int k = 0; k < n; k++ )
	{
		(*C)[0].table[k] = (double*)calloc(row, sizeof(double));
		A->table[k] = (double*)calloc(row, sizeof(double));
		for (int j = 0 ;j < n;j++) A->table[k][j] = B->table[k][j];
		(*C)[0].table[k][k] = 1;
	}
	a = A->table;
	matrix *N = &(*C)[0];
	for (current_col = 0 ; current_col < n; current_col++) //step in other words it's  a col
	{
		bearing = 0;
		pos = current_row;
		i = current_row;
		for (i = current_row;i < row;i++)//by bite do it
		{
			if (abs_compare(a[i][current_col],bearing) )
			{
				bearing = a[i][current_col];
				pos = i;
			}
		}
		if (fabs(bearing) < EPS ) break;
		if (current_row != pos)
		{
			swap_simpleTransformation(A,pos,current_row,'r');
			swap_simpleTransformation(N,pos,current_row,'r');
		}
		for (int j = 0;j < col; j++)
		{
			a[current_row][j] /= bearing;
			N->table[current_row][j] /= bearing;
		}
		for (int j = current_row + 1; j < row ;j++)
			{
				add_simpleTransformation(N,j,current_row,-a[j][current_col],'r');
				add_simpleTransformation(A,j,current_row,-a[j][current_col],'r');
			}
		current_row++;
	}
	if (fabs(bearing) < EPS)
	{
		printf("Sorry.The inverse_matrix didn't exist!");
		free_matrix(C, 1);
		free_matrix(&A, 1);
		return -1;
	}
	for (int k = row-1;k > 0;k--)
	{
		for (int t = 0; t < k;t++)
			{
				add_simpleTransformation(N,t,k,-a[t][k],'r');
				add_simpleTransformation(A,t,k,-a[t][k],'r');//ok
			}
	}
	free_matrix(&A, 1);
	return 1;
}
