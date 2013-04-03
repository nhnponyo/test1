/*
	작성자: 김동진
	작성일: 2013.03.31
	기능
		matrixSum(), matrixMulti(), matrixTranspose() 함수 테스트
*/
#include <stdio.h>
#include <stdlib.h>

extern int **make2DArray(int rowNum, int colNum);
extern void	matrixSum(int **matrixResult, int **matrixA, int **matrixB, int rowNum, int colNum);
extern int	matrixMulti(int **matrixResult, int **matrixA, int rowNumOfA, int colNumOfA, int **matrixB, int rowNumOfB, int colNumOfB);
extern void	matrixTranspose(int **matrixAT, int **matrixA, int rowNumOfA, int colNumOfA);

//
// matrix를 출력하는 함수
//
void	printMatrix(int **matrix, int rowNum, int colNum)
{
	int	rowIdx, colIdx;

	for(rowIdx=0; rowIdx < rowNum; rowIdx++) {
		for(colIdx = 0; colIdx < colNum; colIdx++) {
			printf("%10d ", matrix[rowIdx][colIdx]);
		}
		printf("\n");
	}
}

//
// make2DArray()와 random number 생성기를 이용해서 matrix를 생성하는 함수
//
int **generateMatrix(int rowNum, int colNum)
{
	int	rowIdx, colIdx;
	int **matrix = make2DArray(rowNum, colNum);

	// matrix의 각 원소에 임의의 값 저장
	for(rowIdx = 0; rowIdx < rowNum; rowIdx++)
		for(colIdx = 0; colIdx < colNum; colIdx++) 
			matrix[rowIdx][colIdx] = rand() % 10;

	return matrix;
}

//
// matrix 합 테스트 함수
//
void testMatrixSum(void)
{
	int **matrixA, **matrixB;
	int	**matrixResult;
	int	rowNum, colNum;

	rowNum = colNum = 3;

	matrixA = generateMatrix(rowNum, colNum);
	matrixB = generateMatrix(rowNum, colNum);

	matrixResult = make2DArray(rowNum, colNum);

	matrixSum(matrixResult, matrixA, matrixB, rowNum, colNum);

	printf("----------- test: matrix addition ------------------\n");

	printf("matrixA\n");
	printMatrix(matrixA, rowNum, colNum);

	printf("matrixB\n");
	printMatrix(matrixB, rowNum, colNum);

	printf("matrixResult = matrixA + matrixB\n");
	printMatrix(matrixResult, rowNum, colNum);

}

//
// matrix 곱 테스트 함수
//
void testMatrixMulti(void)
{
	int **matrixA, **matrixB;
	int	**matrixResult;
	int	rowNumOfA, colNumOfA;
	int	rowNumOfB, colNumOfB;
	int rowNumOfR, colNumOfR;

	rowNumOfA = 2;
	colNumOfA = 3;

	rowNumOfB = 3;
	colNumOfB = 2;

	matrixA = generateMatrix(rowNumOfA, colNumOfA);
	matrixB = generateMatrix(rowNumOfB, colNumOfB);

	matrixResult = make2DArray(rowNumOfA, colNumOfA);

	printf("----------- test: matrix multiplication ------------------\n");
	if(!matrixMulti(matrixResult, matrixA, rowNumOfA, colNumOfA, matrixB, rowNumOfB, colNumOfB)) {
		printf("matrixA\n");
		printMatrix(matrixA, rowNumOfA, colNumOfA);

		printf("matrixB\n");
		printMatrix(matrixB, rowNumOfB, colNumOfB);

		printf("matrixResult = matrixA x matrixB\n");
		rowNumOfR = rowNumOfA;
		colNumOfR = colNumOfB;
		printMatrix(matrixResult, rowNumOfR, colNumOfR);	
	}
	else
		printf("Fail to matrix multiplication\n");
}

//
// matrix tranpose 테스트 함수
//
void testMatrixTranspose(void)
{
	int **matrixA;
	int	**matrixAT;
	int	rowNumOfA, colNumOfA;
	int rowNumOfAT, colNumOfAT;

	rowNumOfA = 2;
	colNumOfA = 3;
	matrixA = generateMatrix(rowNumOfA, colNumOfA);

	rowNumOfAT = colNumOfA;
	colNumOfAT = rowNumOfA;
	matrixAT = make2DArray(rowNumOfAT, colNumOfAT);

	printf("----------- test: matrix transpose ------------------\n");
	matrixTranspose(matrixAT, matrixA, rowNumOfA, colNumOfA);

	printf("matrixA\n");
	printMatrix(matrixA, rowNumOfA, colNumOfA);

	printf("matrixAT\n");
	printMatrix(matrixAT, rowNumOfAT, colNumOfAT);		
}