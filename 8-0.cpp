#include<stdio.h> 
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<string.h>
//#define DEBUG
#define LEN 4
#define MSG "<New>"
#define END "<END>"
//enum Bool{false=0,true=1};
//typedef enum Bool bool;
#define bool int
#define true (1)
#define false (0)

//結構:儲存玩家資料
struct Player_data_list{
	char name[50];	//玩家名稱 
	int cnt;	//回合數 
	int time;	//時間
	struct Player_data_list *next;	//下個玩家資訊 
}; 
typedef struct Player_data_list P_list;

//全域變數 
char quest[LEN];
char input[LEN];

//宣告函數 
bool init(void);	//初始化
void print_ruler(void);	//顯示規則 


//主程式 
int main(void)
{
	print_ruler();	//顯示規則 
	int i;
	bool ok;	//確認步驟完成 
	clock_t start,end;	//紀錄時間始末
	int cnt=0;	//紀錄回合數 
	int A,B;	//紀錄提示訊息
	int useclock;	//紀錄時間 
	char tmp_input;
	//初始化 
		//設定亂數(0-9)且四個數字都不重複
		srand(time(NULL));
		ok=init();
		if(ok==false)
		{
			printf("error!!");
			exit(1);
		}
		//設定時間、回合數 
		start=end=clock(); 
#ifdef DEBUG
	printf("設定數字為:");
	for(i=0;i<LEN;i++)
	{
		printf("%d ",quest[i]);
	}
	printf("\n");
#endif
go_start:
	while(1){
	A=B=0; 
	//使用者輸入答案
	for(i=0;i<LEN;i++)
	{
		scanf(" %c",&input[i]);
	}
	fflush(stdin);
	for(i=0;i<LEN;i++)	//判斷書入是否為數字 
	{
		if(input[i]>'9'||input[i]<'0')
		{
			printf("  輸入錯誤!\n");
			goto go_start;
		}
		else
		{
			input[i]-='0';
		}
	}
#ifdef DEBUG
	printf("輸入為：");
	for(i=0;i<LEN;i++)
	{
		printf("%d ",input[i]);
	}
	printf("\n");
#endif 
	for(i=0;i<LEN;i++)	//判斷是否輸入重複數字 
	{
		int t;
		for(t=1;t<LEN;t++)
		{
			if(input[i]==input[(i+t)%LEN])
			{
				printf("t=%d,i=%d\n",t,i);
				printf("  數字不可重複!!\n");
				goto go_start;
			}
		}
	}
	//判斷是否正確並回傳提示(包含放棄,電腦顯示答案),計入回合數
	for(i=0;i<LEN;i++)
	{
		if(input[i]==quest[i])
			A++;
		else
		{
			int t;
			for(t=1;t<LEN;t++)
			{
				if(input[i]==quest[(i+t)%LEN]){
					B++;
				}
			}
		}
	}
	cnt++;
	printf("%dA%dB\n",A,B);
	if(A==LEN)
		break;
	
	}
	//結束
		//統計時間和回和數
		end=clock(); 
		system("color 1E");
		printf("Bingo!!  恭喜答對!!\n");
		printf("花費時間：%d秒\t總回合數：%d\n",useclock=(end-start)/CLK_TCK,cnt);

		//記錄使用者名字
		printf("請輸入名字：");
		char name[50];
		gets(name);
		
		P_list *now,*tmp,*first,me;
		//儲存現在玩家資訊
		strcpy(me.name,name);
		me.cnt=cnt;
		me.time=useclock;
		me.next=NULL;
		now=first=&me;
		//開啟檔案
		FILE *fp;
		fp=fopen("num_game_list.txt","a+");
		 
		 char get_msg[50],get_stop[50];
		 sprintf(get_msg,"%s\n",MSG);
		 sprintf(get_stop,"%s\n",END);
		 while(!feof(fp))
		 {
		 	char input[50];
		 	fgets(input,50,fp);
		 	if(strcmp(input,END)==0)
		 		continue;
		 	else if(strcmp(input,get_msg)==0)
		 	{
		 		tmp=(P_list *)malloc(sizeof(P_list));
		 		fgets(tmp->name,50,fp);
		 		char *cg_name;
		 		cg_name=tmp->name;
		 		int len=strlen(cg_name);
		 		cg_name[len-1]='\0';
		 		fscanf(fp," %d",&(tmp->cnt));
		 		fscanf(fp," %d",&(tmp->time));
		 		now->next=tmp;
		 		now=tmp;
		 	}
		 }
		 tmp=(P_list *)malloc(sizeof(P_list));
		 strcpy(tmp->name,me.name);
		 tmp->cnt=me.cnt;
		 tmp->time=me.time;
		 now->next=tmp;
		 tmp->next=NULL;
		//選擇排序方式(或離開)
		int cg=1; //選擇
		printf("1.以回數排名\t2.以花費時間排名\t3.離開\n請選擇：");
		do{
			scanf(" %d",&cg);
		}while(cg!=1&&cg!=2&&cg!=3);
		if(cg==3)
		{
			//goto write_in;
			fprintf(fp,"%s\n%s\n%d\n%d\n%s\n",MSG,me.name,me.cnt,me.time,END);
			fclose(fp);
			return 0;
		}
		//show 
		P_list *g; 
		now=first;
		printf("名次\t玩家\t次數\t時間\n");
		for(i=0;;i++)
		{
			now=first;
			g=now->next;
#ifdef DEBUG1
		printf("first=%d\n",first);
		printf("first->next=%d\n",first->next);
		printf("now->next=%d\n",now->next);
		printf("g=%d\n",g);
		printf("g->next=");
		(g->next==NULL)?printf("NULL\n"):printf("%d",g->next);
		system("pause");
#endif 
			do
			{
				now=now->next;
				if(cg==1)
				{
					if(now->cnt<0)
						continue;
					else
					{
						if(now->cnt<g->cnt)
							g=now;
					}
				}
				else if(cg==2)
				{
					if(now->time<0)
						continue;
					else
					{
						if(now->time<g->time)
							g=now;
					}
				}
			}while(now->next!=NULL);
			
			printf("%d：\t%s\t%3d次  %d秒\n",i+1,g->name,g->cnt,g->time);
			now=first;
			if(g==first)
			{
				if(g->next=NULL)
					break;
				else
					first=g->next;
			}
			while(now->next!=g&&now->next!=NULL)
			{
				now=now->next;
			}
			now->next=g->next;
			if(first->next==NULL)
				break;
#ifdef DEBUG1
		printf("first=%d\n",first);
		printf("first->next=%d\n",first->next);
		printf("now->next=%d\n",now->next);
		printf("g=%d\n",g);
		printf("g->next=");
		(g->next==NULL)?printf("NULL\n"):printf("%d",g->next);
		system("pause");
#endif 

		}
write_in:
		fprintf(fp,"%s\n%s\n%d\n%d\n%s\n",MSG,me.name,me.cnt,me.time,END);
		fclose(fp);
		system("pause");
}

bool init(void)
{
	int i;
	for(i=0;i<LEN;i++)
	{
		quest[i]=-1;
	}
	for(i=0;i<LEN;i++)
	{
		quest[i]=rand()%10;
		int t;
		for(t=1;t<LEN;t++)
		{
			if(quest[i]==quest[(i+t)%LEN])
			{
				i--;
				break;
			}
		}
	}
	return true;
}

void print_ruler(void)
{
	system("color F");
	printf("!-----猜數字遊戲-----!\n");
	
}
