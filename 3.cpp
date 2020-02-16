#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
struct member;
void reset(member*);
void check_is(member*);
void print(member*,int);

int n;	//輸入的n 


struct member
{
	bool is;	//是否是質數 
	int num;	//值 
};

int main(void)
{
	printf("請輸入最大數字(n):");
	int test;
	do{
		test=scanf("%d",&n);
		if(n<=0||test!=1)
			printf("輸入錯誤,請從新輸入:");
	}while(n<=0||test!=1);
	free(&test);
	
	member *list=(member*)calloc(n,sizeof(member));	//紀錄清單 
	reset(list);	//初始化list
	check_is(list);	//測試質數
	system("cls");
	printf("3.1\n");
	int way=0;	//印出方式 
	print(list,way);	//顯示結果
	system("pause"); 
	
	system("cls");
	printf("3.2\n");
	if((list+n-1)->is==true)
		printf("n=%d是質數\n",n);
	else
		printf("n=%d不是質數\n",n);
	system("pause"); 
	
	system("cls");
	printf("3.3\n");
	way=1;	//印出方式 
	print(list,way);	//顯示結果
	system("pause"); 
} 
void print(member *list,int way)
{
	int i;
	for(i=0;i<n;i++)
	{
		if(way!=0 && i==n-1)
			continue;
		else if((list+i)->is==true)	//如果是質數就印出來 
			printf("%d ",(list+i)->num);
	}
	printf("\n");
}
void reset(member* list)	//初始化 
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
	int head=0;	//紀錄標準(公式) 
	int i;
	do{
		for(i=head;i<max;i++)	//尋找標準 
		{
			if((list+i)->is==true)
			{
				head=i;
				break;
			}
		}
		if(i>=max)	//跳出do-while 
			break;
		for(i=head+1;i<max;i++)	//與標準比較 
		{
			if((list+i)->is==true)
			{
				if(((list+i)->num)%((list+head)->num)==0)
					(list+i)->is=false;
			}
		}
		head++; //下次尋找標準略過此; 
	}while(1);
	#undef max
}
	
