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

#if TEMPLATE_SPARSE_MATRIX

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
	//
	//                                   ä�� �κ�
	//

	if(src[0].value == 0)
		return 0; // ������ ������ 0�̹Ƿ� �� �̻� ������ �ʿ� ���� return. �������� �Ϸῡ �ش��.

	// dst�� 0���� ���� ����, ���� ����, 0�� �ƴ� ���� ���� ���� �����ϹǷ� ������ ���� ������ 1������ �����ϵ��� �����Ѵ�.
	// ä�� �κ�
	
	// colIdx�� 0������ src[0].colIdx - 1 ���� �����ϸ鼭
	// ���� ���� colIdx�� ���� colIdx�� ���� ���Ҹ� ã�Ƽ� dst�� �����Ѵ�. 
	//
	//
	//
	//                                   ä�� �κ�
	//
	//

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
	//
	//                        ä�� �κ�
	//

	// dst[0]�� row ����, col ����, 0�� �ƴ� ���� ������ �����Ѵ�.
	//
	//                        ä�� �κ�
	//

	// ������ ������ 0�̸� �� �̻� ������ �ʿ� ���� return�Ѵ�
	//
	//                        ä�� �κ�

	// �ະ�� src sparse_matrix�� 0�� �ƴ� ���Ұ� �� �������� �����ϱ� ���� ���� �Ҵ�
	//
	//                        ä�� �κ�
	
	// �ະ�� dst sparse_matrix�� 0�� �ƴ� ���Ұ� ��ġ�ϴ� ���� �� ù ��° ��ġ�� �����ϱ� ���� ���� �Ҵ�
	//
	//                        ä�� �κ�
	//

	// �Ҵ��� �޸� �ʱ�ȭ
	//
	//                        ä�� �κ�
	//

	// src�� ��� ���Ҹ� scan�ϸ鼭 col���� �� ���� ���Ұ� �ִ��� Ȯ��
	//
	//                        ä�� �κ�
	//

	// eleNumOfEachCol[]�� scan�ϸ鼭 dst���� �����ϴ� ��ġ�� ����Ѵ�.
	//		dst�� ù ��° ���Ҵ� Ư���� �뵵�� ���ǰ� ������ �� �뵵�� ���� ����, ���� ����, 0�� �ƴ� ������ ������ �����ϰ� �ִ�.
	//		����, 0 column�� ���� ��ġ�� dst�� 1��° ��ġ�� �����Ѵ�.
	// 0�� column�� ���� ��ġ�� ������ �������Ƿ� �Ʒ��� for-loop�� 1������ �����Ѵ�.
	//
	//                        ä�� �κ�
	//

	// src�� element���� scan�ϸ鼭
	// �� ������ colIdx�� startPosOfEachCol[colIdx]�� �̿��Ͽ� ���Ұ� dst���� ��ġ�� ���� ��ġ�� �����Ѵ�.
	//
	//
	//
	//
	//
	//                        ä�� �κ�
	//
	//
	//
	//
	//

	// �Ҵ��� �޸𸮸� free�Ѵ�.
	//
	//                        ä�� �κ�
	//

	return 0;
}

//
// matrix���� startEldIdx���� �����ؼ� matrix[startEleIdx].rowIdx�� ���� ���� ������ ���Ҹ� ã�Ƽ� return�Ѵ�.
//
int	findEndIdxWithEqualRowIdx(sparse_matrix_t *matrix, int startEleIdx)
{
	int	endEleIdx = startEleIdx;

	//
	//               ä�� �κ�
	//
	//

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

	//
	//
	//
	//                             ä�� �κ�
	//
	//
	//

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

	// matrixC�� 0��° �迭 ������ ���� �ʱ�ȭ�Ѵ�.
	//
	//                         ä�� �κ�
	//

	// parse_matrix_t �迭�� ���� ������ �ʱ�ȭ�Ѵ�.
	//                         ä�� �κ�

	// matrixBT�� ���� �޸𸮸� �����Ҵ��ϰ� fast_transpose()�� �����Ѵ�.
	//
	//
	//                         ä�� �κ�
	//
	//


	// matrixA�� ���� ã�� ������ �����Ѵ�.
	//     ���� �ȿ��� matrixBT�� ���� ã�� ������ �����Ѵ�.
	//           2�� ���� �ȿ��� �� ���� ���� ���ͷ� �����ؼ� ������ ���� �� ������� matrixC[curEleIdxOfC]�� �����Ѵ�.
	//
	//
	//
	//
	//
	//           ���� �˰����� �����ؼ� ä�� �κ�
	//
	//
	//
	//
	//
	//

	matrixC[0].value = curEleIdxOfC - 1; 

	// �Ҵ��� �޸𸮸� free�Ѵ�.
	//
	//                ä�� �κ�

	return 0;
}


#endif // TEMPLATE_SPARSE_MATRIX