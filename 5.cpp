#include<stdio.h>
#include<stdlib.h>

int main(void)
{
	double a=0,b=0;
	char equ;
	int go=1;
	while(go)
	{
		//��J
		//�P�_��J
		//���~���}
		int check_input;
		do{
			printf(">> ");
			check_input=scanf(" %lf %c %lf",&a,&equ,&b);
			if(check_input!=3){
				printf(">> �ڤ����D���p��!!\n");
				fflush(stdin);
			}
		}while(check_input!=3);
		//���T�p��
		//�[��������} 
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
					printf(">> �������i���s\n");
				break;
			case 'q':
			case 'Q':
				go=0;
				break;
			default:
				printf(">> �ڤ����D���p��!!\n");
		}
	}
} 
