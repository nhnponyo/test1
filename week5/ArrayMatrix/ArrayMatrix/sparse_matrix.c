/*
	작성자: 김동진
	작성일: 2013.04.02
	구성 함수
		sparse_matrix_creation()
		sparse_matrix_transpose()
		sparse_matrix_fast_transpose()
		sparse_matrix_multiplication()
*/
#include <stdio.h>
#include <stdlib.h>
#include "sparse_matrix_types.h"
#include "def.h"

#if !TEMPLATE_SPARSE_MATRIX

#define	ZERO_RATIO	(0.1 * 100)
extern int **make2DArray(int rowNum, int colNum);

//
// sparse matrix를 만들기 위해서 80%의 원소들을 강제적으로 0으로 치환하는 함수
//
void setManyElementsOfMatrixToZero(int **matrix, int rowNum, int colNum)
{
	int	rowIdx, colIdx;

	for(rowIdx = 0; rowIdx < rowNum; rowIdx++) {
		for(colIdx = 0; colIdx < colNum; colIdx++) {
			if( (rand() % 100) < ZERO_RATIO )
				matrix[rowIdx][colIdx] = 0;
		}
	}
}

//
// matrix가 주어지면 sparse_matrix 자료구조로 변환해서 return하는 함수
//
sparse_matrix_t *sparse_matrix_creation(int **matrix, int rowNum, int colNum)
{
	sparse_matrix_t *sparse_matrix;
	int	eleNum = 0;
	int	rowIdx, colIdx;
	int	eleIdx;

	// 입력 matrix의 각 element를 확인해서 0이 아닌 원소들의 개수를 측정한다.
	for(rowIdx = 0; rowIdx < rowNum; rowIdx++) {
		for(colIdx = 0; colIdx < colNum; colIdx++) {
			if(matrix[rowIdx][colIdx] != 0) eleNum++; // 0이 아닌 원소 개수마다 1 증가
		}
	}

	sparse_matrix = (sparse_matrix_t *)malloc(sizeof(sparse_matrix_t) * (eleNum + 1) ); // 원소의 개수를 저장하기 위해서 1개 추가로 메모리 할당한다.

	// sparse matrix 자료구조에서 배열의 첫 번째 원소에는 행의 개수, 열의 개수, 0이 아닌 원소의 개수를 저장
	eleIdx = 0;
	sparse_matrix[eleIdx].rowIdx = rowNum; // row(행)의 개수 저장
	sparse_matrix[eleIdx].colIdx = colNum; // column(열) 개수 저장
	sparse_matrix[eleIdx].value = eleNum; // 0이 아닌 원소의 개수 저장
	eleIdx++;

	// matrix의 모든 원소를 scan하면서 0이 아닌 원소를 sparse_matrix 배열에 저장한다.
	// 저장되는 값은 0이 아닌 원소의 행의 위치, 열의 위치, 원소의 값이다.
	for(rowIdx = 0; rowIdx < rowNum; rowIdx++) {
		for(colIdx = 0; colIdx < colNum; colIdx++) {
			if(matrix[rowIdx][colIdx] != 0) { // 0이 아닌 경우 저장
				sparse_matrix[eleIdx].rowIdx = rowIdx;
				sparse_matrix[eleIdx].colIdx = colIdx;
				sparse_matrix[eleIdx].value = matrix[rowIdx][colIdx];
				eleIdx++;
			}
		}
	}

	return sparse_matrix;
}

int sparse_matrix_transpose(sparse_matrix_t *dst, sparse_matrix_t *src)
{
	int	colIdx, eleIdx;
	int	curPosInDst = 0;

	if(!src || !dst) return -1; // source에 데이타가 없거나 destination 메모리 공간이 없으면 -1을 return한다.

	// dst[0]에 row 개수, col 개수, 0이 아닌 원수 개수를 저장한다.
	dst[0].rowIdx = src[0].colIdx; // src의 열의 개수가 dst의 행의 개수가 된다.
	dst[0].colIdx = src[0].rowIdx; // src의 행의 개수가 dst의 열의 개수가 된다.
	dst[0].value = src[0].value; // 0이 아닌 원소의 개수는 src와 dst가 같다. 왜냐하면, src의 모든 원소를 복사하기 때문이다. 

	if(src[0].value == 0)
		return 0; // 원소의 개수가 0이므로 더 이상 진행할 필요 없이 return. 정상적인 완료에 해당됨.

	// dst의 0번은 행의 개수, 열의 개수, 0이 아닌 원소 개수 등을 저장하므로 원소의 저장 공간을 1번부터 시작하도록 지정한다.
	curPosInDst = 1;

	// colIdx를 0번부터 src[0].colIdx - 1 까지 진행하면서
	// 진행 중인 colIdx와 같은 colIdx를 갖는 원소를 찾아서 dst에 저장한다. 
	for(colIdx = 0; colIdx < src[0].colIdx; colIdx++) {
		for(eleIdx = 1; eleIdx <= src[0].value; eleIdx++) { /* note: 1부터 시작 value까지 진행. 0은 row 개수 저장 용도로 사용됨 */
			if(src[eleIdx].colIdx == colIdx) { // 현재 지정된 colIdx와 같은 colIdx를 갖는 src 원소가 나오면 dst에 저장.
				dst[curPosInDst].colIdx = src[eleIdx].rowIdx;
				dst[curPosInDst].rowIdx = src[eleIdx].colIdx;
				dst[curPosInDst].value = src[eleIdx].value;
				curPosInDst++;
			}
		}
	}

	// 테스트 코드
	if( (curPosInDst-1) != src[0].value) {
		printf("src의 모든 원소가 dst로 복사되지 않음\n");
		return -2; // transpose 연산 오류: -2
	}

	return 0; // 정상 완료
}

