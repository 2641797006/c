//以下将ElemType作数字处理
#include <stdio.h>
#include <stdlib.h>
#include <c:/users/26417/desktop/datas/pSqList.h>

void menu();
void menux();
int choose(int n);
int ychoose(int n);
void pfname(char** pps);

int main(){
	int i;
	SqList L;
	menu();
	if( InitList(&L, 100) )
		printf("First init Error\n");
	for(i=0;i<100;i++)
		*(L.elem+i)=i;
	L.length=100;
	ungetc('\n', stdin);
	while(1)
	{
		if( scanf("%*[^0-9a-zA-Z]%1[0-9a-zA-Z]%*[^\n]", &i)<1 )
			continue;
		i=choose(i);
		i=ychoose(i);
		switch(i)
		{
			case 'A':
				if(L.length<1)
					printf("顺序表中没有数据\n");
				else
					PrintList(&L);
			break;
			case 'B':
				if( rInitList(&L, 100) )
					printf("Init Error\n");
				else{
					L.length=100;
					for(i=0;i<100;i++)
						*(L.elem+i)=i;
					PrintList(&L);
				}
			break;
			case 'C':
				DestroyList(&L);
				if( InitList(&L, 0) )
					printf("Error Code: 0x07ff\n");
				else
					printf("顺序表已清空\n");
			break;
			case 'D':
			{
				ElemType e;
				if(L.length==0){
					printf("顺序表中没有数据\n");
					break;
				}
				printf("请输入要删除的元素位置: ");
				scanf("%*[^0-9]%d%*[^\n]", &i);
				if( ListDelete(&L, i, &e) )
					printf("位置错误: %d\n", i);
				else
					printf("已删除第%d个元素%d\n", i, e);
			}
			break;
			case 'E':
			{
				int r;
				ElemType e;
				printf("请输入要增加元素的位置: ");
				scanf("%*[^0-9]%d%*[^\n]", &i);
				printf("然后输入新增元素的值: ");
				scanf("%*[^0-9]%d%*[^\n]", &e);
				r=ListInsert(&L, i, e);
				if(r==-1)
					printf("位置错误: %d\n", i);
				else if(r==-2)
					printf("内存错误, 增加元素失败\n");
				else
					printf("已在第%d位置插入元素%d\n", i, e); 
			}
			break;
			case 'F':
			{
				int num=0;
				SqList L1=L;
				ElemType* pe, e;
				printf("请输入要查找元素的值: ");
				scanf("%*[^0-9]%d%*[^\n]", &e);
				while(L1.length>0){
					pe=LocateElem(&L1, e);
					if(!pe)
						break;
					else{
						printf("第%d个, ", ++pe-L.elem);
						L1.length-=(pe-L1.elem);
						L1.elem=pe;
						num++;
					}
				}
				printf("共找到%d个\n", num);
			}
			break;
			case 'G':
			{
				ElemType e, e1;
				printf("请输入要修改的元素值: ");
				scanf("%*[^0-9]%d%*[^\n]", &e);
				printf("请输入新的元素值: ");
				scanf("%*[^0-9]%d%*[^\n]", &e1);
				if( !ListAmend(&L, e, e1) )
					printf("未找到值%d\n", e);
				else
					printf("已将一个%d改为%d\n", e, e1);
			}
			break;
			case 'H':
				printf("\n      <<更多菜单>>\n");
				menux();
				printf("\n");
			break;
			case 'K':
				system("cls");
			break;
			case 'M':
				if(L.length<1){
					printf("顺序表中没有数据\n");
					break;
				}
				if( MessList(&L) )
					printf("打乱顺序失败\n");
				else
					PrintList(&L);
			break;
			case 'N':
			{
				if(L.length<2){
					printf("顺序表中数据不超过一个\n");
					break;
				}
				ReverseList(&L);
				PrintList(&L);
			}
			break;
			case 'Q':
				DestroyList(&L);
				return 0;
			break;
			case 'R':
			{
				int r;
				char filename[512], openmode[8]="r", *ps=filename;
				printf("请将目标文件拖到这里||或输入目标文件名: ");
				pfname(&ps);
				r=fscanList(&L, ps, openmode);
				if(r!=-520)
					printf("Error: fscanList error code: %d\n", r);
			}
			break;
			case 'S':
				if(L.length<1){
					printf("顺序表中没有数据\n");
					break;
				}
				SortList(&L);
				PrintList(&L);
			break;
			case 'V':
			{
				if(L.length<1){
					printf("顺序表中没有数据\n");
					break;
				}
				ElemType* pe=L.elem+L.length-1, e;
				printf("请输入用来格式化顺序表的值: ");
				scanf("%*[^0-9]%d%*[^\n]", &e);
				while(pe>=L.elem)
					*pe--=e;
				PrintList(&L);
			}
			break;
			case 'W':
			{
				int r;
				char filename[512], openmode[8]="w", *ps=filename;
				printf("请将目标文件拖到这里||或输入目标文件名: ");
				pfname(&ps);
				r=fprintList(&L, ps, openmode);
				if(r!=-520)
					printf("Error: fprintList error code: %d\n", r);
			}
			break;
			case 'X':
			{
				if(L.length<1){
					printf("顺序表中没有数据\n");
					break;
				}
				int p, q;
				ElemType* pe=L.elem;
				for(i=0;i<L.length;i++){
					p=prand()%300/100;
					q=10*((p+9)/10*9+1)*((p+8)/10*9+1);
					*pe++=prand()%q;
				}
				PrintList(&L);
			}
			break;
			case 'Y':
				PrintListInfo(&L);
			break;
			case 'Z':
			{
				double v;
				printf("请输入数据,(非法输入结束): ");
				while( scanf("%Lf", &v)>0 ){
					if(v!=(int)v)
						break;
					if( ListInsert(&L, L.length+1, v) )
						printf("内存错误\n");
				}
				scanf("%*[^\n]");
			}
			break;
			default:
				printf("<<Switch Case>>: This option was not found!\n");
				printf("下面展开更多选项:\n\n");
				menux();
				printf("\n");
		}
		menu();
	}
}

void menu()
{
	printf("\nA.输出顺序表  B.初始化设置100个数据  C.clear清空  D.删除元素  E.添加元素  F.查找元素  G.修改元素  H.更多  Q.退出\n请选择: ");
}

void menux()
{
	printf("\
S.sort排序        M.mess乱序\n\
R.从文件读取数据  W.向文件输出数据\n\
X.随机赋值        V.全部元素赋值为\n\
Y.输出顺序表参数  N.倒置顺序表\n\
Z.手动输入顺序表");

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
	return n;
}

int ychoose(int n)
{
	n+=0x40;
	printf(">>>检测到选项\'%c\'\n\n", n);
	return n;
}

void pfname(char** pps)
{
		scanf("%*c%500[^\n]%*[^\n]", *pps);
		if(**pps==0x22){
			*(*pps+strlen(*pps)-1)=0;
			(*pps)++;
		}
}
