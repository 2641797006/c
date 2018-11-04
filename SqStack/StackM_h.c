/* 通用栈, C语言, 64bit,
	注意:	要使用此通用栈, 请务必调用 InitStack() 初始化栈,
		然后才能进行 push/pop 等操作
	push(value); 压栈数据value可以是char,int,double等类型值或指针, 也可以是一个任意大小的结构体
	pop(address); 根据address的类型确定出栈字节数, 注意与push(value)对应

	#对于"浮点数"以外的基本类型: char, short, int/long, long long等
		push(value),pop(address), value,address类型可以不对应
		会对高字节进行补0, 或舍去高字节部分
		例: char c=0x61; int a=0x74737271;
		一:	push(c); pop(&a);
				从c到a: 压栈数据长度不足, a的高字节将为0, 结果a=0x61, c=0x61;
		二:	push(a); pop(&c);
				从a到c: 原压栈数据int类型a的值高字节部分将舍去, 结果a=0x74737271, c=0x71;

*/

int InitStack();
int push(value);
int pop(address);
int GetTop(address);
void PrintStack();

QWORD* GetTopP();
void SetTopP(void* p);

void ClearStack();
void DestroyStack();
int StackEmpty();
int StackLength();

int InitStack();
/*	请调用且仅调用一次此函数
	此函数初始化栈
	成功返回0, 失败返回-1
*/

int push(value);
/*	将value压栈,
	value:
		value可以是立即数, char,int,double等类型值或指针, 也可以是一个任意大小的结构体
	成功返回0, 失败返回-1
	一般不会出错, (进行大量压栈时可能因为申请内存失败而失败)
	一般情况可以不检查错误
*/

int pop(address);
/*	根据提供的地址address进行出栈, 
	注意:
		pop应与push对应
	成功返回0, 失败返回-1
	一般不会出错,
	(当栈内没有数据, 或者数据大小不够address类型时不会进行出栈操作, 此时返回-1)
	一般情况可以不检查错误
*/

int GetTop(address);
/*	获取栈顶数据到address地址处
	此函数与 pop(address) 类似
	但此函数不会移动栈顶指针
*/

void PrintStack();
/*	形象地输出栈
*/

/***************************************************/

QWORD* GetTopP();
/*	获取栈顶指针
	示例: QWORD* bp=GetTopP();
*/

void SetTopP(void* p);
/*	设置栈顶指针
	可与 GetTopP() 联合使用
		使执行某些代码后栈指针不变
	QWORD* bp=GetTopP();
	DoOtherThing();
	SetTopP(bp);
*/

/***************************************************/

void ClearStack();
/*	此函数将栈长度设置为0
	不会撤销分配给栈的空间
*/

void DestroyStack();
/*	此函数销毁栈
	销毁后 如要使用栈, 请使用InitStack()初始化栈
	可以不使用此函数
	如非必要 请不要使用此函数
	尽量使用 ClearStack() 代替使用此函数
*/

int StackEmpty();
/*	检查栈是否为空
	栈空返回1
	否则返回0
*/

int StackLength();
/*	返回栈长度
*/

//如果发现任何错误, 可以点击页面右上方联系我们










