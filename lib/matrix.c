
#include "matrix.h"

/*

    * a matrix is  :

		    columns
	    pointer   .   .   .   .
    rows	  |	
	      |
	      V
	      .
	      .
	      .

    the matrix is an array of array pointers 
    where each array pointer corresponds to a vector

*/

static double   vector_multiply                 (double *col    , double *row   , int length);
static void     vector_addition                 (double *v1     , double *v2    , int length);
static void     scalar_vector_multiplication    (double factor  , double *vector, int length);
static void     vector_subtraction              (double *v1     , double *v2    , int length);

/* return success if there is at least one zero vector in the matrix */
int matrixZeroVector(Matrix *m)
{
	unsigned int i, j, counter;
	if(m == NULL)
		return matrixFail;
	for(i = 0; i < m->columns; i++){
		counter = 0;	
		for(j = 0; j < m->rows; j++){
			if(m->numbers[i][j] == 0)
				counter++;
		}
		if(counter == 3)
			return matrixSucc;
	}
	return matrixFail;
}

/* make a zero matrix of given dimensions */
Matrix *matrixConstructor(int r, int c)
{
	unsigned int i;
	Matrix *m;
	if(r <= 0 || c <= 0){
		perror("Give me positive values for dimensions genius");
		return NULL;
	}
	m = gcMalloc(sizeof(Matrix));
	m->rows = r;
	m->columns = c;
	m->numbers = gcMalloc(sizeof(double *)*c);
	for(i = 0; i < c; i++)
		m->numbers[i] = gcMalloc(sizeof(double)*r);
	return m;
}

/* enter 1s along the main diagonal */
Matrix *matrixIdentity(int length)
{
	unsigned int i, j;
	Matrix *m;
	m = matrixConstructor(length, length);
	for(i = 0; i < length; i++){
		j = i;
		(m->numbers[i])[j] = 1;
	}
	return m;
}

/* gcFree memory associated with the matrix  */
int matrixDestroy(Matrix *m)
{
	unsigned int i;
	if(m == NULL)
		return matrixFail;
	for(i = 0; i < m->columns; i++)
		gcFree(m->numbers[i]);
	gcFree(m->numbers);
	gcFree(m);
	return matrixSucc;
}

/* matrixPrint the matrix  */
int matrixPrint(Matrix *m)
{
	unsigned int i, j;
	if(m == NULL)
		return matrixFail;
	for(i = 0; i < m->rows; i++){
		for(j = 0; j < m->columns; j++){
			printf("%f ", m->numbers[j][i]);
		}
		printf("\n");
	}
	return matrixSucc;
}

int matrixRowSwap(Matrix *m, int a, int b)
{
	double temp;
	unsigned int i;
	if(m == NULL)
		return matrixFail;
	if(m->rows <= a || m->rows <= b)
		return matrixFail;	
	for(i = 0; i < m->columns; i++){
		temp = m->numbers[i][a];
		m->numbers[i][a] = m->numbers[i][b];
		m->numbers[i][b] = temp;	
	}		
	return matrixSucc;	
}

int matrixScalarMultiply(Matrix *m, float scalar)
{
	int i, j;
	if(m == NULL)
		return matrixFail;
	for(i = 0; i < m->columns; i++){
		for(j = 0; j < m->rows; j++)
			(m->numbers[i])[j] *= scalar;
	}
	return matrixSucc;
}

/* matrixReduce row b by factor*a  */
int matrixReduce(Matrix *m, int a, int b, float factor)
{
	int i;
	if(m == NULL)
		return matrixFail;
	if(m->rows < a || m->rows < b)
		return matrixFail;
	for(i = 0; i < m->columns; i++){
		m->numbers[i][b]  -= m->numbers[i][a]*factor;
	}

	return matrixSucc;
}

