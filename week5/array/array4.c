#include <stdio.h>
#include <stdlib.h>
//make m * n array and return it
int** make2Darray(int m, int n)
{
	int **p;
	int i,j;
	p = (int**) malloc(m* sizeof(int*));
	for(i=0; i < m; i++)
		p[i] = (int *) malloc(n * sizeof(int));
	return p;
}
void free2Darray(int **p, int m, int n)
{
	//implement 
}

int main()
{
	int **pa = make2Darray(5,4);
	int i, j;

	for(i=0; i < 5; i++)
		for(j=0; j< 4; j++)
			pa[i][j] = i*10+j;

	for(i=0; i < 5; i++)
	{
		for(j=0; j< 4; j++)
		{
			//printf("%02d ", *(*(pa+i)+j));
			printf("%02d ", pa[i][j]);
		}
		printf("\n");
	}
	free2Darray(pa,5,4);
	return 0;
}
