/*
	�ۼ���: �赿��
	����: matrix ���� �Լ� ����
	�� ����
		matrixSum()
		matrixMulti()
		matrixTranspose()
*/

#include "def.h"

#if !TEMPLATE_MATRIX

/*
	���: �� ���� matrix�� �־����� �� matrix�� ���� ���
	input: matrixA, matrixB, rowIdx, colNum
			rowNum: ���� ����
			colNum: ���� ����
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
	���: �� ���� matrix�� �־����� �� matrix�� ���� ���
	input: matrixA, matrixB, rowIdx, colNum
			rowNum: ���� ����
			colNum: ���� ����
	output: matrixResult
			matrixResult = matrixA * matrixB
*/
int matrixMulti(int **matrixResult, int **matrixA, int rowNumOfA, int colNumOfA, int **matrixB, int rowNumOfB, int colNumOfB)
{
	int	rowIdx, colIdx, kIdx;

	if(colNumOfA != rowNumOfB) // matrix ������ �� �� ����.
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
	���: �� ���� matrix�� �־����� �־��� matrix�� tranposed matrix�� ���Ѵ�.
	input: matrixA, rowNum, colNum
			rowNum: ���� ����
			colNum: ���� ����
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