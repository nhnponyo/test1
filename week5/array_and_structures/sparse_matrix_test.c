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

	// matrix 생성
	matrix = generateMatrix(rowNum, colNum);
	setManyElementsOfMatrixToZero(matrix, rowNum, colNum); // sparse matrix로 변환하기 위해서 강제적으로 랜덤하게 원소들을 0으로 갱신
	printMatrix(matrix, rowNum, colNum); // 생성한 matrix 출력

	// sparse_matrix 데이타 구조로 변환
	sparseMatrixA = sparse_matrix_creation(matrix, rowNum, colNum); 
	printf("----- sparse matrix -----\n");
	print_sparse_matrix(sparseMatrixA); // sparse_matrix 데이타 출력

	// matrix transpose 결과를 저장할 메모리 공간 생성
	sparseMatrixAT = (sparse_matrix_t *)malloc( ( sizeof(sparse_matrix_t) * (sparseMatrixA[0].value+1) ) );
	
	// TEST: matrix transpose 계산
	sparse_matrix_transpose(sparseMatrixAT, sparseMatrixA);
	printf("----- matrix transpose result -----\n");
	print_sparse_matrix(sparseMatrixAT); // sparseMatrixAT 데이타 출력

	// 메모리 해제
	release2DArray(matrix, rowNum); // matrix 메모리 해제
	free(sparseMatrixAT); 	// matrixT 메모리 해제
	free(sparseMatrixA);				// sparseMatrix 메모리 해제
}

void test_sparse_matrix_fast_transpose(void)
{
	int **matrix;
	sparse_matrix_t	*sparseMatrixA, *sparseMatrixAT;
	int	rowNum = 7, colNum = 5;

	// matrix 생성
	matrix = generateMatrix(rowNum, colNum); // sparse matrix로 변환하기 위해서 강제적으로 랜덤하게 원소들을 0으로 갱신
	setManyElementsOfMatrixToZero(matrix, rowNum, colNum);
	printMatrix(matrix, rowNum, colNum); 	// 생성한 matrix 출력

	// sparse_matrix 데이타 구조로 변환
	sparseMatrixA = sparse_matrix_creation(matrix, rowNum, colNum);
	printf("----- matrix -----\n");
	print_sparse_matrix(sparseMatrixA); // sparse_matrix 데이타 출

	// matrix transpose 결과를 저장할 메모리 공간 생성
	sparseMatrixAT = (sparse_matrix_t *)malloc( ( sizeof(sparse_matrix_t) * (sparseMatrixA[0].value+1) ) );

	// TEST: fast matrix transpose
	sparse_matrix_fast_transpose(sparseMatrixAT, sparseMatrixA);
	printf("----- matrix fast transpose result -----\n");
	print_sparse_matrix(sparseMatrixAT); // sparseMatrixAT 데이타 출력

	// 메모리 해제
	release2DArray(matrix, rowNum); // matrix 메모리 해제
	free(sparseMatrixAT); 	// matrixT 메모리 해제
	free(sparseMatrixA);	// sparseMatrix 메모리 해제
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

	// matrix A 생성
	matrixA = generateMatrix(rowNumOfA, colNumOfA);
	setManyElementsOfMatrixToZero(matrixA, rowNumOfA, colNumOfA); // sparse matrix로 변환하기 위해서 강제적으로 랜덤하게 원소들을 0으로 갱신
	printf("----- matrix A -----\n");
	printMatrix(matrixA, rowNumOfA, colNumOfA); // 생성한 matrix 출력

	// matrix B 생성
	matrixB = generateMatrix(rowNumOfB, colNumOfB);
	setManyElementsOfMatrixToZero(matrixB, rowNumOfB, colNumOfB); // sparse matrix로 변환하기 위해서 강제적으로 랜덤하게 원소들을 0으로 갱신
	printf("----- matrix B -----\n");
	printMatrix(matrixB, rowNumOfB, colNumOfB); // 생성한 matrix 출력

	// matrixA를 sparse_matrix 데이타 구조로 변환
	sparseMatrixA = sparse_matrix_creation(matrixA, rowNumOfA, colNumOfA);
	printf("----- sparse matrix A -----\n");
	print_sparse_matrix(sparseMatrixA); // sparse_matrix 데이타 출력

	// matrixB를 sparse_matrix 데이타 구조로 변환
	sparseMatrixB = sparse_matrix_creation(matrixB, rowNumOfB, colNumOfB);
	printf("----- sparse matrix B -----\n");
	print_sparse_matrix(sparseMatrixB); // sparse_matrix 데이타 출력

	// sparse matrix와 sparse matrix의 곱셈 결과가 full matrix가 될 수도 있어서 (matrixA의 행의 개수) x (matrixB의 열의 개수) 만큼의 메모리 동적 할당
	sparseMatrixC = (sparse_matrix_t *)malloc( sizeof(sparse_matrix_t) * (sparseMatrixA[0].rowIdx * sparseMatrixB[0].colIdx + 1) ); // +1은 0번째 원소가 특수 용도로 사용되기 때문.

	// sparseMatrixC = sparseMatrixA x sparseMatrixB 수행
	sparse_matrix_multi(sparseMatrixC, sparseMatrixA, sparseMatrixB);
	printf("----- sparse matrix C = A x B -----\n");
	print_sparse_matrix(sparseMatrixC); // sparse_matrix 데이타 출력

	// 일반 matrix 곱셈 수행
	rowNumOfC = rowNumOfA;
	colNumOfC = colNumOfB;
	matrixC = generateMatrix(rowNumOfC, colNumOfC);
	matrixMulti(matrixC, matrixA, rowNumOfA, colNumOfA, matrixB, rowNumOfB, colNumOfB);
	printf("----- matrix C = A x B -----\n");
	printMatrix(matrixC, rowNumOfC, colNumOfC); // sparse_matrix 데이타 출력

	// 메모리 해제
	release2DArray(matrixA, rowNumOfA); // matrixA 메모리 해제
	release2DArray(matrixB, rowNumOfB); // matrixB 메모리 해제
	free(sparseMatrixA);	// sparseMatrixA 메모리 해제
	free(sparseMatrixB); 	// sparseMatrixB 메모리 해제
	free(sparseMatrixC);	// sparseMatrixC 메모리 해제
}