int sparse_matrix_fast_transpose(sparse_matrix_t *dst, sparse_matrix_t *src)
{
	int	colIdx;
	int	rowNum, colNum;
	int	eleNum;
	int eleIdx;
	int	*eleNumOfEachCol;
	int	*startPosOfEachCol;
	int	posInDst;

	// source에 데이타가 없거나 destination 메모리 공간이 없으면 -1을 return한다.
	if(!src || !dst) return -1; // 입력 오류: -1

	// row 개수, col 개수, 0이 아닌 원소 개수를 확인한다.
	rowNum = src[0].rowIdx;
	colNum = src[0].colIdx;
	eleNum = src[0].value;

	// dst[0]에 row 개수, col 개수, 0이 아닌 원수 개수를 저장한다.
	dst[0].rowIdx = colNum; // src의 열의 개수가 dst의 행의 개수가 된다.
	dst[0].colIdx = rowNum; // src의 행의 개수가 dst의 열의 개수가 된다.
	dst[0].value = eleNum; // 0이 아닌 원소의 개수는 src와 dst가 같다. 왜냐하면, src의 모든 원소를 복사하기 때문이다. 

	// 원소의 개수가 0이면 더 이상 진행할 필요 없음
	if(eleNum == 0)
		return 0; // 정상적인 완료에 해당됨.

	// 행별로 src sparse_matrix에 0이 아닌 원소가 몇 개인지를 저장하기 위한 공간 할당 
	eleNumOfEachCol = (int *)malloc(sizeof(int)*colNum);
	if(!eleNumOfEachCol)
		return -2; // 메모리 할당 실패.
	
	// 행별로 dst sparse_matrix에 0이 아닌 원소가 위치하는 영역 중 첫 번째 위치를 저장하기 위한 공간 할당
	startPosOfEachCol = (int *)malloc(sizeof(int)*colNum);
	if(!startPosOfEachCol) {
		free(eleNumOfEachCol);
		return -3; // 메모리 할당 실패
	}

	// 할당한 메모리 초기화
	for(colIdx = 0; colIdx < colNum; colIdx++) {
		eleNumOfEachCol[colIdx] = 0;
		startPosOfEachCol[colIdx] = 0;
	}

	// src의 모든 원소를 scan하면서 col별로 몇 개의 원소가 있는지 확인
	for(eleIdx = 1; eleIdx <= eleNum; eleIdx++) // eleIdx = 0인 공간은 행의 개수 등을 저장하는 곳이므로 1부터 시작한다. eleNum과 같은 값이 될 때까지 진행해야 함.
		eleNumOfEachCol[src[eleIdx].colIdx]++;

	// eleNumOfEachCol[]를 scan하면서 dst에서 시작하는 위치를 계산한다.
	//		dst의 첫 번째 원소는 특수한 용도로 사용되고 있으며 그 용도는 행의 개수, 열의 개수, 0이 아닌 원소의 개수를 저장하고 있다.
	//		따라서, 0 column의 시작 위치를 dst의 1번째 위치로 지정한다.
	// 0번 column의 시작 위치는 위에서 정했으므로 아래의 for-loop는 1번부터 시작한다.
	startPosOfEachCol[0] = 1;
	for(colIdx = 1; colIdx < colNum; colIdx++)
		startPosOfEachCol[colIdx] = startPosOfEachCol[colIdx - 1] + eleNumOfEachCol[colIdx - 1];

	// src를 element별로 scan하면서
	// 각 원소의 colIdx와 startPosOfEachCol[colIdx]를 이용하여 원소가 dst에서 배치될 최종 위치에 저장한다.
	for(eleIdx = 1; eleIdx <= eleNum; eleIdx++) { // 0번은 특수 용도이므로 1번부터 시작한다.

		// src element의 colIdx를 이용해서 이 element가 dst의 몇 번째 위치에 저장될 지를 startPosOfEachCol[]을 이용해서 추출함.
		posInDst = startPosOfEachCol[src[eleIdx].colIdx];

		dst[posInDst].colIdx = src[eleIdx].rowIdx;
		dst[posInDst].rowIdx = src[eleIdx].colIdx;
		dst[posInDst].value = src[eleIdx].value;

		// 다음 번에 동일한 colIdx의 원소가 나올 때 dst에서 저장될 위치를 지정
		startPosOfEachCol[src[eleIdx].colIdx]++;
	}

	free(startPosOfEachCol);
	free(eleNumOfEachCol);

	return 0;
}

