#include <stdio.h>
#include <stdlib.h>


int main()
{
	int (*p)[100];
	int i,j;
	p =  calloc(200 , sizeof(int));
	p[1][50] = 10;
	printf("size of p: %d\n", sizeof(p));
	for (i=0; i < 2;  i ++)
	{
		for(j=0; j < 100; j++)
			printf("%d ", p[i][j]);
		printf("\n");
	}


	return 0;
}

