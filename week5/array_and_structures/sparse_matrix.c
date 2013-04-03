/*
	�ۼ���: �赿��
	�ۼ���: 2013.04.02
	���� �Լ�
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
// sparse matrix�� ����� ���ؼ� 80%�� ���ҵ��� ���������� 0���� ġȯ�ϴ� �Լ�
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
// matrix�� �־����� sparse_matrix �ڷᱸ���� ��ȯ�ؼ� return�ϴ� �Լ�
//
sparse_matrix_t *sparse_matrix_creation(int **matrix, int rowNum, int colNum)
{
	sparse_matrix_t *sparse_matrix;
	int	eleNum = 0;
	int	rowIdx, colIdx;
	int	eleIdx;

	// �Է� matrix�� �� element�� Ȯ���ؼ� 0�� �ƴ� ���ҵ��� ������ �����Ѵ�.
	for(rowIdx = 0; rowIdx < rowNum; rowIdx++) {
		for(colIdx = 0; colIdx < colNum; colIdx++) {
			if(matrix[rowIdx][colIdx] != 0) eleNum++; // 0�� �ƴ� ���� �������� 1 ����
		}
	}

	sparse_matrix = (sparse_matrix_t *)malloc(sizeof(sparse_matrix_t) * (eleNum + 1) ); // ������ ������ �����ϱ� ���ؼ� 1�� �߰��� �޸� �Ҵ��Ѵ�.

	// sparse matrix �ڷᱸ������ �迭�� ù ��° ���ҿ��� ���� ����, ���� ����, 0�� �ƴ� ������ ������ ����
	eleIdx = 0;
	sparse_matrix[eleIdx].rowIdx = rowNum; // row(��)�� ���� ����
	sparse_matrix[eleIdx].colIdx = colNum; // column(��) ���� ����
	sparse_matrix[eleIdx].value = eleNum; // 0�� �ƴ� ������ ���� ����
	eleIdx++;

	// matrix�� ��� ���Ҹ� scan�ϸ鼭 0�� �ƴ� ���Ҹ� sparse_matrix �迭�� �����Ѵ�.
	// ����Ǵ� ���� 0�� �ƴ� ������ ���� ��ġ, ���� ��ġ, ������ ���̴�.
	for(rowIdx = 0; rowIdx < rowNum; rowIdx++) {
		for(colIdx = 0; colIdx < colNum; colIdx++) {
			if(matrix[rowIdx][colIdx] != 0) { // 0�� �ƴ� ��� ����
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

	if(!src || !dst) return -1; // source�� ����Ÿ�� ���ų� destination �޸� ������ ������ -1�� return�Ѵ�.

	// dst[0]�� row ����, col ����, 0�� �ƴ� ���� ������ �����Ѵ�.
	dst[0].rowIdx = src[0].colIdx; // src�� ���� ������ dst�� ���� ������ �ȴ�.
	dst[0].colIdx = src[0].rowIdx; // src�� ���� ������ dst�� ���� ������ �ȴ�.
	dst[0].value = src[0].value; // 0�� �ƴ� ������ ������ src�� dst�� ����. �ֳ��ϸ�, src�� ��� ���Ҹ� �����ϱ� �����̴�. 

	if(src[0].value == 0)
		return 0; // ������ ������ 0�̹Ƿ� �� �̻� ������ �ʿ� ���� return. �������� �Ϸῡ �ش��.

	// dst�� 0���� ���� ����, ���� ����, 0�� �ƴ� ���� ���� ���� �����ϹǷ� ������ ���� ������ 1������ �����ϵ��� �����Ѵ�.
	curPosInDst = 1;

	// colIdx�� 0������ src[0].colIdx - 1 ���� �����ϸ鼭
	// ���� ���� colIdx�� ���� colIdx�� ���� ���Ҹ� ã�Ƽ� dst�� �����Ѵ�. 
	for(colIdx = 0; colIdx < src[0].colIdx; colIdx++) {
		for(eleIdx = 1; eleIdx <= src[0].value; eleIdx++) { /* note: 1���� ���� value���� ����. 0�� row ���� ���� �뵵�� ���� */
			if(src[eleIdx].colIdx == colIdx) { // ���� ������ colIdx�� ���� colIdx�� ���� src ���Ұ� ������ dst�� ����.
				dst[curPosInDst].colIdx = src[eleIdx].rowIdx;
				dst[curPosInDst].rowIdx = src[eleIdx].colIdx;
				dst[curPosInDst].value = src[eleIdx].value;
				curPosInDst++;
			}
		}
	}

	// �׽�Ʈ �ڵ�
	if( (curPosInDst-1) != src[0].value) {
		printf("src�� ��� ���Ұ� dst�� ������� ����\n");
		return -2; // transpose ���� ����: -2
	}

	return 0; // ���� �Ϸ�
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

	// source�� ����Ÿ�� ���ų� destination �޸� ������ ������ -1�� return�Ѵ�.
	if(!src || !dst) return -1; // �Է� ����: -1

	// row ����, col ����, 0�� �ƴ� ���� ������ Ȯ���Ѵ�.
	rowNum = src[0].rowIdx;
	colNum = src[0].colIdx;
	eleNum = src[0].value;

	// dst[0]�� row ����, col ����, 0�� �ƴ� ���� ������ �����Ѵ�.
	dst[0].rowIdx = colNum; // src�� ���� ������ dst�� ���� ������ �ȴ�.
	dst[0].colIdx = rowNum; // src�� ���� ������ dst�� ���� ������ �ȴ�.
	dst[0].value = eleNum; // 0�� �ƴ� ������ ������ src�� dst�� ����. �ֳ��ϸ�, src�� ��� ���Ҹ� �����ϱ� �����̴�. 

	// ������ ������ 0�̸� �� �̻� ������ �ʿ� ����
	if(eleNum == 0)
		return 0; // �������� �Ϸῡ �ش��.

	// �ະ�� src sparse_matrix�� 0�� �ƴ� ���Ұ� �� �������� �����ϱ� ���� ���� �Ҵ� 
	eleNumOfEachCol = (int *)malloc(sizeof(int)*colNum);
	if(!eleNumOfEachCol)
		return -2; // �޸� �Ҵ� ����.
	
	// �ະ�� dst sparse_matrix�� 0�� �ƴ� ���Ұ� ��ġ�ϴ� ���� �� ù ��° ��ġ�� �����ϱ� ���� ���� �Ҵ�
	startPosOfEachCol = (int *)malloc(sizeof(int)*colNum);
	if(!startPosOfEachCol) {
		free(eleNumOfEachCol);
		return -3; // �޸� �Ҵ� ����
	}

	// �Ҵ��� �޸� �ʱ�ȭ
	for(colIdx = 0; colIdx < colNum; colIdx++) {
		eleNumOfEachCol[colIdx] = 0;
		startPosOfEachCol[colIdx] = 0;
	}

	// src�� ��� ���Ҹ� scan�ϸ鼭 col���� �� ���� ���Ұ� �ִ��� Ȯ��
	for(eleIdx = 1; eleIdx <= eleNum; eleIdx++) // eleIdx = 0�� ������ ���� ���� ���� �����ϴ� ���̹Ƿ� 1���� �����Ѵ�. eleNum�� ���� ���� �� ������ �����ؾ� ��.
		eleNumOfEachCol[src[eleIdx].colIdx]++;

	// eleNumOfEachCol[]�� scan�ϸ鼭 dst���� �����ϴ� ��ġ�� ����Ѵ�.
	//		dst�� ù ��° ���Ҵ� Ư���� �뵵�� ���ǰ� ������ �� �뵵�� ���� ����, ���� ����, 0�� �ƴ� ������ ������ �����ϰ� �ִ�.
	//		����, 0 column�� ���� ��ġ�� dst�� 1��° ��ġ�� �����Ѵ�.
	// 0�� column�� ���� ��ġ�� ������ �������Ƿ� �Ʒ��� for-loop�� 1������ �����Ѵ�.
	startPosOfEachCol[0] = 1;
	for(colIdx = 1; colIdx < colNum; colIdx++)
		startPosOfEachCol[colIdx] = startPosOfEachCol[colIdx - 1] + eleNumOfEachCol[colIdx - 1];

	// src�� element���� scan�ϸ鼭
	// �� ������ colIdx�� startPosOfEachCol[colIdx]�� �̿��Ͽ� ���Ұ� dst���� ��ġ�� ���� ��ġ�� �����Ѵ�.
	for(eleIdx = 1; eleIdx <= eleNum; eleIdx++) { // 0���� Ư�� �뵵�̹Ƿ� 1������ �����Ѵ�.

		// src element�� colIdx�� �̿��ؼ� �� element�� dst�� �� ��° ��ġ�� ����� ���� startPosOfEachCol[]�� �̿��ؼ� ������.
		posInDst = startPosOfEachCol[src[eleIdx].colIdx];

		dst[posInDst].colIdx = src[eleIdx].rowIdx;
		dst[posInDst].rowIdx = src[eleIdx].colIdx;
		dst[posInDst].value = src[eleIdx].value;

		// ���� ���� ������ colIdx�� ���Ұ� ���� �� dst���� ����� ��ġ�� ����
		startPosOfEachCol[src[eleIdx].colIdx]++;
	}

	free(startPosOfEachCol);
	free(eleNumOfEachCol);

	return 0;
}

