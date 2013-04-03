/*
	작성자: 김동진
	내용: matrix 연산 함수 집합
	상세 내용
		matrixSum()
		matrixMulti()
		matrixTranspose()
*/

#include "def.h"

#if TEMPLATE_MATRIX

/*
	기능: 두 개의 matrix가 주어지면 두 matrix의 합을 계산한다.
	input: matrixA, matrixB, rowIdx, colNum
			rowNum: 행의 개수
			colNum: 열의 개수
	output: matrixResult
			matrixResult = matrixA + matrixB
*/
void matrixSum(int **matrixResult, int **matrixA, int **matrixB, int rowNum, int colNum)
{
	//
	// 채울 부분
	//
	// 
}

/*
	기능: 두 개의 matrix가 주어지면 두 matrix의 곱을 계산한다.
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

	//
	// 채울 부분
	//
	// matrixResult의 각 원소의 값을 구하기 위해서 매트릭스의 각 원소를 스캔한다.
	// scan하면서 각 원소의 값을 계산하기 위해서 아래 작업을 수행한다.
	//		matrixA의 각 행과 matrixB의 각 열에 대해서 벡터내적을 구한다.
	//		벡터내적이란 (a1, b1, c1)와 (a2, b2, c3)의 두 벡터가 주여졌을 때 a1*b1 + a2*b2 + a3*b3를 구하는 것이다. 

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

	//
	// 채울 부분
	//
	// matrixAT에 각 원소의 값을 저장한다.
	// 이를 위해서 matrixA의 각 원소들을 scan하면서 아래 작업을 수행한다.
	//		matrixAT[[i][j] = matrixA[j][i]
	//
}

#endif // TEMPLATE