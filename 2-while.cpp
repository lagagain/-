#include<stdio.h>
#include<stdlib.h>
#define toMAX 1000
/*****使用while-loog做**********/

int main(void)
{
	int i=1;
	int sum=0;
	while(i<toMAX)
	{
		if( (i%3!=0) && (i%2!=0) )
			sum+=i;
		i++;
	}
	printf("計算1~10000(不含)的奇數,但不是3的倍數的和\n");
	printf("計算結果為 %d",sum);
	system("pause");
	return 0;
} 
