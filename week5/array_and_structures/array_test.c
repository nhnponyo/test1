/*
	작성자: 김동진
	작성일: 2013.03.31
	내용:
		1. array.c의 함수들을 테스트하기 위한 함수들
	주요 함수
	    1. print2DArray()
		2. print2DArrayOfFixedSize()
		3. testMake2DArray()
		4. test2DArrayOfFixedSize()

*/

#include <stdio.h>
#include <stdlib.h>

extern int **make2DArray(int rowNum, int colNum);

//
// 동적 할당된 2차원 배열 메모리의 함수 전달 및 출력 예제
//
void print2DArray(int **twoDimArray, int rowNum, int colNum)
{
	int	rowIdx, colIdx;

	// matrix의 각 원소에 저장된 값 출력
	for(rowIdx = 0; rowIdx < rowNum; rowIdx++) {
		for(colIdx = 0; colIdx < colNum; colIdx++)
			printf("%10d ", twoDimArray[rowIdx][colIdx]);
		printf("\n");
	}

	return;
}

//
// 2차원 배열을 넘겨받는 함수
// 2차원 배열의 열의 길이를 함수 인자에 사용해야 함.
//
void print2DArrayOfFixedSize(int twoDimArray[][5], int rowNum, int colNum)
{
	int	rowIdx, colIdx;

	// matrix의 각 원소에 저장된 값 출력
	for(rowIdx = 0; rowIdx < rowNum; rowIdx++) {
		for(colIdx = 0; colIdx < colNum; colIdx++)
			printf("%10d ", twoDimArray[rowIdx][colIdx]);
		printf("\n");
	}

	return;
}


//
// 테스트 함수: 동적 할당된 2차원 배열 메모리의 함수 전달 및 출력
//
void testMake2DArray(void)
{
	int	**twoDimArray;
	int	rowNum, colNum;
	int	rowIdx, colIdx;

	printf("start testMake2DArray()\n");

	// 행과 열의 개수 지정
	rowNum = 5;
	colNum = 5;
	// 지정된 크기의 matrix 메모리 생성
	twoDimArray = make2DArray(rowNum, colNum);

	// matrix의 각 원소에 임의의 값 저장
	for(rowIdx = 0; rowIdx < rowNum; rowIdx++)
		for(colIdx = 0; colIdx < colNum; colIdx++) 
			twoDimArray[rowIdx][colIdx] = rand() % 10;
	
	print2DArray(twoDimArray, rowNum, colNum);

	return;
}


//
// 테스트 코드: 2차원 배열을 선언한 후 함수로 넘기는 방법 예제
//
void test2DArrayOfFixedSize(void)
{
	// 배열의 크기가 고정됨
	int	test2DArray[3][5] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
	int	rowIdx, colIdx;

	printf("start test2DArrayOfFixedSize()\n");

	// matrix의 각 원소에 임의의 값 저장
	for(rowIdx = 0; rowIdx < 3; rowIdx++)
		for(colIdx = 0; colIdx < 5; colIdx++) 
			test2DArray[rowIdx][colIdx] = rand() % 10;

	// 행렬의 크기를 넘겨주어야 함.
	print2DArrayOfFixedSize(test2DArray, 3, 5);

	return;
}