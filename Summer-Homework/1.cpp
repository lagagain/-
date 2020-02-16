#include<stdio.h>
#include<stdlib.h>
#define rabit 4
#define chi 2
const int ra_equ=rabit/chi; //一隻兔子需要幾隻雞 

int main(void)
{
	int check;	//確認輸入正確與否 
	int n;	//n值 
	printf("輸入n=");
	
	do{
		check=scanf("%d",&n);
		if(check!=1)
		{
			printf("輸入錯誤,請重新輸入:");
			fflush(stdin);
		}
	}while(check!=1);	//判斷輸入正確與否
	
	if(n<0)
		printf("輸入為負數!\n");
	else if(n%2!=0)
		printf("輸入為奇數\n");
	else
	{
		system("cls");
		printf("輸入n=%d\n\n",n);
		int rabit_num=0,chi_num=n/chi;	//紀錄雞和兔子的數量 
		do{
			printf("第%d組:",rabit_num+1);
			printf("兔子%d隻，",rabit_num);
			printf("雞%d隻\n",chi_num);
			rabit_num++;
			chi_num-=ra_equ;
		}while(chi_num>=0);
	}

	system("pause");
}
