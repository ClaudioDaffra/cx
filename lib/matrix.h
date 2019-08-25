#ifndef matrix_h
#define matrix_h

#ifdef __linux__
#define _GNU_SOURCE 
#endif

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "gc.h"

#define matrixSucc 1
#define matrixFail -1

/* current representation of a matrix in my mind  */

typedef struct Matrix
{
	int rows;
	int columns;
	double **numbers;
} Matrix;

Matrix *    matrixIdentity              (int length);
Matrix *    matrixInversion             (Matrix *m);
Matrix *    matrixConstructor           (int r, int c);
int         matrixDestroy               (Matrix *m);
int         matrixPrint                 (Matrix *m);
int         matrixRowSwap               (Matrix *m, int a, int b);
int         matrixScalarMultiply        (Matrix *m, float f);
int         matrixReduce                (Matrix *m, int a, int b, float factor);
int         matrixEquals                (Matrix *m1, Matrix *m2);
Matrix *    matrixClone                 (Matrix *m);
Matrix *    matrixTranspose             (Matrix *m);
Matrix *    matrixRand                  (int rows, int columns, int modulo);
Matrix *    matrixMultiply              (Matrix *m1, Matrix *m2);
int         matrixAdd                   (Matrix *m1, Matrix *m2);
int         matrixSub                   (Matrix *, Matrix *);
Matrix *    matrixGramSchmidt           (Matrix *);
double *    matrixProjection            (Matrix *, double *, int length);
int         matrixZeroVector            (Matrix *);
Matrix *    matrixOrthoNormalBasis      (Matrix *);
double      matrixDeterminant           (Matrix *m);
Matrix *    matrixSolvedAugMatrix       (Matrix *);
void        matrixScanf                 (Matrix **m);
double *    matrixEigenValues           (Matrix *m);
int         matrixRowScalarMultiply     (Matrix *m, int row, float factor);

 
#endif /* matrix */



/**/




