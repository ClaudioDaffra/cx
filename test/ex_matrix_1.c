#include <stdlib.h>
#include <stdio.h>
#include "../lib/matrix.h"
#include "../lib/gc.h"


/*

    cl  test\ex_matrix_1.c  lib\matrix.c lib\gc.c  lib\fs.c /EHsc    /Fex.exe
    gcc test\ex_matrix_1.c  lib\matrix.c lib\gc.c  lib\fs.c         -o x.exe
    gcc test/ex_matrix_1.c  lib/matrix.c lib/gc.c  lib/fs.c -lm     -o x

*/


int main(int argc, char **argv)
{
    gcStart();
/*
    // ----------------------------------

    // [OK] matrixRand, matrixPrint 

	Matrix *m;
	m = matrixRand(4, 4, 10);
	matrixPrint(m);
*/  

/*	 
    // [OK] TEST MANUAL ENTRY

	Matrix *m;
	matrixScanf(&m);
	matrixPrint(m); 
*/  
    
 
    // [OK] TEST EIGENVALUES

	Matrix *m;
	double *arr;
	unsigned int i;
	m = matrixRand(2, 2, 3);
	//matrixPrint(m);
	arr = matrixEigenValues(m);
    printf("\n");
	for(i = 0; i < 2; i++)
		printf("%f\n", arr[i]);
 
    
/*           
    // [OK] matrixOrthoNormalBasis

    Matrix *m;

    m=matrixRand(5, 5, 5);
    matrixPrint(m);        
    m=matrixOrthoNormalBasis(m);
    matrixPrint(m);
*/          
/*    
    // [OK] matrixSolvedAugMatrix

    Matrix *m1, *m2;
    m1 = matrixRand(3, 5, 5);
    matrixPrint(m1);
    printf("==\n");
    m2 = matrixSolvedAugMatrix(m1);
    matrixPrint(m2);
*/     
     
    //  [OK] TEST ORTHONORMAL BASIS
/*    
	Matrix *m, *o;
	m = matrixRand(3, 3, 3);
	matrixPrint(m);
	printf("==\n");
	o = matrixOrthoNormalBasis(m);
	matrixPrint(o);
*/

/* 
	// [OK] TEST DETERMINANT

	Matrix *m;
	m = matrixRand(2, 2 ,3);
	matrixPrint(m);
	printf("%f\n", matrixDeterminant(m));
*/ 

/*    
	// [OK] TEST INVERSION
    
	Matrix *m1, *m2, *m3;
	//matrixScanf(&m1);
    m1 = matrixRand(3, 3, 3);
	matrixPrint(m1);
	printf("==\n");
	m2 = matrixClone(m1);
	m2 = matrixInversion(m2);
	matrixPrint(m2);
	printf("==\n");
	m3 = matrixMultiply(m1, m2);
	matrixPrint(m3); 
*/
 
/*    
	// [OK] TEST CLONING AND EQUATING

	Matrix *m1, *m2;
	m1 = matrixRand(5, 5, 10);
	matrixPrint(m1);
	printf("==\n");
	m2 = matrixClone(m1);
	matrixPrint(m2);
	if(matrixEquals(m1, m2) == 1)
		printf("They are equal\n");
*/ 
    
/*   
	// [OK] TEST FOR ZERO CHECK

	Matrix *m;
	m = matrixRand(3, 3, 2);
	matrixPrint(m);
	if(matrixZeroVector(m) == 1)
		printf("yeah\n");
*/
/*       
    // [OK] TEST Scalar Multiplication of row

    Matrix *m;
    m = matrixRand(4, 4, 4);
    matrixPrint(m);
    printf("==\n");
    matrixRowScalarMultiply(m, 2, 2);
    matrixPrint(m);
 */      
/*    
	// [OK] TEST ROW REDUCING
    
	Matrix *m;
	m = matrixRand(3, 2, 4);
	matrixPrint(m);
	printf("===\n");
	matrixReduce(m, 0, 2, 4);
	matrixPrint(m);
*/
/*	 
	// [OK] TEST SCALAR MULTIPLICATION ON MATRIX

	Matrix *m;
	m = matrixRand(3, 3, 3);
	matrixPrint(m);
	printf("==\n");
	matrixScalarMultiply(m, 3);
	matrixPrint(m);
*/
/* 
	// [OK] TEST ROW SWAP

	Matrix *m;
	m = matrixRand(3, 3, 3);
	matrixPrint(m);
	printf("==\n");
	matrixRowSwap(m, 1, 2);
	matrixPrint(m);
*/
/* 
	// [OK] TEST MULTIPLY

	Matrix *m1, *m2, *m3;
	m1 = matrixRand(2, 3, 3);
	matrixPrint(m1);
	m2 = matrixRand(3, 1, 3);
	matrixPrint(m2);
	m3 = matrixMultiply(m1, m2);
	matrixPrint(m3);
*/
/* 
	// [OK] TEST GRAN-SCHMIDT	

	Matrix *m, *d;
	m = matrixRand(3, 3, 4);
	matrixPrint(m);
	printf("==\n");
	d = matrixGramSchmidt(m);
	matrixPrint(d);
*/
/* 
	// [OK] TEST PROJECTION

	Matrix *m1, *v;
	double *project;
	unsigned int i;
	m1 = matrixRand(3, 2, 3);
	matrixPrint(m1);
	v = matrixRand(3, 1, 3);
	printf("==\n");
	matrixPrint(v);
	printf("==\n");
	project = matrixProjection(m1, v->numbers[0], 3);
	for(i = 0; i < 3; i++)
		printf("%f\n", project[i]);
*/
/* 
	// [OK] TEST ADDITION/SUBTRACTION

	Matrix *m1, *m2;
	m1 = matrixRand(3, 3, 3);
	m2 = matrixRand(3, 3, 3);
	matrixPrint(m1);
	printf("==\n");
	matrixPrint(m2);
	printf("==\n");
	matrixAdd(m1, m2);
	matrixPrint(m1);
	printf("==\n");
	matrixSub(m2, m1);
	matrixPrint(m2);
*/
/*	 
	// [OK] TEST TRANSPOSE

	Matrix *m, *m2;
	m = matrixRand(2, 4, 5);
	matrixPrint(m);
	m2 = matrixTranspose(m);
	matrixPrint(m2);
*/
/* 
	// [OK] TEST RANDOM MATRIX GENERATOR

	Matrix *m;
	m = matrixRand(2, 3, 5);
	matrixPrint(m);
*/
/*
	// [OK] TEST CONSTRUCTOR && matrixPrint

	Matrix *m;
	m = matrixConstructor(2, 3); 
	matrixPrint(m);
*/
/* 
	// [OK] TEST IDENTITY

	Matrix *m;
	m = matrixIdentity(3);
	matrixPrint(m);
*/
/*	 
	// [OK] TEST GRAM-SCHMIDT

	Matrix *m;
	m = matrixRand(2, 3, 5);
	matrixPrint(m);
	printf("==\n");
	matrixGramSchmidt(m);
	matrixPrint(m);
*/
/* 
	// [OK] TEST Projection

	Matrix *m;
	double *array, *a1;
	unsigned int i;
	m = matrixRand(3, 2, 3);
	matrixPrint(m);
	printf("==\n");
	array = malloc(sizeof(double)*3);
	for(i = 0; i < 3; i++)
		printf("%f\n", array[i] = i);
	printf("==\n");
	a1 = matrixProjection(m, array, 3);
	for(i = 0; i < 3; i++)
		printf("%f\n", a1[i]);
 
    matrixDestroy(m);
*/ 
 
    // ----------------------------------

    gcStop() ;   

	return 0;
}

/*

    claudio@ubuntu:~/matrix$ valgrind --leak-check=full ./x
    ==39099== Memcheck, a memory error detector
    ==39099== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
    ==39099== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
    ==39099== Command: ./x
    ==39099== 

    1.000000
    1.000000
    ==39099== 
    ==39099== HEAP SUMMARY:
    ==39099==     in use at exit: 0 bytes in 0 blocks
    ==39099==   total heap usage: 19 allocs, 19 frees, 1,384 bytes allocated
    ==39099== 
    ==39099== All heap blocks were freed -- no leaks are possible
    ==39099== 
    ==39099== For counts of detected and suppressed errors, rerun with: -v
    ==39099== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
    claudio@ubuntu:~/matrix$

*/