/* matrix m will become the matrixIdentity so the caller must save their matrix themselves  */
Matrix *matrixInversion(Matrix *m)
{
	Matrix *invert;
	unsigned int i, j, l;
	double factor;
	if(m == NULL)
		return NULL;
	if((m)->columns != (m)->rows)
		return NULL;
	invert = matrixIdentity((m)->rows);

	/* matrixReduce each of the rows to get a lower triangle */	
	for(i = 0; i < (m)->columns; i++){
		for(j = i + 1; j < (m)->rows; j++){
			if((m)->numbers[i][i] == 0){
				for(l=i+1; l < m->rows; l++){
					if(m->numbers[l][l] != 0){
						matrixRowSwap(m, i, l);
						break;
					}
				}	
				continue;
			}
			factor = (m)->numbers[i][j]/((m)->numbers[i][i]);
			matrixReduce(invert, i, j, factor);
			matrixReduce((m), i, j, factor);
		}
	}
	/* now finish the upper triangle  */
	for(i = (m)->columns - 1; i > 0; i--){
		for(j = i-1; j>=0; j--){
			if((m)->numbers[i][i] == 0)
				continue;
			if(j == -1)
				break;
			factor = (m)->numbers[i][j]/((m)->numbers[i][i]);
			matrixReduce(invert, i, j, factor);
			matrixReduce((m), i, j, factor);
		}
	}
	/* scale everything to 1 */
	for(i = 0; i < (m)->columns; i++){
		if((m)->numbers[i][i]==0)
			continue;
		factor = 1/((m)->numbers[i][i]);
		matrixRowScalarMultiply(invert, i, factor);
		matrixRowScalarMultiply((m), i, factor);
	}
	return invert;
}

int matrixRowScalarMultiply(Matrix *m, int row, float factor)
{
	int i;
	if(m == NULL)
		return matrixFail;
	if(m->rows <= row)
		return matrixFail;
	for(i = 0; i < m->columns; i++)
		m->numbers[i][row] *= factor;
	return matrixSucc;
}

int matrixEquals(Matrix *m1, Matrix *m2)
{
	unsigned int i, j;
	if(m1 == NULL || m2 == NULL)
		return matrixFail;
	if(m1->columns != m2->columns || m1->rows != m2->rows)
		return matrixFail;
	for(i = 0; i < m1->columns; i++){
		for(j = 0; j < m1->rows; j++){
			if(m1->numbers[i][j] != m2->numbers[i][j])
				return matrixFail;
		}
	}
	return matrixSucc;
}

Matrix *matrixClone(Matrix *m)
{
	Matrix *copy;
	unsigned int i, j;
	copy = matrixConstructor(m->rows, m->columns);
	for(i = 0; i < m->columns; i++)
		for(j = 0; j < m->rows; j++)
			copy->numbers[i][j] = m->numbers[i][j];
	return copy;
}

Matrix *matrixTranspose(Matrix *m)
{
	Matrix *trans;
	unsigned int i, j;
	if(m == NULL)
		return NULL;
	trans = matrixConstructor(m->columns, m->rows);
	for(i = 0; i < trans->columns; i++){
		for(j = 0; j < trans->rows; j++)
			trans->numbers[i][j] = m->numbers[j][i];
	}
	return trans;	
}

/* create random matrix of integers  */
Matrix *matrixRand(int rows, int columns, int modulo)
{
	Matrix *m;
	unsigned int i, j;
	srand(time(NULL));
	m = matrixConstructor(rows, columns);
	for(i = 0; i < columns; i++){
		for(j = 0; j < rows; j++){
			m->numbers[i][j] = rand()%modulo;
		}
	}
	return m; 
}

/* m1 x m2  */
Matrix *matrixMultiply(Matrix *m1, Matrix *m2)
{
	Matrix *product, *trans;
	unsigned int i, j;
	if(m1 == NULL || m2 == NULL)
		return NULL;
	if(m1->columns != m2->rows)
		return NULL;
	trans = matrixTranspose(m1);
	product = matrixConstructor(m1->rows, m2->columns);
	for(i = 0; i < product->columns; i++){
		for(j = 0; j < product->rows; j++){
			product->numbers[i][j] = vector_multiply(trans->numbers[j], m2->numbers[i], product->rows);
		}
	}
	matrixDestroy(trans);
	return product;
}

/* v1 x v2  -- simply a helper function -- computes dot product between two vectors*/
static double vector_multiply(double *col, double *row, int length)
{
	double sum;
	unsigned int i;
	sum = 0;
	for(i = 0; i < length; i++){
		sum += col[i] * row[i];
	}
	return sum;
}

