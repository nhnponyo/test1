#include <stdio.h>
#include <stdlib.h>
#include "sparse_matrix_types.h"

extern int **make2DArray(int rowNum, int colNum);
extern int **generateMatrix(int rowNum, int colNum);

extern int	release2DArray(int **intArr, int rowNum);
sparse_matrix_t *sparse_matrix_creation(int **matrix, int rowNum, int colNum);

extern void	printMatrix(int **matrix, int rowNum, int colNum);
extern void setManyElementsOfMatrixToZero(int **matrix, int rowNum, int colNum);
extern int	sparse_matrix_transpose(sparse_matrix_t *dst, sparse_matrix_t *src);
extern int	sparse_matrix_fast_transpose(sparse_matrix_t *dst, sparse_matrix_t *src);
extern int	sparse_matrix_multi(sparse_matrix_t *matrixC, sparse_matrix_t *matrixA, sparse_matrix_t *matrixB);
extern int	matrixMulti(int **matrixResult, int **matrixA, int rowNumOfA, int colNumOfA, int **matrixB, int rowNumOfB, int colNumOfB);
extern void	printMatrix(int **matrix, int rowNum, int colNum);

void	print_sparse_matrix(sparse_matrix_t *sparse_matrix)
{
	int	eleIdx;

	for(eleIdx = 0; eleIdx <= sparse_matrix[0].value; eleIdx++)
		printf("%5d %5d %5d\n", sparse_matrix[eleIdx].rowIdx, sparse_matrix[eleIdx].colIdx,  sparse_matrix[eleIdx].value);
}

void test_sparse_matrix_transpose(void)
{
	int **matrix;
	sparse_matrix_t	*sparseMatrixA, *sparseMatrixAT;
	int	rowNum = 7, colNum = 5;

	// matrix ����
	matrix = generateMatrix(rowNum, colNum);
	setManyElementsOfMatrixToZero(matrix, rowNum, colNum); // sparse matrix�� ��ȯ�ϱ� ���ؼ� ���������� �����ϰ� ���ҵ��� 0���� ����
	printMatrix(matrix, rowNum, colNum); // ������ matrix ���

	// sparse_matrix ����Ÿ ������ ��ȯ
	sparseMatrixA = sparse_matrix_creation(matrix, rowNum, colNum); 
	printf("----- sparse matrix -----\n");
	print_sparse_matrix(sparseMatrixA); // sparse_matrix ����Ÿ ���

	// matrix transpose ����� ������ �޸� ���� ����
	sparseMatrixAT = (sparse_matrix_t *)malloc( ( sizeof(sparse_matrix_t) * (sparseMatrixA[0].value+1) ) );
	
	// TEST: matrix transpose ���
	sparse_matrix_transpose(sparseMatrixAT, sparseMatrixA);
	printf("----- matrix transpose result -----\n");
	print_sparse_matrix(sparseMatrixAT); // sparseMatrixAT ����Ÿ ���

	// �޸� ����
	release2DArray(matrix, rowNum); // matrix �޸� ����
	free(sparseMatrixAT); 	// matrixT �޸� ����
	free(sparseMatrixA);				// sparseMatrix �޸� ����
}

void test_sparse_matrix_fast_transpose(void)
{
	int **matrix;
	sparse_matrix_t	*sparseMatrixA, *sparseMatrixAT;
	int	rowNum = 7, colNum = 5;

	// matrix ����
	matrix = generateMatrix(rowNum, colNum); // sparse matrix�� ��ȯ�ϱ� ���ؼ� ���������� �����ϰ� ���ҵ��� 0���� ����
	setManyElementsOfMatrixToZero(matrix, rowNum, colNum);
	printMatrix(matrix, rowNum, colNum); 	// ������ matrix ���

	// sparse_matrix ����Ÿ ������ ��ȯ
	sparseMatrixA = sparse_matrix_creation(matrix, rowNum, colNum);
	printf("----- matrix -----\n");
	print_sparse_matrix(sparseMatrixA); // sparse_matrix ����Ÿ ��

	// matrix transpose ����� ������ �޸� ���� ����
	sparseMatrixAT = (sparse_matrix_t *)malloc( ( sizeof(sparse_matrix_t) * (sparseMatrixA[0].value+1) ) );

	// TEST: fast matrix transpose
	sparse_matrix_fast_transpose(sparseMatrixAT, sparseMatrixA);
	printf("----- matrix fast transpose result -----\n");
	print_sparse_matrix(sparseMatrixAT); // sparseMatrixAT ����Ÿ ���

	// �޸� ����
	release2DArray(matrix, rowNum); // matrix �޸� ����
	free(sparseMatrixAT); 	// matrixT �޸� ����
	free(sparseMatrixA);	// sparseMatrix �޸� ����
}

