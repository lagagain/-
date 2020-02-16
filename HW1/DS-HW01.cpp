#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#define N 50
#define HELP_MSG "\n�o�O�@�ӤG���j�M���{���C\n�N�}�Ҥ@�Ӧs��50�ӱq�p�ƨ�j�Ʀr���ɮסA�ӧA�h�i�H�q���M��Q�䪺�Ʀr�C����,�i�H���(L)ist�d�ݬO�_�j�M���T�C\nPS.�Ʀr�i�୫�ơA�G�j�M����m���@�w�O�A�Q�n���I�I\n\
�A�]�i�H���(H)elp  ��ܦ��T��\n\n\n"


void sort(int *start,int *end);

int main(int argc,char *argv[])
{
	/*open file*/
	FILE *ifile;	//pointer the input_file, there are 50 sorted-numbers(min-to-max) in the file
	int array_num[N];	//storage input num from input_file
	int i;	//use in for-loop, array's iterator 
	int search_num;	//the number that user want to find
	char try_again;	//y is yes, n is no
	int left,right;
	if(argc==1)
		ifile=fopen("DS-HW01-1024622-input.txt","r");
	else if(argc==2)
		ifile=fopen(argv[1],"r");
	else
	{
		printf("Error!!\n");
		system("pause");
		exit(0);
	}
	/*Check the file is open*/
	if(ifile==NULL)
	{
		printf("�}���ɮץ���!!\n");
		system("pause");
		exit(0);
	}
	/*creat a int array*/
	i=0;
	while(!feof(ifile))
	{
		int check_is_num;	//check content is num
		check_is_num=fscanf(ifile," %d",array_num+i);
		if(check_is_num!=1)
		{
			printf("�ɮפ��e�榡���~!!\n");
			system("pause");
			exit(0);
		}
		i++;
	}
	
	fclose(ifile);	//cloce ifile
	
	/*Check the num_list is sorted, and count is ture*/
	if(i!=N)
	{
		printf("�ɮ׼Ʀr�ƶq���ŦX�n�D!!\n");
		system("pause");
		exit(0); 
	}
	else
	{
		for(i=1;i<N;i++)
		{
			if(array_num[i]<array_num[i-1])
			{
				printf("�ɮפ��e�榡���ŦX�n�D!!\n");
				printf("�O�_�i��Ƨ�?(ĵ�i:�o�]�|���ܫ�����ܪ��T��!!)(N) : ");
				char the_answer=getche();
				printf("\n");
				if(the_answer=='y'||the_answer=='Y')
					sort(array_num,array_num+N);
				else
				{
					printf("���Ƨ�, �Y�N���}!");
					system("pause");
					exit(0);
				} 
			}
		}
	}
	
	do{	//let it can search again
		/*set index of min and max*/
		left=0;
		right=N-1;
		/*user input search_num,please*/
		printf("\n�п�J�n�M�䪺�Ʀr : ");
		scanf(" %d",&search_num);
		
		/*to find the num with binary-search*/
		/*print the num, and the order(index+1)*/
		/*   or printf other message*/
		int f_flag=0;	//if fine flag more than zero
		while(left<=right)
		{
			i=(left+right)/2;
			if(array_num[i]==search_num)
			{
				printf("�M��Ʀr%d, �b��%d�Ӧ�m\n",search_num,i+1);
				f_flag++;
				break;
			}
			else if(array_num[i]<search_num)
				left=i+1;
			else
				right=i-1;
		}
		if(!f_flag)
			printf("�S���A�n�䪺�Ʀr��!!\n");
		
		
		
		/**/
		do{
			printf("�O�_�b�j�M�@��?(Y / N / (l)ist / (h)elp) : ");
			
			try_again=getche();
			if(try_again=='l'||try_again=='L')
			{
				printf("\n");	//New_Line 
				for(i=0;i<N;i++)
				{
					printf("%d:%d. %c",i+1,array_num[i],(i<N-1)?'\t':'\n');
				}
			}
			else if(try_again=='h'||try_again=='H')
			{
				printf(HELP_MSG);
				printf("\n");
			}
			else if(try_again!='y'&&try_again!='n'&&try_again!='Y'&&try_again!='N')
				printf("��J���~��!\n");
		}while(try_again!='y'&&try_again!='n'&&try_again!='Y'&&try_again!='N');
		fflush(stdin);
	}while(try_again=='y'||try_again=='Y');
	/*stop and view*/
	system("pause");
	return 0;
}

void sort(int *start,int *end)
{
	/*It will sort a interger list*/
	#define SWAP(a,b,t) ((t)=(a), (a)=(b), (b)=(t)) 
	#define IN_LEN (end-start)
	int i;
	
	printf("�Ƨǫe:\n");
	for(i=0;i<IN_LEN;i++)printf("%d:%d. %c",i+1,*(start+i),(i<IN_LEN-1)?'\t':'\n');	//print list
	for(i=0;i<IN_LEN;i++)
	{
		int ii,tmp;
		for(ii=i;ii<IN_LEN;ii++)
		{
			if(*(start+i)>*(start+ii))
				SWAP(*(start+i),*(start+ii),tmp);
		}
	}
	printf("\n�Ƨǫ�:\n");
	for(i=0;i<IN_LEN;i++)printf("%d:%d. %c",i+1,*(start+i),(i<IN_LEN-1)?'\t':'\n');	//print list


	/*Storage New list*/
	char file_name[50];
	printf("�x�s��(�ťդ��x�s) : ");
	gets(file_name);
	if(file_name!="")
	{
		FILE *ofile;
		ofile=fopen(file_name,"w");
		if(ofile!=NULL)
		{
			for(i=0;i<IN_LEN;i++)
			{
				fprintf(ofile,"%d",*(start+i));
				if(i<IN_LEN-1)
					fprintf(ofile,"\n");
			}
			fclose(ofile);
		}
		else
			printf("�t�s����!!\n");
	}
	
	
	#undef IN_LEN
	#undef SWAP
}
