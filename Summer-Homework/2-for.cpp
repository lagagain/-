#include<stdio.h>
#include<stdlib.h>
#define toMAX 1000
/*****�ϥ�for-loog��**********/

int main(void)
{
	int i;
	int sum=0;
	for(i=1;i<toMAX;i++)
	{
		if( (i%3!=0) && (i%2!=0) )
			sum+=i;
	}
	printf("�p��1~10000(���t)���_��,�����O3�����ƪ��M\n");
	printf("�p�⵲�G�� %d",sum);
	system("pause");
	return 0;
} 