void test_sparse_matrix_multi(void)
{
	int **matrixA, **matrixB, **matrixC;
	sparse_matrix_t	*sparseMatrixA;
	sparse_matrix_t *sparseMatrixB;
	sparse_matrix_t *sparseMatrixC; // C = A * B
	int	rowNumOfA = 3, colNumOfA = 4;
	int	rowNumOfB = 4, colNumOfB = 3;
	int	rowNumOfC, colNumOfC;

	// matrix A ����
	matrixA = generateMatrix(rowNumOfA, colNumOfA);
	setManyElementsOfMatrixToZero(matrixA, rowNumOfA, colNumOfA); // sparse matrix�� ��ȯ�ϱ� ���ؼ� ���������� �����ϰ� ���ҵ��� 0���� ����
	printf("----- matrix A -----\n");
	printMatrix(matrixA, rowNumOfA, colNumOfA); // ������ matrix ���

	// matrix B ����
	matrixB = generateMatrix(rowNumOfB, colNumOfB);
	setManyElementsOfMatrixToZero(matrixB, rowNumOfB, colNumOfB); // sparse matrix�� ��ȯ�ϱ� ���ؼ� ���������� �����ϰ� ���ҵ��� 0���� ����
	printf("----- matrix B -----\n");
	printMatrix(matrixB, rowNumOfB, colNumOfB); // ������ matrix ���

	// matrixA�� sparse_matrix ����Ÿ ������ ��ȯ
	sparseMatrixA = sparse_matrix_creation(matrixA, rowNumOfA, colNumOfA);
	printf("----- sparse matrix A -----\n");
	print_sparse_matrix(sparseMatrixA); // sparse_matrix ����Ÿ ���

	// matrixB�� sparse_matrix ����Ÿ ������ ��ȯ
	sparseMatrixB = sparse_matrix_creation(matrixB, rowNumOfB, colNumOfB);
	printf("----- sparse matrix B -----\n");
	print_sparse_matrix(sparseMatrixB); // sparse_matrix ����Ÿ ���

	// sparse matrix�� sparse matrix�� ���� ����� full matrix�� �� ���� �־ (matrixA�� ���� ����) x (matrixB�� ���� ����) ��ŭ�� �޸� ���� �Ҵ�
	sparseMatrixC = (sparse_matrix_t *)malloc( sizeof(sparse_matrix_t) * (sparseMatrixA[0].rowIdx * sparseMatrixB[0].colIdx + 1) ); // +1�� 0��° ���Ұ� Ư�� �뵵�� ���Ǳ� ����.

	// sparseMatrixC = sparseMatrixA x sparseMatrixB ����
	sparse_matrix_multi(sparseMatrixC, sparseMatrixA, sparseMatrixB);
	printf("----- sparse matrix C = A x B -----\n");
	print_sparse_matrix(sparseMatrixC); // sparse_matrix ����Ÿ ���

	// �Ϲ� matrix ���� ����
	rowNumOfC = rowNumOfA;
	colNumOfC = colNumOfB;
	matrixC = generateMatrix(rowNumOfC, colNumOfC);
	matrixMulti(matrixC, matrixA, rowNumOfA, colNumOfA, matrixB, rowNumOfB, colNumOfB);
	printf("----- matrix C = A x B -----\n");
	printMatrix(matrixC, rowNumOfC, colNumOfC); // sparse_matrix ����Ÿ ���

	// �޸� ����
	release2DArray(matrixA, rowNumOfA); // matrixA �޸� ����
	release2DArray(matrixB, rowNumOfB); // matrixB �޸� ����
	free(sparseMatrixA);	// sparseMatrixA �޸� ����
	free(sparseMatrixB); 	// sparseMatrixB �޸� ����
	free(sparseMatrixC);	// sparseMatrixC �޸� ����
}