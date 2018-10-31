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
					printf("���Ա���û������\n");
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
				printf("���Ա������\n");
			break;
			case 'D':
			{
				if(ListLength(&L)==0){
					printf("���Ա���û������\n");
					break;
				}
				printf("������Ҫɾ����Ԫ��λ��: ");
				scanf("%*[^0-9]%d%*[^\n]", &i);
				if( ListDelete(&L, i, NULL) )
					printf("λ�ô���: %d\n", i);
				else
					printf("��ɾ����%d��ѧ����Ϣ\n", i);
			}
			break;
			case 'E':
				if(ListLength(&L)==0){
					printf("���Ա���û������\n");
					break;
				}
				printf("������Ҫ�޸�ѧ����Ϣ�����: ");
				scanf("%*[^0-9]%d%*[^\n]", &i);
				if( i<1||i>ListLength(&L) )
					printf("��Ŵ���\n");
				else{
					scanfelem(&student, i);
					CopyElem(GetElem(&L, i, NULL), &student);
					printf("���޸ĵ�%d��ѧ������Ϣ\n", i);
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
				printf(">>>��60������ѧ�Ƶ�ѧ��:\n");
				while(p=p->next)
					for(i=0;i<4;i++)
						if(p->data.grade[i]<60){
							num++;
							printelem(&p->data);
							break;
						}
				printf(">>>��%d��\n", num);
			}
			break;
			case 'V':
			{
				int num=0;
				LNode* p=&L;
				printf(">>>��90������ѧ�Ƶ�ѧ��:\n");
				while(p=p->next)
					for(i=0;i<4;i++)
						if(p->data.grade[i]>=90){
							num++;
							printelem(&p->data);
							break;
						}
				printf(">>>��%d��\n", num);
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
	printf("\nA.���  B.����  C.���  D.ɾ��  E.�޸�  K.����  U.60������  V.90������  Q.�˳�\n��ѡ��: ");
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
	printf(">>>��⵽ѡ��\'%c\'\n\n", n);
	return n;
}

void printelem(ElemType* pe)
{
	printf("����: %s \nѧ��: %s \n�ɼ�: %-5.3G %-5.3G %-5.3G %-5.3G \nƽ����: %.6G\n\n",
		pe->name, pe->ID, pe->grade[0], pe->grade[1], pe->grade[2], pe->grade[3], pe->average);
}

int scanfelem(ElemType* pe, int i)
{
	printf("�������%d��ѧ��������. \n>>>����: ", i);
	scanf("%*c%15[^\n]%*[^\n]", pe->name);
	printf(">>>ѧ��: ");
	scanf("%*[^0-9a-zA-Z]%15[0-9a-zA-Z]%*[^\n]", pe->ID);
	printf(">>>�ĿƳɼ�: ");
	scanf("%f %f %f %f", pe->grade, pe->grade+1, pe->grade+2, pe->grade+3);
	scanf("%*[^\n]");
	return 0;
}

void stuave(ElemType* pe)
{
	pe->average=(pe->grade[0]+pe->grade[1]+pe->grade[2]+pe->grade[3])/4.0;
}







