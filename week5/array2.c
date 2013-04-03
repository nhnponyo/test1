#include <stdio.h>
int main()
{
	//convert 2d array into int pointer
	//remember that a[15] = *(a+15) 
	int a[][2] = { {7}, {11,13}, {17,19} };
	int *p = (int*) a; //casting
  	//int **pp = (int**) a; //wrong

	int i,j;
	for (i= 0; i < 3; i++)
		for(j=0; j < 2; j++)
			printf("%d %d, %d: %d\n",i, j, i*2+j,*(p+i*2+j));
			//printf("%d %d, %d: %d\n",i, j, i*2+j,*(*(a+i)+j));
	return 0;
}
