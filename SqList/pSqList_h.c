 
//注意: 此处将ElemType当作数字处理, 不考虑其他数据类型

typedef struct{
	ElemType* elem;
	int length;
	int listsize;
}SqList;

int InitList(SqList* L, int size);
/*	此函数为顺序表分配空间
	参数:
		L: 指向SqList结构的指针
		size: 指定要为顺序表L分配的空间大小, 以 sizeof(ElemType) 为单位
	返回值:
		分配空间成功返回0, 否则返回-1
	注意:
		请仅用于首次为顺序表分配空间, 或者在DestroyList后使用
*/
int rInitList(SqList* L, int size);
/*	此函数调整顺序表分配的空间, 若size小于顺序表长度 则调整顺序表长度丢弃多余数据
	参数:
		L: 指向SqList结构的指针
		size: 指定调整顺序表的空间为 size 个 ElemType 大小, size>0
	返回值:
		调整分配空间成功返回0, 否则返回-1
	注意:
		请仅用于调整顺序表空间. 若首次为顺序表分配空间, 请使用InitList
		size需大于0, 若要清空顺序表空间 请使用DestroyList
*/
void DestroyList(SqList* L);
/*	此函数释放为顺序表分配的空间, 顺序表长度清零
	参数:
		L: 指向SqList结构的指针
	返回值:
		此函数不返回数据
	注意:
		清空顺序表后, 若要使用顺序表, 首次分配空间请使用InitList
*/
ElemType* LocateElem(SqList* L, ElemType e);
/*	此函数在顺序表中查找第一个与 e 相等的元素位置
	参数:
		L: 指向SqList结构的指针
		e: ElemType类型数值
	返回值:
		若找到一个与e相等的元素, 立即返回指向它的指针. 
		未找则到返回NULL
*/
ElemType* ListAmend(SqList* L, ElemType e, ElemType e1);
/*	此函数查找顺序表中第一个与 e 相等的元素, 并将其值修改为 e1
	参数:
		L: 指向SqList结构的指针
		e: ElemType类型数值
		e1: ElemType类型数值
	返回值:
		若找到一个与e相等的元素, 将它的值改为e1, 并返回指向它的指针. 
		未找则到返回NULL
*/
int ListInsert(SqList* L, int i, ElemType e);
/*	此函数在顺序表中添加元素, 若顺序表已满 则自动扩展顺序表空间
	参数:
		L: 指向SqList结构的指针
		i: 指定要插入数据的位置
		e: ElemType类型数值
	返回值:
		-1: 位置错误
		-2: 扩展空间失败
		0 : 添加元素成功
*/
int ListDelete(SqList* L, int i, ElemType* pea);
/*	此函数删除顺序表中的数据, 并通过pea返回删除的值. (此函数不会释放顺序表分配的空间)
	参数:
		L: 指向SqList结构的指针
		i: 指定要删除数据的位置
		pea: 指向ElemType类型数值的指针, 删除的数据将存储在pea指向的位置
	返回值:
		-1: 位置错误
		0 : 删除元素成功
*/
void PrintList(SqList* L);
/*	此函数输出顺序表, 数据之间以空格分隔, 仅在最末输出1个换行符
*/
void PrintListInfo(SqList* L);
/*	输出顺序表参数信息, 其中L->elem地址以十六进制输出
*/
void SortList(SqList* L);
/*	排序
	采用快速排序法为顺序表排序, 从小到大
	可以使用ReverseList倒置顺序表 实现从大到小排序
*/
int MessList(SqList* L);
/*	乱序
	采用随机算法生成100个随机数, 根据随机数来打乱顺序表的顺序
	返回值:
		-1: 失败
		0 : 成功
*/
void ReverseList(SqList* L);
/*	倒置顺序表
	可以使用SortList排序后再倒置 实现从大到小排序
*/
int CloneList(SqList* Ln, SqList* L);
/*	Ln需指向空的顺序表, L指向要克隆到Ln的顺序表
	此函数为Ln分配与L一样的空间, 并复制L的所有数据
	可以使用PrintListInfo输出顺序表参数信息
	返回值:
		-1: 失败
		0 : 成功
*/
int ListTraverse(SqList* L, int (*visit)(ElemType*));
/*	此函数 依次对L的每个数据元素调用函数visit函数, 
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
		ListTraverse(&L, &visit)会依次将顺序表中的元素乘以2再加1
		如果遇到元素乘以2再加1后小于0, ListTraverse立即返回-1
*/
int fprintList(SqList* L, char* filename, char* openmode);
/*	将顺序表输出到文件中, 数据之间以空格间隔, 不输出换行符
	参数:
		filename: 指向字符串的指针, 指定输出文件的路径与文件名
		openmode: 指向字符串的指针, 指定打开文件的方式, 可以为 "w" 或 "a"
			"w": 覆盖原文件  "a": 追加到文件末尾
	返回值:
		-520: 成功
		其他值: 失败
*/
int fscanList(SqList* L, char* filename, char* openmode);
/*	从文件中读取数据, 数据之间需以空格间隔. 
	参数:
		filename: 指向字符串的指针, 指定读取文件的路径与文件名
		openmode: 指向字符串的指针, 指定打开文件的方式, 可以为 "r" 或 "r"
	返回值:
		-520: 成功
		其他值: 失败
	注意:
		若顺序表中有数据, 此函数不会覆盖原有数据,
		读取到的数据会追加到原有数据后面
		读取过程此函数会根据需要自动扩展顺序表空间
		可以使用PrintListInfo输出顺序表参数信息
*/