 
//注意: 此处将ElemType当作数字处理, 不考虑其他数据类型
//	链表需设置头结点, 不考虑头结点存储的数据
//	头结点为链表中第0个结点

typedef struct LNode{
	ElemType data;
	struct LNode* next;
}LNode;

int InitList(LNode* L, int size);
void DestroyList(LNode* L);
int ListLength(LNode* L);
LNode* GetElem(LNode* L, int i, ElemType* e);
LNode* LocateElem(LNode* L, ElemType e);
LNode* PriorElem(LNode* L, ElemType cur_e, ElemType* pre_e);
LNode* ListAmend(LNode* L, ElemType e, ElemType e1);
LNode* ListInsert(LNode* L, int i, ElemType e);
LNode* ListDelete(LNode* L, int i, ElemType* pe);
void PrintList(LNode* L);
void PrintListX(LNode* L);
LNode* MergeList(LNode* La, LNode* Lb);
void SortList(LNode* L);
int MessList(LNode* L);
void ReverseList(LNode* L);
int CloneList(LNode* Ln, LNode* L);
int ListTraverse(LNode* L, int (*visit)(ElemType*));
int fprintList(LNode* L, char* filename, char* openmode);
int fscanList(LNode* L, char* filename, char* openmode);

int InitList(LNode* L, int size);
/*	初始化一个链表, 为其分配size个结点空间
	参数:
		size:(size>=0). size>0时, 可用 ListTraverse 设置头结点外所有结点的值
	注意:
		新定义的链表必须先初始化, 初始化可以使用 InitList(&L, 0);
*/
void DestroyList(LNode* L);
/*	销毁一个链表
*/
int ListLength(LNode* L);
/*	返回链表的结点个数(不包括头结点)
*/
LNode* GetElem(LNode* L, int i, ElemType* e);
/*	此函数获取链表第i个结点的数据, 并将其存储到e中,
	参数:
		i: 指定目标结点的位置, i=0时将指定头结点
			i<0或i>ListLength(L)时将返回NULL
		e: 用来接受第i个结点的数据,
			如果不需要接受数据, 则e可以为NULL
	返回指:
		返回指向链表中第i个结点的指针
*/
LNode* LocateElem(LNode* L, ElemType e);
/*	此函数在链表L中查找数据e
	返回第一个所存储数据等于e的结点的地址
	如果没有找到, 则返回NULL
*/
LNode* PriorElem(LNode* L, ElemType cur_e, ElemType* pre_e);
/*	若链表中的有存储cur_e数据的结点, 则用pre_e返回第一个cur_e的前驱存储的数据
	参数:
		pre_e: 返回cur_e的前驱存储的数据,
			如果不需要返回前驱的数据, 则pre_e可以为NULL
	返回值:
		此函数返回指向cur_e前驱的指针
		如果cur_e为第一个结点, 将返回头结点的地址
		如果链表中没有cur_e, 则返回NULL
*/
LNode* ListAmend(LNode* L, ElemType e, ElemType e1);
/*	此函数将链表中第一个e修改为e1
	并返回指向e所在结点的指针
	如果链表中没有e, 将返回NULL
*/
LNode* ListInsert(LNode* L, int i, ElemType e);
/*	此函数自动为e分配一个结点的空间
	并将其插入到链表中第i个结点位置
	1<=i && i<=ListLength(L)+1
	i的值非法时返回NULL
*/
LNode* ListDelete(LNode* L, int i, ElemType* pe);
/*	此函数删除链表中第i个结点, 并用pe返回删除结点的数据
	参数:
		i : 指定删除结点的位置, 1<=i && i<=ListLength(L)
		pe: 接受删除结点的数据, 
			如果不需要接受删除结点的数据, 则pe可以为NULL
	返回值:
		返回删除结点的前驱的地址, 删除第一个结点时 返回头结点地址
		如果i值非法, 则返回NULL
*/
void PrintList(LNode* L);
/*	输出链表数据
*/
void PrintListX(LNode* L);
/*	输出链表数据, 并且输出next指针的值
*/
LNode* MergeList(LNode* La, LNode* Lb);
/*	合并链表 La, Lb
	返回合并后的头结点地址
	若合并前La, Lb 从小到大排列
		则合并后的链表依旧从小到大排列
*/
void SortList(LNode* L);
/*	采用归并排序法对链表进行排序
	(从小到大排序)
	可用ReverseList函数倒置链表实现从大到小排序
*/
int MessList(LNode* L);
/*	打乱链表顺序
	成功返回0, 失败返回-1
*/
void ReverseList(LNode* L);
/*	倒置链表
*/
int CloneList(LNode* Ln, LNode* L);
/*	开辟空间创建新表Ln 克隆L的所有数据
	成功返回0, 失败返回-1
*/
int ListTraverse(LNode* L, int (*visit)(ElemType*));
/*	此函数 依次对L的每个数据调用visit函数, 
	一但visit返回非0值, 则此函数立即返回visit返回的非零值
	参数:
		visit: 一个 int (*visit)(ElemType*) 型函数
	例:
		int visit(ElemType* e)
		{
			*e=*e*2+1;
			if(*e<0)
				return -1;
			return 0;
		}
		ListTraverse(&L, &visit)会依次将链表中的数据乘以2再加1
		如果遇到数据乘以2再加1后小于0, ListTraverse立即返回-1
*/
int fprintList(LNode* L, char* filename, char* openmode);
/*	将链表输出到文件中, 数据之间以空格间隔, 不输出换行符
	参数:
		filename: 指向字符串的指针, 指定输出文件的路径与文件名
		openmode: 指向字符串的指针, 指定打开文件的方式, 可以为 "w" "wb" 或 "a" "ab"
			注意: wb, ab 为以二进制形式输出到文件
	返回值:
		-520: 成功
		其他值: 失败
*/
int fscanList(LNode* L, char* filename, char* openmode);
/*	从文件中读取数据, 数据之间需以空格间隔. 
	参数:
		filename: 指向字符串的指针, 指定读取文件的路径与文件名
		openmode: 指向字符串的指针, 指定打开文件的方式, 可以为 "r" 或 "rb"
			慎用 "rb"
	返回值:
		-520: 成功
		其他值: 失败
	注意:
		若链表中有数据, 此函数不会覆盖原有数据,
		读取到的数据会追加到原有数据后面
		读取过程此函数会根据需要自动增加链表结点
		可以使用PrintListX输出链表数据及地址信息
*/



