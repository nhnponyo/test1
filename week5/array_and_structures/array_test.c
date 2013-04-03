/*
	�ۼ���: �赿��
	�ۼ���: 2013.03.31
	����:
		1. array.c�� �Լ����� �׽�Ʈ�ϱ� ���� �Լ���
	�ֿ� �Լ�
	    1. print2DArray()
		2. print2DArrayOfFixedSize()
		3. testMake2DArray()
		4. test2DArrayOfFixedSize()

*/

#include <stdio.h>
#include <stdlib.h>

extern int **make2DArray(int rowNum, int colNum);

//
// ���� �Ҵ�� 2���� �迭 �޸��� �Լ� ���� �� ��� ����
//
void print2DArray(int **twoDimArray, int rowNum, int colNum)
{
	int	rowIdx, colIdx;

	// matrix�� �� ���ҿ� ����� �� ���
	for(rowIdx = 0; rowIdx < rowNum; rowIdx++) {
		for(colIdx = 0; colIdx < colNum; colIdx++)
			printf("%10d ", twoDimArray[rowIdx][colIdx]);
		printf("\n");
	}

	return;
}

//
// 2���� �迭�� �Ѱܹ޴� �Լ�
// 2���� �迭�� ���� ���̸� �Լ� ���ڿ� ����ؾ� ��.
//
void print2DArrayOfFixedSize(int twoDimArray[][5], int rowNum, int colNum)
{
	int	rowIdx, colIdx;

	// matrix�� �� ���ҿ� ����� �� ���
	for(rowIdx = 0; rowIdx < rowNum; rowIdx++) {
		for(colIdx = 0; colIdx < colNum; colIdx++)
			printf("%10d ", twoDimArray[rowIdx][colIdx]);
		printf("\n");
	}

	return;
}


//
// �׽�Ʈ �Լ�: ���� �Ҵ�� 2���� �迭 �޸��� �Լ� ���� �� ���
//
void testMake2DArray(void)
{
	int	**twoDimArray;
	int	rowNum, colNum;
	int	rowIdx, colIdx;

	printf("start testMake2DArray()\n");

	// ��� ���� ���� ����
	rowNum = 5;
	colNum = 5;
	// ������ ũ���� matrix �޸� ����
	twoDimArray = make2DArray(rowNum, colNum);

	// matrix�� �� ���ҿ� ������ �� ����
	for(rowIdx = 0; rowIdx < rowNum; rowIdx++)
		for(colIdx = 0; colIdx < colNum; colIdx++) 
			twoDimArray[rowIdx][colIdx] = rand() % 10;
	
	print2DArray(twoDimArray, rowNum, colNum);

	return;
}


//
// �׽�Ʈ �ڵ�: 2���� �迭�� ������ �� �Լ��� �ѱ�� ��� ����
//
void test2DArrayOfFixedSize(void)
{
	// �迭�� ũ�Ⱑ ������
	int	test2DArray[3][5] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
	int	rowIdx, colIdx;

	printf("start test2DArrayOfFixedSize()\n");

	// matrix�� �� ���ҿ� ������ �� ����
	for(rowIdx = 0; rowIdx < 3; rowIdx++)
		for(colIdx = 0; colIdx < 5; colIdx++) 
			test2DArray[rowIdx][colIdx] = rand() % 10;

	// ����� ũ�⸦ �Ѱ��־�� ��.
	print2DArrayOfFixedSize(test2DArray, 3, 5);

	return;
}