int InitStack();
void push(value);
void pop(address);

int InitStack();
/*	调用且仅调用一次此函数
	此函数初始化栈
	成功返回0, 失败返回-1
*/

void push(value);
/*	将value压栈,
	value:
		value可以是立即数, char,int,double类型值或指针, 也可以是一个结构体
	push失败将设置全局变量 push_err为-1, (push_err初始值为0)
	push成功不会设置push_err的值
*/

void pop(address);
/*	根据提供的地址出栈, 注意与push对应
	pop失败将设置全局变量 pop_err为-1, (pop_err初始值为0)
	pop成功不会设置pop_err的值
*/

//如果发现任何错误, 可以点击页面右上方联系我们