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
int gcd(int a,int b)	//程そ计,劣锣埃猭 
{
	int max;
	int min;
	if(a>=b)
	{
		max=a;
		min=b;
	}
	else
	{
		max=b;
		min=a;
	}
	if (max%min!=0)
	   return gcd(min, (max%min));
	return min;
}

int lcm(int a,int b)
{
    int max = (a >= b?a:b),min = (a < b?a:b),i;
    for(i = 1;;++i)
    {
        if((max * i) % min == 0)
        {
            return (max * i);
        }
    }
}
