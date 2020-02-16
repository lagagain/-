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
	LONG list[MAX];	//資料 
	clock_t start,end;
	int i;	//迴圈鰾數 
	input(list);	//輸入 
	start=clock();  //排序開始計時 
	end=sort(list);	//排序,結束計時 
	show(list);	//顯示整理後的結果 
	printf("\n處理時間%lf秒",((double)end-start)/CLK_TCK);
	system("pause");
} 

void input(LONG *list)
{
	int i;
	for(i=0;i<MAX;i++)
	{
		int check;
		printf("輸入第%d個數字:",i+1);
		do{
			check=scanf("%lf",list+i);
			if(check!=1)
			{
				printf("輸入錯誤,請重新輸入:");
				char ch;
				scanf("%c",&ch);
			}
		}while(check!=1);
	}
} 

clock_t sort(LONG *list)
{
	int i;
	LONG max;	//儲存最大值 
	int index;	//交換號碼 
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

void show(LONG *list)	//顯示的函數 
{
	int i;
	for(i=MAX-1;i>=0;i--)
	{
		printf("%lf ",*(list+i));
	}
}
