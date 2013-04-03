#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct 
{
	int row;
	int col;
	int val;
} spmat_t;
void print_spmat_t(spmat_t *mat);
void transpose(spmat_t *mat);

int main()
{
	spmat_t mat[] ={ {10,10,4},
		{0,0,1},
		{1,1,1},
		{2,5,2},
		{4,7,9}};

	spmat_t ans[5] = {0};

	int i;
/*
	for(i=0; i<5; i++)
		printf("%d %d %d\n",mat[i].row,mat[i].col,mat[i].val);
// */
	print_spmat_t(mat);
	return 0;
}

void print_spmat_t(spmat_t *mat)
{
	int m = mat[0].row;
	int n = mat[0].col;
	int count = mat[0].val;
	int idx=1, val;
	int i, j;
	for(i = 0; i < m ; i++)
	{
		for( j = 0; j < n; j++)
		{
			if(i== mat[idx].row && j== mat[idx].col)
			{
				val = mat[idx].val;
				idx++;
			}
			else val=0;
			printf("%d ",val);
		}
		printf("\n");
	}
	assert(count == (idx-2));
	
}

void transpose(spmat_t *mat, spmat_t *tran)
{
	int m = mat[0].row;
	int n = mat[0].col;
	int count = mat[0].val;
	tran[0].row = n;
	tran[0].col = m;
	tran[0].val = count;



