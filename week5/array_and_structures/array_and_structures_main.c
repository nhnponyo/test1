/*
   작성자: 김동진
   작성일: 2013.03.30
   주제: array와 structure 사용 예제
   상세 내용
       1. 2D array 사용예제
	   2. structure 사용 예제
	   3. typedef 사용 예제
	   4. matrices 사용 예제
*/

#include <stdio.h>

extern void testMake2DArray(void);
extern void	test2DArrayOfFixedSize(void);
extern void	testMatrixSum(void);
extern void	testMatrixMulti(void);
extern void	testMatrixTranspose(void);
extern void	testStructures(void);
extern void	testSelfReferentialStrucutures(void);
extern void	testRectangleStructures(void);
extern void test_sparse_matrix_transpose(void);
extern void test_sparse_matrix_fast_transpose(void);
extern void	test_sparse_matrix_multi(void);

int main(void)
{
	/*
	testMake2DArray();

	test2DArrayOfFixedSize();

	testMatrixSum();

	testMatrixMulti();

	testMatrixTranspose();

	testStructures();

	testSelfReferentialStrucutures();

	testRectangleStructures();
	*/

	// test_sparse_matrix_transpose();

	// test_sparse_matrix_fast_transpose();

	test_sparse_matrix_multi();

	return 0;
}