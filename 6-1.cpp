#include<stdio.h>
#include<stdlib.h>


struct big_num{
	int num;
	struct big_num *next;
	struct big_num *pre;
};


void mult(struct big_num*,int);
void show(struct big_num*);

int main(void)
{
	struct big_num ans={1,NULL,NULL};
	int n;
	printf("½Ð¥X¤Jn:");
	scanf(" %d",&n);
	
	
	if(n<0)
	{
		printf("Error!!\n");
		exit(0);
	}
	int old_n=n;
	n=1;
	while(n<=old_n){
		mult(&ans,n);
//		printf("%d!=",n);
//		show(&ans);
//		printf("\n");
		n++;
	}
	
	printf("%d!=",old_n);
	show(&ans);
	printf("\n");
	system("pause");
	return 0;
}

void mult(struct big_num *fist,int n)
{
	struct big_num *now=fist;
	
	int tmp=0;
	while(1)
	{
		(now->num)*=n;
		(now->num)+=tmp;
		tmp=(now->num)/10;
		(now->num)%=10;
		
//		printf("tmp = %d\n",tmp);
//		system("pause");
			
		if((now->next)==NULL)
		{
			while(tmp>0)
			{
				now->next=(struct big_num*)malloc(sizeof(struct big_num));
				struct big_num *totmp=now;
				now=now->next;
				now->pre=totmp;
				now->num=tmp;
				now->next=NULL;
				tmp=(now->num)/10;
				now->num%=10;
			}
			break;
		}
		else
			now=now->next;
	}
}
void show(struct big_num *fist)
{
	struct big_num *now=fist;
	while(now->next!=NULL)
	{
		now=now->next;
	}
	
	while(1)
	{
		printf("%d",(now->num));
		if(now->pre!=NULL)
			now=now->pre;
		else
			break;
	}
}
