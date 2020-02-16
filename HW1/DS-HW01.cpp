#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#define N 50
#define HELP_MSG "\n這是一個二元搜尋的程式。\n將開啟一個存有50個從小排到大數字的檔案，而你則可以從中尋找想找的數字。之後,可以選擇(L)ist查看是否搜尋正確。\nPS.數字可能重複，故搜尋的位置不一定是你想要的！！\n\
你也可以選擇(H)elp  顯示此訊息\n\n\n"


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
		printf("開啟檔案失敗!!\n");
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
			printf("檔案內容格式錯誤!!\n");
			system("pause");
			exit(0);
		}
		i++;
	}
	
	fclose(ifile);	//cloce ifile
	
	/*Check the num_list is sorted, and count is ture*/
	if(i!=N)
	{
		printf("檔案數字數量不符合要求!!\n");
		system("pause");
		exit(0); 
	}
	else
	{
		for(i=1;i<N;i++)
		{
			if(array_num[i]<array_num[i-1])
			{
				printf("檔案內容格式不符合要求!!\n");
				printf("是否進行排序?(警告:這也會改變後續顯示的訊息!!)(N) : ");
				char the_answer=getche();
				printf("\n");
				if(the_answer=='y'||the_answer=='Y')
					sort(array_num,array_num+N);
				else
				{
					printf("不排序, 即將離開!");
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
		printf("\n請輸入要尋找的數字 : ");
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
				printf("尋找數字%d, 在第%d個位置\n",search_num,i+1);
				f_flag++;
				break;
			}
			else if(array_num[i]<search_num)
				left=i+1;
			else
				right=i-1;
		}
		if(!f_flag)
			printf("沒有你要找的數字喔!!\n");
		
		
		
		/**/
		do{
			printf("是否在搜尋一次?(Y / N / (l)ist / (h)elp) : ");
			
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
				printf("輸入錯誤喔!\n");
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
	
	printf("排序前:\n");
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
	printf("\n排序後:\n");
	for(i=0;i<IN_LEN;i++)printf("%d:%d. %c",i+1,*(start+i),(i<IN_LEN-1)?'\t':'\n');	//print list


	/*Storage New list*/
	char file_name[50];
	printf("儲存為(空白不儲存) : ");
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
			printf("另存失敗!!\n");
	}
	
	
	#undef IN_LEN
	#undef SWAP
}
