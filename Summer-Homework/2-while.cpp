#include<stdio.h>
#include<stdlib.h>
#define toMAX 1000
/*****�ϥ�while-loog��**********/

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
	printf("�p��1~10000(���t)���_��,�����O3�����ƪ��M\n");
	printf("�p�⵲�G�� %d",sum);
	system("pause");
	return 0;
} 
