#include<stdio.h>
#include<stdlib.h>
int gcd(int ,int);
int lcm(int,int);
/**************�ƭȤ�k��****************/

int main(void)
{
	int a,b;
	printf("�п�J���a�G");
	scanf("%d",&a);
	printf("�п�J���b�G");
	scanf("%d",&b);
	
	printf("a�Pb���̤j���]�� %d\n",gcd(a,b));
	
	printf("a�Pb���̤p������ %d\n",lcm(a,b));
	system("pause");
	
}
int gcd(int a,int b)
{
	int i;
	for((a>=b)?i=a:i=b ; i>0;i--)
	{
		if((a%i==0) && (b%i==0))
			return i;
	}
}

int lcm(int a,int b)
{
	int i;
	for((a>=b)?i=b:i=a ; ;i++)
	{
		if((i%a==0) && (i%b==0))
			return i;
	}
}
