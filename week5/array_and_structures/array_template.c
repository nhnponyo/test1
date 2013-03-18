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

#if TEMPLATE_ARRAY

//
// 동적으로 2차원 배열 메모리 할당하는 코드
//

int **make2DArray(int rowNum, int colNum)
{
	int **intArr;

	// 채워야 하는 부분
	//
	// 구현할 기능
	//		rowNum 크기의 포인터 배열을 malloc으로 할당한다.
	//		할당된 배열의 시작 주소를 intArr에 저장한다.
	//		intArr의 각 원소가 colNum 크기 배열의 시작 주소를 가리키도록 한다.
	//		이를 위해서 각 원소별로
	//			배열을 동적 생성
	//			생성된 주소의 시작 주소를 배열에 저장한다.

	return intArr;
}

#endif // TEMPLATE

