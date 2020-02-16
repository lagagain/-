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

//���c:�x�s���a���
struct Player_data_list{
	char name[50];	//���a�W�� 
	int cnt;	//�^�X�� 
	int time;	//�ɶ�
	struct Player_data_list *next;	//�U�Ӫ��a��T 
}; 
typedef struct Player_data_list P_list;

//�����ܼ� 
char quest[LEN];
char input[LEN];

//�ŧi��� 
bool init(void);	//��l��
void print_ruler(void);	//��ܳW�h 


//�D�{�� 
int main(void)
{
	print_ruler();	//��ܳW�h 
	int i;
	bool ok;	//�T�{�B�J���� 
	clock_t start,end;	//�����ɶ��l��
	int cnt=0;	//�����^�X�� 
	int A,B;	//�������ܰT��
	int useclock;	//�����ɶ� 
	char tmp_input;
	//��l�� 
		//�]�w�ü�(0-9)�B�|�ӼƦr��������
		srand(time(NULL));
		ok=init();
		if(ok==false)
		{
			printf("error!!");
			exit(1);
		}
		//�]�w�ɶ��B�^�X�� 
		start=end=clock(); 
#ifdef DEBUG
	printf("�]�w�Ʀr��:");
	for(i=0;i<LEN;i++)
	{
		printf("%d ",quest[i]);
	}
	printf("\n");
#endif
go_start:
	while(1){
	A=B=0; 
	//�ϥΪ̿�J����
	for(i=0;i<LEN;i++)
	{
		scanf(" %c",&input[i]);
	}
	fflush(stdin);
	for(i=0;i<LEN;i++)	//�P�_�ѤJ�O�_���Ʀr 
	{
		if(input[i]>'9'||input[i]<'0')
		{
			printf("  ��J���~!\n");
			goto go_start;
		}
		else
		{
			input[i]-='0';
		}
	}
#ifdef DEBUG
	printf("��J���G");
	for(i=0;i<LEN;i++)
	{
		printf("%d ",input[i]);
	}
	printf("\n");
#endif 
	for(i=0;i<LEN;i++)	//�P�_�O�_��J���ƼƦr 
	{
		int t;
		for(t=1;t<LEN;t++)
		{
			if(input[i]==input[(i+t)%LEN])
			{
				printf("t=%d,i=%d\n",t,i);
				printf("  �Ʀr���i����!!\n");
				goto go_start;
			}
		}
	}
	//�P�_�O�_���T�æ^�Ǵ���(�]�t���,�q����ܵ���),�p�J�^�X��
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
	//����
		//�έp�ɶ��M�^�M��
		end=clock(); 
		system("color 1E");
		printf("Bingo!!  ���ߵ���!!\n");
		printf("��O�ɶ��G%d��\t�`�^�X�ơG%d\n",useclock=(end-start)/CLK_TCK,cnt);

		//�O���ϥΪ̦W�r
		printf("�п�J�W�r�G");
		char name[50];
		gets(name);
		
		P_list *now,*tmp,*first,me;
		//�x�s�{�b���a��T
		strcpy(me.name,name);
		me.cnt=cnt;
		me.time=useclock;
		me.next=NULL;
		now=first=&me;
		//�}���ɮ�
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
		//��ܱƧǤ覡(�����})
		int cg=1; //���
		printf("1.�H�^�ƱƦW\t2.�H��O�ɶ��ƦW\t3.���}\n�п�ܡG");
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
		printf("�W��\t���a\t����\t�ɶ�\n");
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
			
			printf("%d�G\t%s\t%3d��  %d��\n",i+1,g->name,g->cnt,g->time);
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
	printf("!-----�q�Ʀr�C��-----!\n");
	
}
