#ifndef _PMATRIX_H_
#define _PMATRIX_H_

#ifndef _INC_STDLIB
#include <stdlib.h>
#ifndef _INC_STDLIB
#define _INC_STDLIB
#endif
#endif

typedef struct{
	int row;
	int col;
	float** bp;
}MATRIX;

int InitMatrix(MATRIX* mat, int row, int col)
{
	int i;
	float** bp;
	bp=(float**)malloc(row*sizeof(float*));
	if(!bp)
		return -1;
	mat->bp=bp;
	for(i=0;i<row;i++){
		*(bp+i)=(float*)malloc(col*sizeof(float));
		if(!*(bp+i))
			return i+1;
	}
	mat->row=row;
	mat->col=col;
	return 0;
}

void DestroyMatrix(MATRIX* mat)
{
	int i, row;
	float** bp;
	row=mat->row;
	bp=mat->bp;
	for(i=0;i<row;i++)
		free(*(bp+i));
	free(bp);
}

void PrintMatrix(MATRIX* mat)
{
	int i, j, row, col;
	float **bp, *p;
	bp=mat->bp;
	row=mat->row;
	col=mat->col;
	for(i=0;i<row;i++){
		p=*(bp+i);
		for(j=0;j<col;j++)
			printf("%-8.6G ", *(p+j));
		printf("\n");
	}
}

int MatrixTraverse(MATRIX* mat, int (*visit)(float*, int, int))
{
	int i, row, ret;
	float **bp;
	bp=mat->bp;
	row=mat->row;
	for(i=0;i<row;i++){
		ret=visit(*(bp+i), i, mat->col);
		if(ret)
			return ret;
	}
	return 0;
}























#endif