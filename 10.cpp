#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define MAX 10
typedef double LONG;
void input(LONG*);
clock_t sort(LONG*);
void show(LONG*);
int main(void)
{
	LONG list[MAX];	//��� 
	clock_t start,end;
	int i;	//�j������ 
	input(list);	//��J 
	start=clock();  //�ƧǶ}�l�p�� 
	end=sort(list);	//�Ƨ�,�����p�� 
	show(list);	//��ܾ�z�᪺���G 
	printf("\n�B�z�ɶ�%lf��",((double)end-start)/CLK_TCK);
	system("pause");
} 

void input(LONG *list)
{
	int i;
	for(i=0;i<MAX;i++)
	{
		int check;
		printf("��J��%d�ӼƦr:",i+1);
		do{
			check=scanf("%lf",list+i);
			if(check!=1)
			{
				printf("��J���~,�Э��s��J:");
				char ch;
				scanf("%c",&ch);
			}
		}while(check!=1);
	}
} 

clock_t sort(LONG *list)
{
	int i;
	LONG max;	//�x�s�̤j�� 
	int index;	//�洫���X 
	for(i=0;i<MAX;i++)
	{
		int j;
		max=*(list+i);
		index=i;
		for(j=i;j<MAX;j++)
		{
			if(*(list+j)>max)
			{
				max=*(list+j);
				index=j;
			}
		}
		LONG tmp;
		tmp=*(list+i);
		*(list+i)=*(list+index);
		*(list+index)=tmp;
//		show(list);
//		printf("\n");
//		for(i=1;i<10000;i++)printf(" \b");
	}
	
	return clock();
} 

void show(LONG *list)	//��ܪ���� 
{
	int i;
	for(i=MAX-1;i>=0;i--)
	{
		printf("%lf ",*(list+i));
	}
}
