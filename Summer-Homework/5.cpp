#include<stdio.h>
#include<stdlib.h>

int main(void)
{
	double a=0,b=0;
	char equ;
	int go=1;
	while(go)
	{
		//輸入
		//判斷輸入
		//錯誤離開
		int check_input;
		do{
			printf(">> ");
			check_input=scanf(" %lf %c %lf",&a,&equ,&b);
			if(check_input!=3){
				printf(">> 我不知道怎麼計算!!\n");
				fflush(stdin);
			}
		}while(check_input!=3);
		//正確計算
		//加減乘除或離開 
		switch(equ)
		{
			case '+':
				printf(">> %f\n",a+b);
				break;
			case '-':
				printf(">> %f\n",a-b);
				break;
			case '*':
				printf(">> %f\n",a*b);
				break;
			case '/':
				if(b!=0)
					printf(">> %f\n",a/b);
				else
					printf(">> 分母不可為零\n");
				break;
			case 'q':
			case 'Q':
				go=0;
				break;
			default:
				printf(">> 我不知道怎麼計算!!\n");
		}
	}
} 