//
// matrix에서 startEldIdx부터 시작해서 matrix[startEleIdx].rowIdx와 값이 같은 마지막 원소를 찾아서 return한다.
//
int	findEndIdxWithEqualRowIdx(sparse_matrix_t *matrix, int startEleIdx)
{
	int	endEleIdx = startEleIdx;

	while( (endEleIdx + 1) <= matrix[0].value && matrix[endEleIdx+1].rowIdx == matrix[startEleIdx].rowIdx) endEleIdx++;
	
	return endEleIdx;
}

//
// 두 개 vector의 inner product (내적)을 구한다.
// 3차원 벡터의 경우 (x1, y1, z1)과 (x2, y2, z2)의 내적은 x1y2 + x2y2 + z1z2이다.
// matrixA x matrixB를 구하기 위해서 matrixA와 matrixBT의 각 열을 벡터로 처리해서 곱할 때
// 두 벡터의 곱은 colIdx가 같은 것끼리 곱하게 된다.
//
int	vectorInnerProduct(sparse_matrix_t *A, int startOfA, int endOfA, sparse_matrix_t *B, int startOfB, int endOfB)
{
	int	value = 0;
	int	aIdx, bIdx;

	aIdx = startOfA;
	bIdx = startOfB;

	while(aIdx <= endOfA && bIdx <= endOfB) {
		if(A[aIdx].colIdx == B[bIdx].colIdx) {
			value += A[aIdx].value * B[bIdx].value;
			aIdx++;
			bIdx++;
		}
		else if(A[aIdx].colIdx < B[bIdx].colIdx)
			aIdx++;
		else
			bIdx++;
	}

	return value;
}

/*
	sparse matrix의 곱셈
	C = A x B
*/
int	sparse_matrix_multi(sparse_matrix_t *matrixC, sparse_matrix_t *matrixA, sparse_matrix_t *matrixB)
{
	int	curEleIdxOfC;
	int startEleIdxOfA, endEleIdxOfA;
	int	startEleIdxOfBT, endEleIdxOfBT;
	int	eleValueOfC;
	sparse_matrix_t	*matrixBT;

	matrixC[0].rowIdx = matrixA[0].rowIdx; // 곱셈 결과의 행(row) 개수
	matrixC[0].colIdx = matrixB[0].colIdx; // 곱셈 결과의 열(column) 개수
	matrixC[0].value = 0; // 곱셈 결과의 0이 아닌 원소 개수
	curEleIdxOfC = 1; // sparse_matrix_t 배열의 원소 개수

	matrixBT = (sparse_matrix_t *)malloc(sizeof(sparse_matrix_t)*(matrixB[0].value + 1)); // transpose 저장할 메모리 생성
	if(sparse_matrix_fast_transpose(matrixBT, matrixB)) { // matrix transpose 수행
		free(matrixBT);
		return -1; // transpose 실패
	}

	startEleIdxOfA = matrixA[1].rowIdx; // matrixA의 첫 번째 원소의 행 번호
	do {
		endEleIdxOfA = findEndIdxWithEqualRowIdx(matrixA, startEleIdxOfA); // 동일한 행 번호를 갖는 마지막 원소 위치

		startEleIdxOfBT = 1; // matrixBT의 첫 번째 원소의 행 번호
		eleValueOfC = 0; // matrixC에 저장할 원소 값(c_ij = a_ik * b_kj) 초기화 
		do {
			endEleIdxOfBT = findEndIdxWithEqualRowIdx(matrixBT, startEleIdxOfBT); // matrixBT의 첫 번째 원소의 행 번호

			// c_ij 계산하는 부분
			eleValueOfC = vectorInnerProduct(matrixA, startEleIdxOfA, endEleIdxOfA, matrixBT, startEleIdxOfBT, endEleIdxOfBT); // 두 개의 벡터 내적. colIdx가 같은 경우만 곱해서 더함.
		
			if(eleValueOfC != 0) { // 0이 아니므로 matrixC에 저장
				matrixC[curEleIdxOfC].rowIdx = matrixA[startEleIdxOfA].rowIdx; // 저장되는 원소의 rowIdx는 matrixA 원소의 rowIdx
				matrixC[curEleIdxOfC].colIdx = matrixBT[startEleIdxOfBT].rowIdx; // 저장되는 원소의 colIdx는 matrixBT 원소의 rowIdx
				matrixC[curEleIdxOfC].value = eleValueOfC; // sum(a_ik * b_kj) 저장
				curEleIdxOfC++; // 다음 번에 저장할 위치 지정
			}

			startEleIdxOfBT = endEleIdxOfBT + 1;
			eleValueOfC = 0;
		} while(startEleIdxOfBT <= matrixBT[0].value);

		startEleIdxOfA = endEleIdxOfA + 1; 
	} while(startEleIdxOfA <= matrixA[0].value);

	matrixC[0].value = curEleIdxOfC - 1; 

	free(matrixBT);

	return 0;
}

#endif