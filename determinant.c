#include <stdio.h>
#include <stdlib.h>
#include "determinant.h"

double det_Gauss_determinant(matrix *A);


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
    printf("Determinant for thin matrix didn't exist!");
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
