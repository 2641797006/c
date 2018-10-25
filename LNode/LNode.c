//���½�ElemType�����ִ���
#include <stdio.h>
#include <stdlib.h>
#include <c:/users/26417/desktop/LNode/pLNode.h>

void menu();
void menux();
int choose(int n);
int ychoose(int n);
void pfname(char** pps);

int main(){
	int i;
	LNode L;
	menu();
	InitList(&L, 0);
	for(i=0;i<100;i++)
		ListInsert(&L, i+1, i);
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
				if(ListLength(&L)<1)
					printf("������û������\n");
				else
					PrintList(&L);
			break;
			case 'B':
					PrintListX(&L);
			break;
			case 'C':
				DestroyList(&L);
				printf("���������\n");
			break;
			case 'D':
			{
				ElemType e;
				if(ListLength(&L)<1){
					printf("������û������\n");
					break;
				}
				printf("������Ҫɾ����Ԫ��λ��: ");
				scanf("%*[^0-9]%d%*[^\n]", &i);
				if( !ListDelete(&L, i, &e) )
					printf("λ�ô���: %d\n", i);
				else
					printf("��ɾ����%d��Ԫ��%d\n", i, e);
			}
			break;
			case 'E':
			{
				ElemType e;
				printf("������Ҫ����Ԫ�ص�λ��: ");
				scanf("%*[^0-9]%d%*[^\n]", &i);
				printf("Ȼ����������Ԫ�ص�ֵ: ");
				scanf("%*[^0-9]%d%*[^\n]", &e);
				if( !ListInsert(&L, i, e) )
					printf("����Ԫ��ʱ��������\n");
				else
					printf("���ڵ�%dλ�ò���Ԫ��%d\n", i, e); 
			}
			break;
			case 'F':
			{
				int num=0;
				LNode* Ln=&L;
				ElemType e;
				printf("������Ҫ����Ԫ�ص�ֵ: ");
				scanf("%*[^0-9]%d%*[^\n]", &e);
				while(Ln->next){
					Ln=LocateElem(Ln, e);
					if(!Ln)
						break;
					else{
						i=ListLength(&L)-ListLength(Ln);
						printf("��%d��, ", i);

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
			case 'I':
				DestroyList(&L);
				for(i=0;i<100;i++)
					ListInsert(&L, ListLength(&L)+1, i);
				PrintList(&L);
			break;
			case 'K':
				system("cls");
			break;
			case 'M':
				if(ListLength(&L)<2){
					printf("���������ݲ�����һ��\n");
					break;
				}
				if( MessList(&L) )
					printf("����˳��ʧ��\n");
				else
					PrintList(&L);
			break;
			case 'N':
			{
				if(ListLength(&L)<2){
					printf("���������ݲ�����һ��\n");
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
				if(ListLength(&L)<2){
					printf("���������ݲ�����һ��\n");
					break;
				}
				SortList(&L);
				PrintList(&L);
			break;
			case 'V':
			{
				if(ListLength(&L)<1){
					printf("������û������\n");
					break;
				}
				LNode* p=&L;
				ElemType e;
				printf("������������ʽ�������ֵ: ");
				scanf("%*[^0-9]%d%*[^\n]", &e);
				while(p=p->next)
					p->data=e;
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
				if(ListLength(&L)<1){
					printf("������û������\n");
					break;
				}
				LNode* p=&L;
				while(p=p->next){
					i=prand()%320/100;
					i=10*((i+9)/10*9+1)*((i+8)/10*9+1);
					p->data=prand()%i;
				}
				PrintList(&L);
			}
			break;
			case 'Z':
			{
				double v;
				printf("����������,(�Ƿ��������): ");
				while( scanf("%Lf", &v)>0 ){
					if(v!=(int)v)
						break;
					if( !ListInsert(&L, ListLength(&L)+1, v) )
						printf("����Ԫ��ʧ��\n");
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
	printf("\nA.�������  B.��ϸ���  C.clear���  D.ɾ��Ԫ��  E.���Ԫ��  F.����Ԫ��  G.�޸�Ԫ��  H.����  K.����  Q.�˳�\n��ѡ��: ");
}

void menux()
{
	printf("\
S.sort����        M.mess����\n\
R.���ļ���ȡ����  W.���ļ��������\n\
X.�����ֵ        V.ȫ��Ԫ�ظ�ֵΪ\n\
Z.�ֶ���������    N.��������\n\
I.��ʼ������100������");

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