//
// matrix���� startEldIdx���� �����ؼ� matrix[startEleIdx].rowIdx�� ���� ���� ������ ���Ҹ� ã�Ƽ� return�Ѵ�.
//
int	findEndIdxWithEqualRowIdx(sparse_matrix_t *matrix, int startEleIdx)
{
	int	endEleIdx = startEleIdx;

	while( (endEleIdx + 1) <= matrix[0].value && matrix[endEleIdx+1].rowIdx == matrix[startEleIdx].rowIdx) endEleIdx++;
	
	return endEleIdx;
}

//
// �� �� vector�� inner product (����)�� ���Ѵ�.
// 3���� ������ ��� (x1, y1, z1)�� (x2, y2, z2)�� ������ x1y2 + x2y2 + z1z2�̴�.
// matrixA x matrixB�� ���ϱ� ���ؼ� matrixA�� matrixBT�� �� ���� ���ͷ� ó���ؼ� ���� ��
// �� ������ ���� colIdx�� ���� �ͳ��� ���ϰ� �ȴ�.
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
	sparse matrix�� ����
	C = A x B
*/
int	sparse_matrix_multi(sparse_matrix_t *matrixC, sparse_matrix_t *matrixA, sparse_matrix_t *matrixB)
{
	int	curEleIdxOfC;
	int startEleIdxOfA, endEleIdxOfA;
	int	startEleIdxOfBT, endEleIdxOfBT;
	int	eleValueOfC;
	sparse_matrix_t	*matrixBT;

	matrixC[0].rowIdx = matrixA[0].rowIdx; // ���� ����� ��(row) ����
	matrixC[0].colIdx = matrixB[0].colIdx; // ���� ����� ��(column) ����
	matrixC[0].value = 0; // ���� ����� 0�� �ƴ� ���� ����
	curEleIdxOfC = 1; // sparse_matrix_t �迭�� ���� ����

	matrixBT = (sparse_matrix_t *)malloc(sizeof(sparse_matrix_t)*(matrixB[0].value + 1)); // transpose ������ �޸� ����
	if(sparse_matrix_fast_transpose(matrixBT, matrixB)) { // matrix transpose ����
		free(matrixBT);
		return -1; // transpose ����
	}

	startEleIdxOfA = matrixA[1].rowIdx; // matrixA�� ù ��° ������ �� ��ȣ
	do {
		endEleIdxOfA = findEndIdxWithEqualRowIdx(matrixA, startEleIdxOfA); // ������ �� ��ȣ�� ���� ������ ���� ��ġ

		startEleIdxOfBT = 1; // matrixBT�� ù ��° ������ �� ��ȣ
		eleValueOfC = 0; // matrixC�� ������ ���� ��(c_ij = a_ik * b_kj) �ʱ�ȭ 
		do {
			endEleIdxOfBT = findEndIdxWithEqualRowIdx(matrixBT, startEleIdxOfBT); // matrixBT�� ù ��° ������ �� ��ȣ

			// c_ij ����ϴ� �κ�
			eleValueOfC = vectorInnerProduct(matrixA, startEleIdxOfA, endEleIdxOfA, matrixBT, startEleIdxOfBT, endEleIdxOfBT); // �� ���� ���� ����. colIdx�� ���� ��츸 ���ؼ� ����.
		
			if(eleValueOfC != 0) { // 0�� �ƴϹǷ� matrixC�� ����
				matrixC[curEleIdxOfC].rowIdx = matrixA[startEleIdxOfA].rowIdx; // ����Ǵ� ������ rowIdx�� matrixA ������ rowIdx
				matrixC[curEleIdxOfC].colIdx = matrixBT[startEleIdxOfBT].rowIdx; // ����Ǵ� ������ colIdx�� matrixBT ������ rowIdx
				matrixC[curEleIdxOfC].value = eleValueOfC; // sum(a_ik * b_kj) ����
				curEleIdxOfC++; // ���� ���� ������ ��ġ ����
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