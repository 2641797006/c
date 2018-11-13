
// 注意: 本文件使用了通用栈 SqStackX.h

int precede(char c);
int InfixToSuffix(char* infix, char* suffix);
double DealSuffix(char* suffix);

int precede(char c);
/*	返回运算符优先级
	参数c为运算符
	InfixToSuffix函数根据此优先级来处理中缀表达式
*/

int InfixToSuffix(char* infix, char* suffix);
/*	将中缀表达式转换为后缀表达式
	参数:
		infix: 中缀表达式字符串
		suffix: 存放生成的后缀表达式, 请保证该字符串长度足够
	返回值:
		成功返回0
		失败返回非0, 中缀表达式不规范可能导致处理失败
*/

double DealSuffix(char* suffix);
/*	计算后缀表达式, 返回计算结果
	请保证后缀表达式规范
*/