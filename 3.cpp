#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
struct member;
void reset(member*);
void check_is(member*);
void print(member*,int);

int n;	//��J��n 


struct member
{
	bool is;	//�O�_�O��� 
	int num;	//�� 
};

int main(void)
{
	printf("�п�J�̤j�Ʀr(n):");
	int test;
	do{
		test=scanf("%d",&n);
		if(n<=0||test!=1)
			printf("��J���~,�бq�s��J:");
	}while(n<=0||test!=1);
	free(&test);
	
	member *list=(member*)calloc(n,sizeof(member));	//�����M�� 
	reset(list);	//��l��list
	check_is(list);	//���ս��
	system("cls");
	printf("3.1\n");
	int way=0;	//�L�X�覡 
	print(list,way);	//��ܵ��G
	system("pause"); 
	
	system("cls");
	printf("3.2\n");
	if((list+n-1)->is==true)
		printf("n=%d�O���\n",n);
	else
		printf("n=%d���O���\n",n);
	system("pause"); 
	
	system("cls");
	printf("3.3\n");
	way=1;	//�L�X�覡 
	print(list,way);	//��ܵ��G
	system("pause"); 
} 
void print(member *list,int way)
{
	int i;
	for(i=0;i<n;i++)
	{
		if(way!=0 && i==n-1)
			continue;
		else if((list+i)->is==true)	//�p�G�O��ƴN�L�X�� 
			printf("%d ",(list+i)->num);
	}
	printf("\n");
}
void reset(member* list)	//��l�� 
{
	int i;
	for(i=0;i<n;i++)
	{
		(list+i)->num=i+1;
		(list+i)->is=true;
	}
	if(list->num==1)
		list->is=false;
}

void check_is(member*list)
{
	#define max n
	int head=0;	//�����з�(����) 
	int i;
	do{
		for(i=head;i<max;i++)	//�M��з� 
		{
			if((list+i)->is==true)
			{
				head=i;
				break;
			}
		}
		if(i>=max)	//���Xdo-while 
			break;
		for(i=head+1;i<max;i++)	//�P�зǤ�� 
		{
			if((list+i)->is==true)
			{
				if(((list+i)->num)%((list+head)->num)==0)
					(list+i)->is=false;
			}
		}
		head++; //�U���M��зǲ��L��; 
	}while(1);
	#undef max
}
	
