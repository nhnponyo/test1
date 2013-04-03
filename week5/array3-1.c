#include <stdio.h>
#include <stdlib.h>

int main()
{
	//1D dynamic alloc
	int *a;
	int i,n;
	printf("input size of array [1-n] ");
	scanf("%d",&n);


	//size 5 array
	a = malloc(n* sizeof(int) );
	for(i=0; i < n; i++)
		a[i] = (i+1) * 2; //2,4,6,8,10

	for(i=0; i < n; i++)
	{
		printf("a %d :%d\n",i, a[i], &a[i]);
	}

	free(a);
	return 0;
}
