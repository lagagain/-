#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//#define DEBUG


struct dic{
	char *voc;
	int cnt;
	struct dic *next;
};

struct letter{
	char ch;
	int cnt;
};


struct dic* in_diclist(const char *,struct dic*);
int main(int avgc,char *avgv[])
{
	//輸入檔案
	FILE *ofile,*out;
	char *opname;
	struct letter ch_list[26];
	struct dic dic_list;
	
	if (avgc==2)
	{
		ofile=fopen(avgv[1],"r");
		out=fopen("outfile.txt","w");
		opname=avgv[1];
	}
	else if(avgc==1)
	{
		printf("請輸入檔案:");
		opname=(char *)malloc(sizeof(char)*100);
		gets(opname);
		ofile=fopen(opname,"r");
		out=fopen("outfile.txt","w");
	}
	else
	{
		printf("error!!");
		exit(1);
	}
	//分析、裝載(以及排序)
	if(ofile!=NULL)
	{
		int i;
		printf("open file %s\n",opname);	//提示訊息 
		
		//重設定定字母清單
		 for(i=0;i<26;i++){
			 ch_list[i].cnt=0;
			 ch_list[i].ch='a'+i;
			 
		#ifdef DEBUG
			printf("%c : %d\n",ch_list[i].ch,ch_list[i].cnt);
		#endif
		}
		dic_list.cnt=0;
		dic_list.next=NULL;
		
		char *letter=(char*)malloc(sizeof(char)*50);
		letter[0]='\0';
		dic_list.voc=(char*)malloc(sizeof(char)*15);
		dic_list.voc[0]='\0';
		
		struct dic *dic_now=&dic_list;
		#ifdef DEBUG
			printf("%s : %d\n",dic_now->voc,dic_now->cnt);
			while(dic_now->next!=NULL){
				dic_now=dic_now->next;
				printf("%s : %d\n",dic_now->voc,dic_now->cnt);
			} 
			system("pause");
		#endif
		
		while(!feof(ofile))
		{
			char ch;	//存取字母 
			ch=fgetc(ofile); //fscanf(ofile," %c",&ch); 
			if(ch>='a'&&ch<='z')
			{
				ch_list[ch-'a'].cnt++;
				sprintf(letter,"%s%c",letter,ch);
			}
			else if(ch>='A'&&ch<='Z')
			{
				ch_list[ch-'A'].cnt++;
				sprintf(letter,"%s%c",letter,ch-('A'-'a'));
			}
			else
			{
			//	static struct dic *dic_now=&dic_list;	//紀錄第一筆位置,現在位置 
				dic_now=&dic_list;
				if(in_diclist(letter,&dic_list)==NULL)
				{
					#ifdef DEBUG
						printf("Not in,letter=%s\n",letter);
					#endif
					if(letter[0]=='\0')
						continue;
					while(dic_now->next!=NULL)
					{
						struct dic *next=dic_now->next;
						if(strcmp(next->voc,letter)==1)
							break;
						dic_now=dic_now->next;
					}
					struct dic *tmp;
					tmp=dic_now->next;
					dic_now->next=(struct dic*)malloc(sizeof(struct dic));
					dic_now=dic_now->next;
					dic_now->voc=(char*)malloc(sizeof(char)*15);
					for(i=0;letter[i]!='\0';i++){
						(dic_now->voc)[i]=letter[i];
					//	printf("%c ",letter[i]);
					}
					//printf("\n");
					(dic_now->voc)[i]='\0';//strcpy(dic_now->voc,letter);
					dic_now->cnt=0;
					dic_now->next=tmp;
				
					#ifdef DEBUG
						printf("add %s\n",dic_now->voc);
					#endif
				}
				else
				{
					#ifdef DEBUG
						printf("Yes, in\n");
					#endif
					dic_now=in_diclist(letter,&dic_list);
					#ifdef DEBUG
						printf("finded\n");
					#endif
				}
				dic_now->cnt++;
				letter[0]='\0';
			
			}
			
		}
		//印出
		dic_now=&dic_list;	//	struct dic *dic_now=&dic_list;
		while(dic_now->next!=NULL){
			dic_now=dic_now->next;
			printf("%s : %d\n",dic_now->voc,dic_now->cnt);
			fprintf(out,"%s : %d\n",dic_now->voc,dic_now->cnt);
		} 
		double all_ch_cnt=0;
		for(i=0;i<26;i++){
			all_ch_cnt+=ch_list[i].cnt;
		}
		for(i=0;i<26;i++){
			double precent=(ch_list[i].cnt/all_ch_cnt)*100;
			printf("%c : %d  %.3lf%%\n",ch_list[i].ch,ch_list[i].cnt,precent);
			fprintf(out,"%c : %d  %.3lf%%\n",ch_list[i].ch,ch_list[i].cnt,precent);
		} 
		printf("同時另存到outfile.txt裡\n");
		fclose(ofile);
		fclose(out);
	}
	else
	{
		printf("can't open the file(%s)",opname);
		exit(1);
	}
	//列印 
	system("pause");
	return 0;
}


struct dic* in_diclist(const char *letter,struct dic *doc_list){
	
	#ifdef DEBUG
		printf("find %s\n",letter);
	#endif
	if(strcmp(letter,doc_list->voc)==0)
	{
		return doc_list;
	}
	while(doc_list->next!=NULL){
		doc_list=doc_list->next;
		if(strcmp(letter,doc_list->voc)==0)
		{
			return doc_list;
		}
	}
	
	#ifdef DEBUG
		printf("done!!\n");
	#endif
	return NULL;
}
