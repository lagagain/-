#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
//#define DEBUG 

struct member
{
	bool is;
	int num;
};
int main(void)
{
	int max;
	int i;
	printf("請輸入最大數字(MAX):");
	do{
		int test;
		test=scanf("%d",&max);
		if(test!=1||max<=0)
			printf("輸入錯誤,請從新輸入:");
		fflush(stdin);
	}while(max<=0);
	
	member *list=(member*)calloc(max,sizeof(member));
	for(i=0;i<max;i++)
	{
		(list+i)->num=i+1;
		(list+i)->is=true;
	}
#ifdef DEBUG
	for(i=0;i<max;i++)
	{
		printf("is=");
		if((list+i)->is==true)
			printf("true");
		else
			printf("false");
		printf("  num=%d\n",(list+i)->num);
	}
#endif

	if(list->num==1)
		list->is=false;
	
	int head;
	do{
		for(i=0;i<max;i++)
		{
			if((list+i)->is==true)
			{
				head=i;
				break;
			}
		}
		for(i=head+1;i<max;i++)
		{
			if((list+i)->is==true)
			{
				if(((list+i)->num)%((list+head)->num)==0)
					(list+i)->is=false;
			}
		}
		printf("%d ",(list+head)->num);
		(list+head)->is=false;
		for(i=0;i<max;i++)
		{
			if((list+i)->is==true)
				break;
			else if(i==max-1)
				return 0;
		}
	}while(1);
	system("pause");
} 
