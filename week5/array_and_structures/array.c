/*
	�ۼ���: �赿��
	�ۼ���: 2013.03.31
	����:
		�������� 2���� �迭 �޸� �Ҵ��ϴ� �Լ�
	�ֿ����
		2���� �迭�� �Ѱܹ��� �Լ����� arr[rowIdx][colIdx]�� ���·� ����Ϸ���
		������ �迭�� �̿��� 2���� �迭�� ���� �޸� �Ҵ� ����� ����ϴ� ���� ����
*/

#include <stdlib.h>
#include "def.h"

#if !TEMPLATE_ARRAY

//
// �������� 2���� �迭 �޸� �Ҵ��ϴ� �ڵ�
//
int **make2DArray(int rowNum, int colNum)
{
	int **intArr;
	int	rowIdx;

	// row ������ŭ int �迭�� ���� �ּҸ� �����ϴ� ���� ����
	intArr = (int **)malloc(sizeof(int *)*rowNum);

	// �޸� �Ҵ� ���� �� return;
	if(!intArr)
		return (int **)NULL;

	for(rowIdx = 0; rowIdx < rowNum; rowIdx++) {

		// �� row���� colNum ������ŭ int �迭 ����
		intArr[rowIdx] = (int *)malloc(sizeof(int)*colNum);

		/*
		// �޸� �Ҵ� ���п� ���� ��� �ڵ�
		// C��� �ʺ����� ��� �� �κ��� �����ϰ� �������� ������.
		if(intArr[rowIdx] == (int *)NULL) {
			int	tmpIdx;
			for(tmpIdx = 0; tmpIdx < rowIdx - 1; tmpIdx++) {
				// �Ҵ�� row�� 1���� �迭 �޸� ����
				free(intArr[rowIdx]);
			}

			// 1���� �迭�� ���� �ּҵ��� �����ϴ� ������ �迭 �޸� ����
			free(intArr);
			
			return (int **)NULL;
		}
		*/
	}

	return intArr;
}

int	release2DArray(int **intArr, int rowNum)
{
	int	rowIdx;

	if(!intArr) return -1;

	for(rowIdx = 0; rowIdx < rowNum; rowIdx++)
		if(intArr[rowIdx]) free(intArr[rowIdx]);

	free(intArr);

	return 0;
}

#endif // !TEMPLATE