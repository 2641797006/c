#ifndef _PMATRIX_H_
#define _PMATRIX_H_

#ifndef _INC_STDLIB
#include <stdlib.h>
#ifndef _INC_STDLIB
#define _INC_STDLIB
#endif
#endif

int __MATRIX__;

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

int InverseNum(int* a, int n)
{
	int *p, *q, *t=a+n-1, num=0;
	for(p=a+1;p<=t;p++)
		for(q=a;q<p;q++)
			if(*q>*p)
				num++;
	return num;
}

float DetValue(MATRIX* mat)
{
	float** bp=mat->bp;
	double det=0, product;
	int order=mat->row;
	if(mat->col!=order){
		__MATRIX__=-1;
		return 0;
	}
	int arr[order+2], *a=arr+1, *t=a+order-1, *p, *q, i, x=0x2, y=0, z;
	for(p=a;p<=t;p++)
		*p=p-a;
	arr[0]=-1;
	a[order]=-1;
	int NextOrdinal()
	{
		p=t;
		while(*p<*--p);
		if(p<a)
			return -1;
		q=p;
		while(*++q>*p);
		i=*--q, *q=*p, *p=i;
		p++, q=t;
		while(p<q)
			i=*p, *p++=*q, *q--=i;
	}
	do{
		for(p=a,product=1,i=0; p<=t; p++,i++)
			product*=*(*(bp+i)+*p);
#ifndef _PQUICK_
		if(InverseNum(a, order)%2==0)
#else
		if(z=(x+=1)&0x2, y++, y>=0x18 ? (x = (y=0, x>0x19) ? 0 : 2) : 0, z)
#endif
			det+=product;
		else
			det-=product;
	}while(NextOrdinal()>=0);
	__MATRIX__=0;
	return (float)det;
}













#endif