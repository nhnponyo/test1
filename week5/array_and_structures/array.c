/*
	작성자: 김동진
	작성일: 2013.03.31
	내용:
		동적으로 2차원 배열 메모리 할당하는 함수
	주요사항
		2차원 배열을 넘겨받은 함수에서 arr[rowIdx][colIdx]의 형태로 사용하려면
		포인터 배열을 이용한 2차원 배열의 동적 메모리 할당 기법을 사용하는 것이 좋음
*/

#include <stdlib.h>
#include "def.h"

#if !TEMPLATE_ARRAY

//
// 동적으로 2차원 배열 메모리 할당하는 코드
//
int **make2DArray(int rowNum, int colNum)
{
	int **intArr;
	int	rowIdx;

	// row 개수만큼 int 배열의 시작 주소를 저장하는 공간 생성
	intArr = (int **)malloc(sizeof(int *)*rowNum);

	// 메모리 할당 실패 시 return;
	if(!intArr)
		return (int **)NULL;

	for(rowIdx = 0; rowIdx < rowNum; rowIdx++) {

		// 각 row별로 colNum 개수만큼 int 배열 생성
		intArr[rowIdx] = (int *)malloc(sizeof(int)*colNum);

		/*
		// 메모리 할당 실패에 대한 방어 코드
		// C언어 초보자의 경우 이 부분은 무시하고 지나가도 무방함.
		if(intArr[rowIdx] == (int *)NULL) {
			int	tmpIdx;
			for(tmpIdx = 0; tmpIdx < rowIdx - 1; tmpIdx++) {
				// 할당된 row의 1차원 배열 메모리 해제
				free(intArr[rowIdx]);
			}

			// 1차원 배열의 시작 주소들을 저장하는 포인터 배열 메모리 해제
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