/* m1 += m2  */
int matrixAdd(Matrix *m1, Matrix *m2)
{
	unsigned int i, j;
	if(m1 == NULL || m2 == NULL)
		return matrixFail;
	if(m1->rows != m2->rows || m1->columns != m2->columns)
		return matrixFail;
	for(i = 0; i < m1->columns; i++){
		for(j = 0; j < m1->rows; j++)
			m1->numbers[i][j] += m2->numbers[i][j];
	}
	return matrixSucc;
}

int matrixSub(Matrix *m1, Matrix *m2)
{
	unsigned int i, j;
	if(m1 == NULL || m2 == NULL)
		return matrixFail;
	if(m1->rows != m2->rows || m1->columns != m2->columns)
		return matrixFail;
	for(i = 0; i < m1->columns; i++){
		for(j = 0; j < m1->rows; j++)
			m1->numbers[i][j] -= m2->numbers[i][j];
	}
	return matrixSucc;
}

/* change m into an orthogonal matrix  */
Matrix *matrixGramSchmidt(Matrix *m)
{
	Matrix *ortho;
	double *ortho_vector, *temp;
	unsigned int i, j;
	if(m != NULL || m->rows == m->columns || matrixZeroVector(m) != 1){
		/* create my empy matrix to have new orthogonal vector be added to */
		ortho = matrixConstructor(m->rows, 1);
		/* initialize with the first vector */
		gcFree(ortho->numbers[0]);
		ortho_vector = gcMalloc(sizeof(double)*m->rows);
		for(i = 0; i < m->rows; i++)
			ortho_vector[i] = m->numbers[0][i];
		ortho->numbers[0] = ortho_vector;	
		/* now loop and go through the gs system */
		for(i = 1; i < m->columns; i++){
			/* first initialize to the regular vector */
			ortho_vector = gcMalloc(sizeof(double)*m->rows);
			for(j = 0; j < m->rows; j++)
				ortho_vector[j] = m->numbers[i][j];
			/* get the subtracting factor */
			temp = matrixProjection(ortho, ortho_vector, m->rows);
			/* expand the matrix */
			ortho->columns++;
			ortho->numbers = gcRealloc(ortho->numbers, sizeof(double *)*ortho->columns);
			ortho->numbers[ortho->columns - 1] = ortho_vector;
			vector_subtraction(ortho_vector, temp, m->rows);
		}
		return ortho;
	}
	return NULL;
}

double *matrixProjection(Matrix *m, double *v, int length)
{
	unsigned int i, j;
	double *sum, *copy, *vector, factor;
	if(m->rows != length)
		return NULL;
	if(m == NULL || v == NULL)
		return NULL;
	sum = gcMalloc(sizeof(double)* m->rows);
	copy = gcMalloc(sizeof(double)*m->rows);
	for(i = 0; i < m->columns; i++){
		for(j = 0; j < m->rows; j++)
			copy[j] = m->numbers[i][j];
		vector = copy;
		factor = vector_multiply(v, vector, m->rows)/vector_multiply(vector, vector, m->rows);
		scalar_vector_multiplication(factor, vector, m->rows);
		vector_addition(sum, vector, m->rows);
	}
	gcFree(copy);
	return sum;
}

/* v1 *= v2  */
static void scalar_vector_multiplication(double factor, double *vector, int length)
{
	unsigned int i;
	for(i = 0; i < length; i++)
		vector[i] *= factor;
}

/* v1 += v2  */
static void vector_addition(double *v1, double *v2, int length)
{
	unsigned int i;
	for(i = 0; i < length; i++){
		v1[i] += v2[i];
	}
}

static void vector_subtraction(double *v1, double *v2, int length)
{
	unsigned int i;
	for(i = 0; i < length; i++){
		v1[i] -= v2[i];
	}
}

double matrixDeterminant(Matrix *m)
{
	Matrix *copy;
	unsigned int i, j;
	double det, factor;
	if(m == NULL)
		return -1;
	if(m->columns != m->rows)
		return -1;
	copy = matrixClone(m);
	det = 1;

	/* matrixReduce each of the rows to get a lower triangle */	
	for(i = 0; i < copy->columns; i++){
		for(j = i + 1; j < copy->rows; j++){
			if(copy->numbers[i][i] == 0)
				continue;
			factor = copy->numbers[i][j]/(copy->numbers[i][i]);
			matrixReduce(copy, i, j, factor);
		}
	}
	for(i = 0; i < copy->columns; i++)
		det *= copy->numbers[i][i];
	matrixDestroy(copy);
	return det;
}

