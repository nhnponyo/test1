#include <stdio.h>

int main()
{
	//1d array 
	int a[5] = {1,3,5,7,10};

	//2d array
	int b[][4] = {1,2,3,4,5,6,7,8}; // [[1,2,3,4],[5,6,7,8]]
	int i,j;

	//print 1d array
	for(i=0;i<5; i++)
		printf("a %d: %d %p\n", i, a[i], &a[i]);

	//print 2d array
	for(i=0; i<2; i++)
		for(j=0; j<4; j++)
			printf("b %d %d: %d %p\n", i, j,b[i][j], &b[i][j]);
	return 0;
}
