#include <stdio.h>

typedef struct{
	char name[16];
	char ID[16];
	float grade[4];
	double average;
}STUDENT;

#define ElemType STUDENT
#include <C:/Users/26417/Desktop/ZY/zy2/LNodeM.h>

void menu();
int choose(int n);
void printelem(ElemType* pe);
int scanfelem(ElemType* pe, int i);
void stuave(ElemType* pe);


int main()
{
	int i;
	LNode L;
	STUDENT student;
	InitList(&L, 0);
	menu();
	ungetc('\n', stdin);
	while(1)
	{
		if( scanf("%*[^0-9a-zA-Z]%1[0-9a-zA-Z]%*[^\n]", &i)<1 )
			continue;
		i=choose(i);
		switch(i)
		{
			case 'A':
				if(ListLength(&L)<1)
					printf("线性表中没有数据\n");
				else
					PrintList(&L, &printelem);
			break;
			case 'B':
				scanfelem(&student, ListLength(&L)+1);
				stuave(&student);
				printelem(&student);
				ListInsert(&L, ListLength(&L)+1, &student);
			break;
			case 'C':
				DestroyList(&L);
				printf("线性表已清空\n");
			break;
			case 'D':
			{
				if(ListLength(&L)==0){
					printf("线性表中没有数据\n");
					break;
				}
				printf("请输入要删除的元素位置: ");
				scanf("%*[^0-9]%d%*[^\n]", &i);
				if( ListDelete(&L, i, NULL) )
					printf("位置错误: %d\n", i);
				else
					printf("已删除第%d个学生信息\n", i);
			}
			break;
			case 'E':
				if(ListLength(&L)==0){
					printf("线性表中没有数据\n");
					break;
				}
				printf("请输入要修改学生信息的序号: ");
				scanf("%*[^0-9]%d%*[^\n]", &i);
				if( i<1||i>ListLength(&L) )
					printf("序号错误\n");
				else{
					scanfelem(&student, i);
					CopyElem(GetElem(&L, i, NULL), &student);
					printf("已修改第%d个学生的信息\n", i);
				}
			break;
			case 'K':
				system("cls");
			break;
			case 'Q':
				DestroyList(&L);
				return 0;
			break;
			case 'U':
			{
				int num=0;
				LNode* p=&L;
				printf(">>>有60分以下学科的学生:\n");
				while(p=p->next)
					for(i=0;i<4;i++)
						if(p->data.grade[i]<60){
							num++;
							printelem(&p->data);
							break;
						}
				printf(">>>共%d个\n", num);
			}
			break;
			case 'V':
			{
				int num=0;
				LNode* p=&L;
				printf(">>>有90分以上学科的学生:\n");
				while(p=p->next)
					for(i=0;i<4;i++)
						if(p->data.grade[i]>=90){
							num++;
							printelem(&p->data);
							break;
						}
				printf(">>>共%d个\n", num);
			}
			break;
			default:
				printf(">>>Switch Case: This option was not found!\n");
		}
		menu();
	}
}


void menu()
{
	printf("\nA.输出  B.输入  C.清空  D.删除  E.修改  K.清屏  U.60分以下  V.90分以上  Q.退出\n请选择: ");
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

void printelem(ElemType* pe)
{
	printf("姓名: %s \n学号: %s \n成绩: %-5.3G %-5.3G %-5.3G %-5.3G \n平均分: %.6G\n\n",
		pe->name, pe->ID, pe->grade[0], pe->grade[1], pe->grade[2], pe->grade[3], pe->average);
}

int scanfelem(ElemType* pe, int i)
{
	printf("请输入第%d个学生的数据. \n>>>姓名: ", i);
	scanf("%*c%15[^\n]%*[^\n]", pe->name);
	printf(">>>学号: ");
	scanf("%*[^0-9a-zA-Z]%15[0-9a-zA-Z]%*[^\n]", pe->ID);
	printf(">>>四科成绩: ");
	scanf("%f %f %f %f", pe->grade, pe->grade+1, pe->grade+2, pe->grade+3);
	scanf("%*[^\n]");
	return 0;
}

void stuave(ElemType* pe)
{
	pe->average=(pe->grade[0]+pe->grade[1]+pe->grade[2]+pe->grade[3])/4.0;
}







