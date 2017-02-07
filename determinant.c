#include <stdio.h>
#include <stdlib.h>
#include "determinant.h"
#include <math.h>
#include "simpleTransformation.h"
#include "matrix.h"
#define EPS 0.0000001

double det_Gauss_determinant(matrix *B)
{
    double det = 1;
  	int col = B->col;
  	int row = B->row;
  	if(row != col)
  	{
  		printf("Sorry.Determinant  didn't exist!");
  		return 0.3;
  	}
    matrix *A = (matrix*)malloc(sizeof(matrix));
    A->row = row;
    A->col = col;
    A->table = (double**)malloc(sizeof(double*) * row);
  	double **a = A->table;
    for (int i = 0; i < row;i++)//copy
    {
      a[i] = (double*)malloc(sizeof(double) * row);
      for (int j = 0; j < row;j++)
        a[i][j] = B->table[i][j];
    }

  	int current_row = 0;
  	int current_col = 0;
  	int different = 0;
  	int i;
  	int n = (col < row)? col:row;
  	double bearing;
  	int pos;
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
        det = det*(-1);
  		}
  		for (int j = 0;j < col; j++)
  			a[current_row][j] /= bearing;
      det *= bearing;
  		for (int j = current_row + 1; j < row ;j++)
  		  add_simpleTransformation(A,j,current_row,-a[j][current_col],'r');
  		current_row++;
  	}
  	if (fabs(bearing) < EPS)
  	{
  		free_matrix(&A, 1);
  		return 0;
  	}
    free_matrix(&A, 1);
  	return det;
}


double RecursDet(double **a,int i,int j, int n)
{
  double det = 0;
  double **new =(double**)malloc(sizeof(double*)*n) ;
  for (int k = 0,t = 0;k < n;k++)
  {
    if (k == i) t = 1;
    new[k] = a[k+t];
  }
  int sgn = (((i + j) % 2) == 0)?1:-1;
  if (n == 2)
  {
    det = sgn * (new[0][0]*new[1][1] - new[1][0]*new[0][1]);
    free(new);
    return (det);
  }
  for (int k = 0; k < n; k++)
    det += new[k][n-1] * RecursDet(new,k,n-1,n-1);
  free(new);
  return sgn * det;
}

double det_Recursively_determinant(matrix *A)
{
  if(A->row != A->col)
  {
    printf("Determinant for this matrix didn't exist!");
    return 0.3 ;//nah
  }
  double det = 0;
  double **new = A->table;
  int n = A->row;
  if (n == 1) return new[0][0];
  for (int i = 0;i < n;i++)
   det += new[i][n-1] * RecursDet(new, i,n-1,n-1);
  return det;
}