Matrix *matrixOrthoNormalBasis(Matrix *m)
{
	Matrix *orthog;
	unsigned int i, j;
	double factor;
	if(m == NULL)
		return NULL;
	orthog = matrixGramSchmidt(m);
	for(i = 0; i < m->columns; i++){
		factor = 0;
		for(j = 0; j < m->rows; j++)
			factor += orthog->numbers[i][j]*orthog->numbers[i][j];
		factor = sqrt(factor);
		for(j = 0; j < m->rows; j++)
			orthog->numbers[i][j] /= factor;
	}
	return orthog;
}

Matrix *matrixSolvedAugMatrix(Matrix *m)
{
	Matrix *low;
	double factor, absolute;
	unsigned int i, j, k, l;
	if(m == NULL)
		return NULL;
	low = matrixClone(m);
	absolute = abs(m->rows - m->columns);
	for(k = 0; k < absolute; k++){
		/* matrixReduce each of the rows to get a lower triangle */	
		for(i = 0; i < low->columns && i<low->rows; i++){
			for(j = i + 1; j < low->rows; j++){
				if(low->numbers[i][i] == 0){
					for(l = i+1; l < low->rows; l++){
						if(m->numbers[l][l]!=0){
							matrixRowSwap(low, i, l);
							break;
						}
					}
					continue;
				}
				factor = low->numbers[i][j]/(low->numbers[i][i]);
				matrixReduce(low, i, j, factor);
			}
		}
		/* now finish the upper triangle  */
		for(i = (low->rows>low->columns)?low->columns-1:low->rows-1; i > 0; i--){
			for(j = i-1; j>=0; j--){
				if(low->numbers[i][i] == 0)
					continue;
				if(j == -1)
					break;
				factor = low->numbers[i][j]/(low->numbers[i][i]);
				matrixReduce(low, i, j, factor);
			}
		}
		/* scale everything to 1 */
		for(i = 0; i < low->columns; i++){
			if(low->numbers[i][i]==0)
				continue;
			factor = 1/(low->numbers[i][i]);
			matrixRowScalarMultiply(low, i, factor);
		}
	}
	return low;
}

/* Return an array of all of the possible matrixEigenValues */
double *matrixEigenValues(Matrix *m)
{
	double *values, factor;
	Matrix *red;
	unsigned int i, j, l;
	if(m == NULL)
		return NULL;
	if(m->rows != m->columns)
		return NULL;
	values = gcMalloc(sizeof(double)*m->rows);
	red = matrixClone(m);
	/* matrixReduce each of the rows to get a lower triangle */	
	for(i = 0; i < red->columns; i++){
		for(j = i + 1; j < red->rows; j++){
			if(red->numbers[i][i] == 0){
				for(l = i+1; l < red->rows; l++){
					if(red->numbers[l][l] != 0){
						matrixRowSwap(red, i, l);
						break;
					}
				}
				continue;
			}
			factor = red->numbers[i][j]/(red->numbers[i][i]);
			matrixReduce(red, i, j, factor);
		}
	}
	for(i = 0; i < red->columns; i++)
		values[i] = red->numbers[i][i];
	return values;
}

/* make your own matrix */
void matrixScanf(Matrix **m)
{
	Matrix *temp;
	int i, j, rows, cols;
	double number;
	char buffer[12];
	printf("Rows | Columns\n");
	/* should only execute once but I need to do error detection */
	rows = -1; cols = -1;
	while(fgets(buffer, 12, stdin) != NULL){
		sscanf(buffer, "%d | %d", &rows, &cols);
		break;
	}
	if(rows == -1 || cols == -1)
		perror("bad input");
	temp = matrixConstructor(rows, cols);
	if(temp == NULL)
		return;
	i = 0; j = 0;
	printf("start entering numbers from left to right, top to bottom\nand use either EOF to end input\n");
	while(fgets(buffer, 6, stdin) != NULL){
		number = atof(buffer);
		temp->numbers[i%cols][(int) floor(j/rows)] = number;
		i++;
		j++;
	}
	*m = temp;
}
