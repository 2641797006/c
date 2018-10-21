//���½�ElemType�����ִ���
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
					printf("˳�����û������\n");
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
					printf("˳��������\n");
			break;
			case 'D':
			{
				ElemType e;
				if(L.length==0){
					printf("˳�����û������\n");
					break;
				}
				printf("������Ҫɾ����Ԫ��λ��: ");
				scanf("%*[^0-9]%d%*[^\n]", &i);
				if( ListDelete(&L, i, &e) )
					printf("λ�ô���: %d\n", i);
				else
					printf("��ɾ����%d��Ԫ��%d\n", i, e);
			}
			break;
			case 'E':
			{
				int r;
				ElemType e;
				printf("������Ҫ����Ԫ�ص�λ��: ");
				scanf("%*[^0-9]%d%*[^\n]", &i);
				printf("Ȼ����������Ԫ�ص�ֵ: ");
				scanf("%*[^0-9]%d%*[^\n]", &e);
				r=ListInsert(&L, i, e);
				if(r==-1)
					printf("λ�ô���: %d\n", i);
				else if(r==-2)
					printf("�ڴ����, ����Ԫ��ʧ��\n");
				else
					printf("���ڵ�%dλ�ò���Ԫ��%d\n", i, e); 
			}
			break;
			case 'F':
			{
				int num=0;
				SqList L1=L;
				ElemType* pe, e;
				printf("������Ҫ����Ԫ�ص�ֵ: ");
				scanf("%*[^0-9]%d%*[^\n]", &e);
				while(L1.length>0){
					pe=LocateElem(&L1, e);
					if(!pe)
						break;
					else{
						printf("��%d��, ", ++pe-L.elem);
						L1.length-=(pe-L1.elem);
						L1.elem=pe;
						num++;
					}
				}
				printf("���ҵ�%d��\n", num);
			}
			break;
			case 'G':
			{
				ElemType e, e1;
				printf("������Ҫ�޸ĵ�Ԫ��ֵ: ");
				scanf("%*[^0-9]%d%*[^\n]", &e);
				printf("�������µ�Ԫ��ֵ: ");
				scanf("%*[^0-9]%d%*[^\n]", &e1);
				if( !ListAmend(&L, e, e1) )
					printf("δ�ҵ�ֵ%d\n", e);
				else
					printf("�ѽ�һ��%d��Ϊ%d\n", e, e1);
			}
			break;
			case 'H':
				printf("\n      <<����˵�>>\n");
				menux();
				printf("\n");
			break;
			case 'K':
				system("cls");
			break;
			case 'M':
				if(L.length<1){
					printf("˳�����û������\n");
					break;
				}
				if( MessList(&L) )
					printf("����˳��ʧ��\n");
				else
					PrintList(&L);
			break;
			case 'N':
			{
				if(L.length<2){
					printf("˳��������ݲ�����һ��\n");
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
				printf("�뽫Ŀ���ļ��ϵ�����||������Ŀ���ļ���: ");
				pfname(&ps);
				r=fscanList(&L, ps, openmode);
				if(r!=-520)
					printf("Error: fscanList error code: %d\n", r);
			}
			break;
			case 'S':
				if(L.length<1){
					printf("˳�����û������\n");
					break;
				}
				SortList(&L);
				PrintList(&L);
			break;
			case 'V':
			{
				if(L.length<1){
					printf("˳�����û������\n");
					break;
				}
				ElemType* pe=L.elem+L.length-1, e;
				printf("������������ʽ��˳����ֵ: ");
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
				printf("�뽫Ŀ���ļ��ϵ�����||������Ŀ���ļ���: ");
				pfname(&ps);
				r=fprintList(&L, ps, openmode);
				if(r!=-520)
					printf("Error: fprintList error code: %d\n", r);
			}
			break;
			case 'X':
			{
				if(L.length<1){
					printf("˳�����û������\n");
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
				printf("����������,(�Ƿ��������): ");
				while( scanf("%Lf", &v)>0 ){
					if(v!=(int)v)
						break;
					if( ListInsert(&L, L.length+1, v) )
						printf("�ڴ����\n");
				}
				scanf("%*[^\n]");
			}
			break;
			default:
				printf("<<Switch Case>>: This option was not found!\n");
				printf("����չ������ѡ��:\n\n");
				menux();
				printf("\n");
		}
		menu();
	}
}

void menu()
{
	printf("\nA.���˳���  B.��ʼ������100������  C.clear���  D.ɾ��Ԫ��  E.���Ԫ��  F.����Ԫ��  G.�޸�Ԫ��  H.����  Q.�˳�\n��ѡ��: ");
}

void menux()
{
	printf("\
S.sort����        M.mess����\n\
R.���ļ���ȡ����  W.���ļ��������\n\
X.�����ֵ        V.ȫ��Ԫ�ظ�ֵΪ\n\
Y.���˳������  N.����˳���\n\
Z.�ֶ�����˳���");

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
	printf(">>>��⵽ѡ��\'%c\'\n\n", n);
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
