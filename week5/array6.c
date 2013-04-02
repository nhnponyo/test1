#include <stdio.h>

void printptr(int *p, int m, int n);
void printarr(int (*p)[3], int m);

int main()
{
	int arr[][3] = {{1},{0,1},{0,0,1},{0} };
	printptr((int*)arr, 4,3);
	printf("---------cut here--------\n");
	printarr(arr, 4);
	return 0;
}

#define ptr(p,i,j,n) *(p+i*n+j)
void printptr(int *p, int m, int n)
{
	int i,j;
	for(i=0; i < m ; i++)
	{
		for(j=0; j< n; j++)
			//printf("%d ", *(p+i*n+j));
			printf("%d ", ptr(p,i,n,j)); 
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
