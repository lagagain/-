#include<stdio.h>
#include<stdlib.h>
#define rabit 4
#define chi 2
const int ra_equ=rabit/chi; //�@���ߤl�ݭn�X���� 

int main(void)
{
	int check;	//�T�{��J���T�P�_ 
	int n;	//n�� 
	printf("��Jn=");
	
	do{
		check=scanf("%d",&n);
		if(check!=1)
		{
			printf("��J���~,�Э��s��J:");
			fflush(stdin);
		}
	}while(check!=1);	//�P�_��J���T�P�_
	
	if(n<0)
		printf("��J���t��!\n");
	else if(n%2!=0)
		printf("��J���_��\n");
	else
	{
		system("cls");
		printf("��Jn=%d\n\n",n);
		int rabit_num=0,chi_num=n/chi;	//�������M�ߤl���ƶq 
		do{
			printf("��%d��:",rabit_num+1);
			printf("�ߤl%d���A",rabit_num);
			printf("��%d��\n",chi_num);
			rabit_num++;
			chi_num-=ra_equ;
		}while(chi_num>=0);
	}

	system("pause");
}
