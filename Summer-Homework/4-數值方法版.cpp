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
int gcd(int a,int b)	//�̤j���]��,����۰��k 
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
