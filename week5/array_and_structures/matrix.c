/*
	작성자: 김동진
	내용: matrix 연산 함수 집합
	상세 내용
		matrixSum()
		matrixMulti()
		matrixTranspose()
*/

#include "def.h"

#if !TEMPLATE_MATRIX

/*
	기능: 두 개의 matrix가 주어지면 두 matrix의 합을 계산
	input: matrixA, matrixB, rowIdx, colNum
			rowNum: 행의 개수
			colNum: 열의 개수
	output: matrixResult
			matrixResult = matrixA + matrixB
*/
void matrixSum(int **matrixResult, int **matrixA, int **matrixB, int rowNum, int colNum)
{
	int	rowIdx, colIdx;

	for(rowIdx=0; rowIdx < rowNum; rowIdx++)
		for(colIdx=0; colIdx < colNum; colIdx++)
			matrixResult[rowIdx][colIdx] = matrixA[rowIdx][colIdx] + matrixB[rowIdx][colIdx];
}

/*
	기능: 두 개의 matrix가 주어지면 두 matrix의 곱을 계산
	input: matrixA, matrixB, rowIdx, colNum
			rowNum: 행의 개수
			colNum: 열의 개수
	output: matrixResult
			matrixResult = matrixA * matrixB
*/
int matrixMulti(int **matrixResult, int **matrixA, int rowNumOfA, int colNumOfA, int **matrixB, int rowNumOfB, int colNumOfB)
{
	int	rowIdx, colIdx, kIdx;

	if(colNumOfA != rowNumOfB) // matrix 곱셈을 할 수 없음.
		return -1;

	for(rowIdx=0; rowIdx < rowNumOfA; rowIdx++) {
		for(colIdx=0; colIdx < colNumOfB; colIdx++) {
			matrixResult[rowIdx][colIdx] = 0;
			for(kIdx=0; kIdx < colNumOfA; kIdx++)
				matrixResult[rowIdx][colIdx] += matrixA[rowIdx][kIdx] * matrixB[kIdx][colIdx];
		}
	}

	return 0;
}

/*
	기능: 한 개의 matrix가 주어지면 주어진 matrix의 tranposed matrix를 구한다.
	input: matrixA, rowNum, colNum
			rowNum: 행의 개수
			colNum: 열의 개수
	output: matrixAT
			matrixAT[i][j] = matrixA[j][i]
*/
void matrixTranspose(int **matrixAT, int **matrixA, int rowNum, int colNum)
{
	int	rowIdx, colIdx;

	for(rowIdx=0; rowIdx < rowNum; rowIdx++)
		for(colIdx=0; colIdx < colNum; colIdx++)
			matrixAT[colIdx][rowIdx] = matrixA[rowIdx][colIdx];

	return;	
}


#endif // !TEMPLATE