#include<stdio.h>
#include<stdlib.h>
int gcd(int ,int);
int lcm(int,int);
/**************计よ猭****************/

int main(void)
{
	int a,b;
	printf("叫块俱计a");
	scanf("%d",&a);
	printf("叫块俱计b");
	scanf("%d",&b);
	
	printf("a籔b程そ计 %d\n",gcd(a,b));
	
	printf("a籔b程そ计 %d\n",lcm(a,b));
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
