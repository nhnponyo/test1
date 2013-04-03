#include <stdio.h>
#include <stdlib.h>

int main()
{
	//2D array using int **
	int *d1, *d2;
	int **d;
	int i,j;

	//2d dynamic (1)
	d1=malloc(sizeof(int) * 4);
	d2=malloc(sizeof(int) * 4);
	for(i=0; i < 5; i++)
	{
		d1[i] = (i+1) ; 
		d2[i] = (i+1)*2 ; 
	}

	d = malloc(sizeof(int*) *2);
	d[0] = d1;
	d[1] = d2;

	for(i=0; i < 2; i++)
		for(j=0; j < 4; j++)
			printf("d %d %d: %d\n",i,j, d[i][j]);
	
	free(d1);
	free(d2);
	free(d);
	return 0;
}
