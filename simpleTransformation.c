#include <stdio.h>
#include "structMatrix.h"
#include "simpleTransformation.h"

//#define CHECKING()
void add_simpleTransformation(matrix *A,int to,int what, int scalar, char orient )//maybe add scalar?
{
  if (orient == 'r')
  {
    for (int i = 0;i< A->col;i++)
      A->table[to][i] += scalar * A->table[what][i];
      return;
  }
  if (orient == 'c')
  {
    for (int i = 0;i< A->row;i++)
      A->table[i][to] += scalar * A->table[i][what];
      return;
  }
  printf("Try again. Wrong orient!");
}

void mul_simpleTransformation(matrix *A,int scalar)
{
  for (int i = 0; i < A->row;i++)
    for (int j = 0 ; j < A->col;j++)
      A->table[i][j] *= scalar;
}

void div_simpleTransformation(matrix *A,int scalar)
{
  for (int i = 0; i < A->row;i++)
    for (int j = 0 ; j < A->col;j++)
      A->table[i][j] /= scalar;
}

void swap_simpleTransformation(matrix *A,int what,int with,char orient)
{
  //CHECKING();
  if (orient == 'r')
  {
    int *tmp  = A->table[what];
    A->table[what] = A->table[with];
    A->table[with] = tmp;
    return;
  }
  if (orient == 'c')
  {
    int tmp;
    for (int i = 0; i < A->row;i++)
    {
      tmp = A->table[i][what];
      A->table[i][what] = A->table[i][with];
      A->table[i][with] = tmp;
    }
    return;
  }
  printf("Try again. Wrong orient!");
}
