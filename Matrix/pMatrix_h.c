//矩阵结构体
typedef struct{
	int row;	//行 0~m
	int col;	//列 0~n
	double** bp;	//基址指针
}MATRIX;
/*
 * 以行序为主
 * 为每一行单独分配空间
 * 并将每行首地址按顺序放在一个数组中
 * bp为该数组首地址
 */

int InitMatrix(MATRIX* mat, int row, int col);
void DestroyMatrix(MATRIX* mat);
void PrintMatrix(MATRIX* mat);
int MatrixTraverse(MATRIX* mat, int (*visit)(double*, int, int));
int InverseNum(int* a, int n);
double DetValue(MATRIX* mat);
MATRIX* TransposeMatrix(MATRIX* mat, MATRIX* rmat);
MATRIX* CofactorMatrix(MATRIX* mat, int row, int col, MATRIX* rmat);
MATRIX* CloneMatrix(MATRIX* mat);
void MatrixAdd(MATRIX* m1, MATRIX* m2);
void MatrixSub(MATRIX* m1, MATRIX* m2);
MATRIX* MatrixMul(MATRIX* m1, MATRIX* m2);
MATRIX* AdjointMatrix(MATRIX* mat);
MATRIX* InverseMatrix(MATRIX* mat);

int InitMatrix(MATRIX* mat, int row, int col);
/*	初始化矩阵mat, 为矩阵分配空间
	参数:
		mat: 指向MATRIX矩阵结构的指针
		row: 矩阵的行数 row>=1
		col: 矩阵的列数 col>=1
	返回值:
		成功返回0,
		失败返回-1或大于0的值
			-1: 为基址分配数组空间失败
			大于0: 为第i行分配空间失败时返回i(i>=1)
*/

void DestroyMatrix(MATRIX* mat);
/*	销毁矩阵
	释放为矩阵分配的空间
*/

void PrintMatrix(MATRIX* mat);
/*	输出矩阵
*/

int MatrixTraverse(MATRIX* mat, int (*visit)(double*, int, int));
/*	用提供的visit函数访问mat矩阵的每一行
	visit(p, row, col)参数:
		p: 指向第row行的指针 row>=0;
		row: 当前第几行, 从0开始
		col: 矩阵总列数
	visit返回0则继续visit下一行, 否则本函数返回visit函数返回的非0值
*/

int InverseNum(int* a, int n);
/*	计算整形数组的逆序数
	本文件中其他函数均未使用此函数或算法
*/

double DetValue(MATRIX* mat);
/*	返回方阵的行列式值
	算法时间复杂度极大 O(n!)
	空间复杂度 O(n)
	n为方阵阶数
*/

MATRIX* TransposeMatrix(MATRIX* mat, MATRIX* rmat);
/*	转置矩阵
	参数:
		mat: 要计算的矩阵
		rmat: 用来返回转置矩阵的矩阵
			当rmat为NULL时, 生成一个新矩阵来返回
*/

MATRIX* CofactorMatrix(MATRIX* mat, int row, int col, MATRIX* rmat);
/*	余子式
	参数:
		mat: 要计算的矩阵
		row: 余子式元所在行 row>=1
		col: 余子式元所在列 col>=1
		rmat: 用来返回余子式的矩阵
			当rmat为NULL时, 会生成一个新矩阵来返回
*/

MATRIX* CloneMatrix(MATRIX* mat);
/*	克隆矩阵
	为新矩阵分配空间, 并复制mat的数据
	失败返回NULL, 成功返回克隆矩阵指针
*/

void MatrixAdd(MATRIX* m1, MATRIX* m2);
/*	矩阵相加
	m1=m1+m2
*/

void MatrixAdd(MATRIX* m1, MATRIX* m2);
/*	矩阵相减
	m1=m1-m2
*/

MATRIX* MatrixMul(MATRIX* m1, MATRIX* m2);
/*	矩阵乘法
	生成新矩阵来返回m1*m2
	注意:
		m1的列数必须与m2的行数相等
	失败返回NULL, 成功返回新矩阵指针
*/

MATRIX* AdjointMatrix(MATRIX* mat);
/*	伴随矩阵
	生成新矩阵来返回mat的伴随矩阵
	矩阵mat需为方阵
	失败返回NULL
*/

MATRIX* InverseMatrix(MATRIX* mat);
/*	逆矩阵
	生成新矩阵来返回mat的逆矩阵
	若mat为奇异矩阵, 返回NULL
	计算失败返回NULL
	成功返回新矩阵指针
*/






















