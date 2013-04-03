#include <stdio.h>

void printptr(int *p, int m, int n);
void printarr(int (*p)[3], int m);

int main()
{
	int arr[][3] = {{1},{0,1},{0,0,1},{0} }; //4x3 array
	//printptr((int*)arr, 4,3);
	printarr(arr, 4);
	return 0;
}

void printptr(int *p, int m, int n)
{
	int i,j;
	for(i=0; i < m ; i++)
	{
		for(j=0; j< n; j++)
			printf("%d ", *(p+i*n+j));
		printf("\n");
	}
}

void printarr(int (*p)[3], int m)
{
	int i,j;
	for(i=0; i < m ; i++)
	{
		for(j=0; j< 3; j++)
			printf("%d ",p[i][j]);
		printf("\n");
	}

}
