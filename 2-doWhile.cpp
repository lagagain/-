#include<stdio.h>
#include<stdlib.h>
#define toMAX 1000
/*****�ϥ�do-while��**********/

int main(void)
{
	int i=1;
	int sum=0;
	do{
		if( (i%3!=0) && (i%2!=0) )
			sum+=i;
		i++;
	}while(i<toMAX);
	printf("�p��1~10000(���t)���_��,�����O3�����ƪ��M\n");
	printf("�p�⵲�G�� %d",sum);
	system("pause");
	return 0;
} 
