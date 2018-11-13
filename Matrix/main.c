#include <stdio.h>
#include <__pink/prand.h>
#include <C:\Users\26417\Desktop\Matrix\pMatrix.h>

#define ResetCin() ( stdin->_cnt=0, stdin->_ptr=stdin->_base )

void menu();
int choose(int n);
void ScanMatrix(MATRIX* mat);
int FormatMatrix(double* p, int row, int col);

int main()
{
	int i, j, fd=0, fa=0, fi=0;
	double det;
	MATRIX mat, *amat, *imat, *m, tempmat;
	amat=(MATRIX*)malloc(sizeof(MATRIX));
	imat=(MATRIX*)malloc(sizeof(MATRIX));
	InitMatrix(amat, 1, 1);
	InitMatrix(imat, 1, 1);
	InitMatrix(&mat, 5, 5);
	MatrixTraverse(&mat, &FormatMatrix);
	while(1)
	{
		menu();
		ResetCin();
		ungetc(' ', stdin);
		if( scanf("%*[^0-9a-zA-Z]%1[0-9a-zA-Z]", &i)<1 )
			continue;
		i=choose(i);
		switch(i)
		{
			case 'A':
				PrintMatrixS(&mat);
			break;
			case 'B':
				printf("请输入矩阵行数row: ");
				ResetCin();
				ungetc(' ', stdin);
				scanf("%*[^0-9]%d", &i);
				printf("请输入矩阵列数col: ");
				ResetCin();
				ungetc(' ', stdin);
				scanf("%*[^0-9]%d", &j);
				DestroyMatrix(&mat);
				InitMatrix(&mat, i, j);
				printf("请输入矩阵数据:\n");
				ScanMatrix(&mat);
				fd=0, fa=0, fi=0;
			break;
			case 'C':
				if(mat.row!=mat.col){
					printf("此矩阵不是方阵\n");
					break;
				}
				else if(!fd)
					det=DetValue(&mat), fd=1;
				printf("方阵行列式值为: %.32G\n", det);
			break;
			case 'D':
				if(mat.row!=mat.col){
					printf("此矩阵不是方阵\n");
					break;
				}
				else if(!fa){
					DestroyMatrix(amat);
					free(amat);
					amat=AdjointMatrix(&mat);
					fa=1;
				}
				printf("伴随矩阵:\n");
				PrintMatrixS(amat);
			break;
			case 'E':
				if(mat.row!=mat.col){
					printf("此矩阵不是方阵\n");
					break;
				}
				else if(!fi){
					DestroyMatrix(imat);
					free(imat);
					imat=InverseMatrix(&mat);
					fi=1;
				}
				printf("逆矩阵:\n");
				PrintMatrixS(imat);
			break;
			case 'F':
				printf("请输入乘数矩阵:\n行数row: ");
				ResetCin();
				ungetc(' ', stdin);
				scanf("%*[^0-9]%d", &i);
				printf("列数col: ");
				ResetCin();
				ungetc(' ', stdin);
				scanf("%*[^0-9]%d", &j);
				if(i!=mat.col){
					printf("这2个矩阵不能相乘\n");
					break;
				}
				InitMatrix(&tempmat, i, j);
				printf("请输入矩阵数据:\n");
				ScanMatrix(&tempmat);
				m=MatrixMul(&mat, &tempmat);
				printf("\n乘积矩阵:\n");
				PrintMatrixS(m);
				DestroyMatrix(&tempmat);
				DestroyMatrix(m);
				free(m);
			break;
			case 'G':
				printf("矩阵已转置\n");
				m=CloneMatrix(&mat);
				i=mat.row, j=mat.col;
				DestroyMatrix(&mat);
				InitMatrix(&mat, j, i);
				TransposeMatrix(m, &mat);
				PrintMatrixS(&mat);
				DestroyMatrix(m);
				free(m);
			break;
			case 'K':
				system("cls");
			break;
			case 'Q':
				return 0;
			break;
			case 'X':
				MatrixTraverse(&mat, &FormatMatrix);
				fd=0, fa=0, fi=0;
				printf("随机赋值\n");
			break;
			default:
				printf(">>>switch case::This option was not found!\n");
		}
	}
}

void menu()
{
	printf("\nA.输出矩阵  B.输入矩阵  C.行列式值  D.伴随矩阵  E.逆矩阵  F.矩阵相乘  G.转置矩阵  K.清屏  M.更多  Q.退出\n请选择: ");
}

int choose(int n)
{
	if(0x30<=n&&n<=0x39)
		n-=0x30;
	else if(0x41<=n&&n<=0x5a)
		n-=0x40;
	else if(0x61<=n&&n<=0x7a)
		n-=0x60;
	else
		n=-1;
	n+=0x40;
	printf(">>>检测到选项\'%c\'\n\n", n);
	return n;
}

void ScanMatrix(MATRIX* mat)
{
	int i, j;
	ResetCin();
	for(i=0;i<mat->row;i++)
		for(j=0;j<mat->col;j++)
			scanf("%lf", *(mat->bp+i)+j);
}

int FormatMatrix(double* p, int row, int col)
{
	int i, flag;
	for(i=0;i<col;i++,p++){
		flag=prand();
		*p = flag%2==0 ? flag%20 : -flag%20;
	}
	return 0;
}
