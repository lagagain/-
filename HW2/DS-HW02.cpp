#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define HELP "簡單的互動式環境,有一個堆疊容器,你可以對它做以下操作(僅小寫有效)\n\tpush 整數\n\tpop\n\tshow\t顯示所有元素\n以及:\n\tsize\t查看元素個數\n\tcapacity\t查看容器大小\n\tresize\t重設容器大小\n\tisempty\t詢問容器是否為空\n\tclear\t清空容器\n\tindex\t查看特定索引的元素\n\tsort\t排序容器內容\n和其他指令:\n\thelp\t顯示此訊息\n\thelp-all\t顯示更多幫助訊息\n\texit\t離開\n"
#define HELP_MORE "更多:\n\tchange index_of_stack\t轉換為編號index的堆疊,範圍為0~9的整數\n\tnow_use\t顯示現在使用的堆疊編號\n\tdelete\t刪除目前使用的堆疊空間，注意編號0不可移除\n\tdir\t列出所有已經建立的堆疊編號\n\tcgindex2 index 整數\t改變特定索引的值，其中index應為正整數或零\n\tmax\t最大值\n\tmin\t最小值\n\tsum\t加總\n\tavg\t平均\n\taddnum 整數\t將每一元素加值\n\tminnum 整數\t將每一元素減值\n\tmultnum 整數\t將每一元素乘某數\n\tdivnum 整數\t將每一元素除某數\n\tfile 檔案名稱\t載入檔案內容到堆疊\n\tsave 檔案名稱\t儲存堆疊內容至檔案\n\n\t你可以拖曳文字檔案(一或多個)到本執行檔的圖標上,將會預先存入堆疊,\n\t你可以用 方向鍵上、下 使用歷史指令\n" 
#define SWAP(a,b,t) ((t)=(a), (a)=(b), (b)=(t)) 
#define DATATYPE int
#define DATAPRINT "%d"
#define MAX_OF_STACK_LIST 10 
#define base 5
/*函式、類型宣告*/
typedef struct stack stack; 
int str2order(char str[],stack *e);


/*建立堆疊資料類型內容*/
struct stack{
    int num;        //紀錄目前存入數目-1,即記錄最大的索引值 
    int space;      //紀錄目前最大空間
    DATATYPE *element_start;     //實際元素,存放數字資料
};

/*建立堆疊*/
int create_stack(stack *e){
    e->num=-1;
    e->space=base;
    e->element_start=(DATATYPE *)malloc(sizeof(DATATYPE)*e->space);
    return 0;
}

/*放入數字*/
int push_stack(stack *e,DATATYPE d){
    if (e->num>=e->space-1){
        e->space+=base;
        int space=e->space;
        e->element_start=(DATATYPE *)realloc(e->element_start,sizeof(DATATYPE)*space);
    }
    e->num++;
    e->element_start[e->num]=d;
    return 0;
}

/*取出數字*/
DATATYPE pop_stack(stack *e){
	if(e->num>=0){
	    DATATYPE data=e->element_start[e->num];
	    e->num--;
		char pform[100];
		sprintf(pform,"%s\n",DATAPRINT);
	    printf(pform,data);
	    return data;
	}
	else{
		printf("沒有資料\n");
		return NULL;
	}
}

/*顯示堆疊內容*/
int show_stack(stack e){
    int i;
    printf("{");
    for(i=0;i<=e.num;i++){
		char pform[100];
		sprintf(pform," %s%%c",DATAPRINT);
		printf(pform,e.element_start[i],(i==e.num)?' ':',');
    }
    printf("}\n");
}

/*載入檔案至堆疊*/
int load_file(char *fname,stack *m){
	FILE *fp;
	fp=fopen(fname,"r");
	if(fp!=NULL){
		DATATYPE input;
		int check_input;
		char *tmp_ptr;
		while(!feof(fp)){
			char pform[100];
			sprintf(pform," %s",DATAPRINT);
			check_input=fscanf(fp,pform,&input);
			if(check_input==1){
				str2order("push",m);
				tmp_ptr=(char *)&input;
				str2order(tmp_ptr,m);
				sprintf(pform,"push %s\n",DATAPRINT);
				printf(pform,input);
			}
			else{
				printf("數字存取失敗\n");
				fscanf(fp,"%c");
				fflush(stdin);
			}
			fflush(stdin);
		}
		fclose(fp);
		return 0;
	}
	else{
		printf("開檔失敗!\n");
		return -1;
	}
}
/*儲存堆疊內容至檔案*/
int save_as(stack e,char fname[]){
    int i;
    FILE *fp;
    fp=fopen(fname,"w");
    if(fp!=NULL){
	    for(i=0;i<=e.num;i++){
			char pform[100];
			sprintf(pform,"%s",DATAPRINT);
            fprintf(fp,pform,e.element_start[i]);
			if(i<e.num){
				fprintf(fp,"\n");
			} 
	    }
	    fclose(fp);
	    printf("儲存完成\n");
	    return 0;
    }
    else{
    	printf("儲存失敗!\n");
    	return -1;
    }
} 
/*計算堆疊元素總合*/
DATATYPE sum_stack(stack e){
	DATATYPE sum=0;
	int i;
	for(i=0;i<=e.num;i++){
		sum+=e.element_start[i];
	}
	//char pform[100];
	//sprintf(pform,"總和為%s\n",DATAPRINT);
	//printf(pform,sum);
	return sum;
}

/*計算堆疊元素的平均*/
double avg_stack(stack e){
	double avg;
	DATATYPE sum=sum_stack(e);
	if(e.num<0){
		printf("沒有元素\n");
		return -1;
	}
	else{
		avg=(double)sum/(e.num+1);
		printf("平均為%lf\n",avg);
		return avg;	
	}
}

/*堆疊內容的最大元素*/
DATATYPE max_in_stack(stack e){
	int i;
	DATATYPE max;
	if(e.num<0){
		printf("堆疊為空\n");
		return NULL;
	}
	else{
		for(i=1,max=*(e.element_start);i<=e.num;i++){
			if(e.element_start[i]>max){
				max=e.element_start[i];
			}
		}
		char pform[100];
		sprintf(pform,"最大值為%s\n",DATAPRINT);
		printf(pform,max);
		return max;
	}
}



/*堆疊內容的最小元素*/
DATATYPE min_in_stack(stack e){
	int i;
	DATATYPE min;
	if(e.num<0){
		printf("堆疊為空\n");
		return NULL;
	}
	else{
		for(i=1,min=*(e.element_start);i<=e.num;i++){
			if(e.element_start[i]<min){
				min=e.element_start[i];
			}
		}
		char pform[100];
		sprintf(pform,"最小值為%s\n",DATAPRINT);
		printf(pform,min);
		return min;
	}
}

/*改變特定索引的值*/
int change_index_in_stack(stack *e,int index,DATATYPE num){
	if(index<0||index>e->num){
		printf("index值錯誤!\n");
		return -1;
	}
	else{
		e->element_start[index]=num;
		return 0;
	}
	return 0;
}

/*將堆疊中每一元素加上某的數字*/
int stack_add_num(DATATYPE num,stack *e){
	int i;
	for(i=0;i<=e->num;i++){
		e->element_start[i]+=num;
	}
	return 0;
}

/*將堆疊中每一元素減掉某的數字*/
int stack_min_num(DATATYPE num,stack *e){
	int i;
	for(i=0;i<=e->num;i++){
		e->element_start[i]-=num;
	}
	return 0;
}

/*將堆疊中每一元素乘上某的數字*/
int stack_mult_num(DATATYPE num,stack *e){
	int i;
	for(i=0;i<=e->num;i++){
		e->element_start[i]*=num;
	}
	return 0;
}

/*將堆疊中每一元素除某的數字*/
int stack_div_num(DATATYPE num,stack *e){
	int i;
	if(num!=0){
		for(i=0;i<=e->num;i++){
			e->element_start[i]/=num;
		}
	}
	else{
		printf("不可除以零\n");
		return -1;
	}
	return 0;
}


/*轉換字串為命令*/
int str2order(char str[],stack *e){
	enum order_type{
		zero,
		help,
		help_all,
		push,
		pop,
		show,
		exit,
		/*************新增功能*****************/
		size,
		capacity,
		resize,
		isempty,
		clear,
		index,
		sort,
		file,
		save,
		max,
		min,
		sum,
		avg,
		cgindex2,
		addnum,
		minnum,
		multnum,
		divnum
	};
	enum state{
		restart,
		conti,
	}; 
	
	static int status=restart,order=zero;
	if(status==restart){
		if(strcmp(str,"exit")==0){
			order=exit;
			return -1;
		}
		else if(strcmp(str,"help")==0){
			order=help;
			printf(HELP);
			order=zero;
			status=restart;
			return 1;
		}
		else if(strcmp(str,"help-all")==0){
			order=help;
			printf(HELP);
			printf(HELP_MORE);
			order=zero;
			status=restart;
			return 1;
		}
		else if(strcmp(str,"push")==0){	
			order=push;
			status=conti;
			return 2;
		}
		else if(strcmp(str,"pop")==0){
			order=pop;
			pop_stack(e);
			//char pform[100];
			//sprintf(pform,"%s\n",DATAPRINT);
			//printf(pform,pop_stack(e));
			order=zero;
			status=restart;
			return 1;
		}
		else if(strcmp(str,"show")==0){
			order=show;
			show_stack(*e);
			order=zero;
			status=restart;
			return 1;
		}
		else if(strcmp(str,"size")==0){
			 order=size;
			 if(e->num>=0){
			 	printf("元素個數%d\n",e->num+1);
			 }
			 else{
			 	printf("目前為空\n");
			 }
			 order=zero;
			 status=restart;
			 return 1;
		}
		else if(strcmp(str,"capacity")==0){
			order=capacity;
			printf("容器大小%d\n",e->space);
			order=zero;
			status=restart;
			return 1;
		}
		else if(strcmp(str,"isempty")==0){
			order=isempty;
			
			if(e->num<0){
				printf("TURE\n"); 
			}
			else{
				printf("FALSE\n");
			}
			order=zero;
			status=restart;
			return 1;
		}
		else if(strcmp(str,"clear")==0){
			order=clear;
			e->num=-1;
			order=zero;
			status=restart;
			return 1;
		}
		else if(strcmp(str,"index")==0){
			order=index;
			status=conti;
			return 3;
		}
		else if(strcmp(str,"resize")==0){
			order=resize;
			//printf("這項\功\能尚未完成\n");
			status=conti;
			return 4;
		}
		else if(strcmp(str,"sort")==0){
			order=sort;
			//printf("這項\功\能尚未完成\n");
			int i;
			for(i=0;i<=e->num;i++)
			{
				int ii,tmp;
				for(ii=i;ii<=e->num;ii++)
				{
					if(*(e->element_start+i)>*(e->element_start+ii))
						SWAP(*(e->element_start+i),*(e->element_start+ii),tmp);
				}
			}
			order=zero;
			status=restart;
			return 1;
		}
		else if(strcmp(str,"file")==0){
			order=file;
			status=conti;
			return 5;
		}
		else if(strcmp(str,"save")==0){
			order=save;
			status=conti;
			return 6;
		}
		else if(strcmp(str,"sum")==0){
			order=sum;
			//sum_stack(*e);
			char pform[100];
			sprintf(pform,"總和為%s\n",DATAPRINT);
			printf(pform,sum_stack(*e));
			order=zero;
			return 1;
		}
		else if(strcmp(str,"avg")==0){
			order=avg;
			avg_stack(*e);
			//printf("平均為%lf\n",avg_stack(*e));
			order=zero;
			return 1;
		}
		else if(strcmp(str,"max")==0){
			order=max;
			max_in_stack(*e);
			//char pform[100];
			//sprintf(pform,"最大值為%s\n",DATAPRINT);
			//printf(pform,max_in_stack(*e));
			order=zero;
			return 1;
		}
		else if(strcmp(str,"min")==0){
			order=min;
			min_in_stack(*e);
			//printf("最小值為%d\n",min_in_stack(*e));
			order=zero;
			return 1;
		}
		
		else if(strcmp(str,"cgindex2")==0){
			order=cgindex2;
			int check_input=0;
			char pform[100];
			sprintf(pform," %%d %s",DATAPRINT);
			int index;
			DATATYPE cg2num;
			check_input=scanf(pform,&index,&cg2num);
			if(check_input==2){
				change_index_in_stack(e,index,cg2num);
			}
			else{
				printf("執行失敗\n\n指令格式為 cgindex2 index data\n\t其中index應該為整數或零\n\tdata為整數\n");
			}
			order=zero;
			return 1;
		}
		else if(strcmp(str,"addnum")==0){
			order=addnum;
			status=conti;
			return 7;
		}
		else if(strcmp(str,"minnum")==0){
			order=minnum;
			status=conti;
			return 8;
		}
		else if(strcmp(str,"multnum")==0){ 
			order=multnum;
			status=conti;
			return 9;
		}
		else if(strcmp(str,"divnum")==0){ 
			order=divnum;
			status=conti;
			return 10;
		}
		else if(strcmp(str,"change")==0){ 
			order=zero;
			status=restart;
			return 11;
		}
		else if(strcmp(str,"dir")==0){ 
			order=zero;
			status=restart;
			return 12;
		}
		else if(strcmp(str,"delete")==0){ 
			order=zero;
			status=restart;
			return 13;
		}
		else if(strcmp(str,"now_use")==0){ 
			order=zero;
			status=restart;
			return 14;
		}
		else{
			printf("查無此指令!\n");
			return 1;
		}
	}
	else if(status==conti){
		if(order==push){
			DATATYPE *tmp_ptr;
			tmp_ptr=(DATATYPE*)str;
			push_stack(e,*tmp_ptr);
			order=zero;
			status=restart;
		}
		else if(order==index){
			int *tmp_ptr;
			int i;
			tmp_ptr=(int*)str;
			if(*tmp_ptr<0||*tmp_ptr>e->num){
				printf("查無元素\n");
			}
			else{
				char pform[100];
				sprintf(pform,"stack[%%d]=%s\n",DATAPRINT);
				printf(pform,*tmp_ptr,e->element_start[*tmp_ptr]);
			}
			order=zero;
			status=restart;
			return 1;
		}
		else if(order==resize){
			int *tmp_ptr;
			int i;
			tmp_ptr=(int*)str;
			if(*tmp_ptr<0){
				printf("錯誤的指令\n");
			}
			else{
				i=*tmp_ptr;
				e->element_start=(DATATYPE *)realloc(e->element_start,sizeof(DATATYPE)*i);
				e->space=i;
				if(e->num+1>e->space){
					e->num=e->space-1;
				}
			}
			order=zero;
			status=restart;
			return 1;
		}
		else if(order==file){
			order=zero;
			status=restart;
			load_file(str,e);
			order=zero;
			status=restart;
			return 1;
		}
		else if(order==save){
			order=zero;
			status=restart;
			save_as(*e,str);
			order=zero;
			status=restart;
			return 1;
		}
		else if(order==addnum){
			DATATYPE *tmp_ptr;
			tmp_ptr=(DATATYPE *)str;
			stack_add_num(*tmp_ptr,e);
			order=zero;
			status=restart;
		}
		else if(order==minnum){
			DATATYPE *tmp_ptr;
			tmp_ptr=(DATATYPE *)str;
			stack_min_num(*tmp_ptr,e);
			order=zero;
			status=restart;
		}
		else if(order==multnum){
			DATATYPE *tmp_ptr;
			tmp_ptr=(DATATYPE *)str;
			stack_mult_num(*tmp_ptr,e);
			order=zero;
			status=restart;
		}
		else if(order==divnum){
			DATATYPE *tmp_ptr;
			tmp_ptr=(DATATYPE *)str;
			stack_div_num(*tmp_ptr,e);
			order=zero;
			status=restart;
		}
	}
}
/*初始化*/
int init(int argc,char *argv[],stack *e){
	if(argc==1){
		return 0;
	}
	else if(argc>1){
		int i;
		for(i=1;i<argc;i++){
			load_file(argv[i],e);
		}
		return 0;
	}
	else{
		printf("不明錯誤狀況\n");
		return -1;
	}
	return 0;
}


/*主程式*/
int main(int argc,char *argv[]){
	printf(HELP);
    stack *m[MAX_OF_STACK_LIST];	//記錄堆疊位置的清單
	int i_for_init;
	for(i_for_init=0;i_for_init<MAX_OF_STACK_LIST;i_for_init++){
		m[i_for_init]=NULL;
	}
	m[0]=(stack *)malloc(sizeof(stack));
    create_stack(m[0]);	//建立第一個堆疊 
    int index_of_stack_list=0;	//現在使用的堆疊,初始為0 
	init(argc,argv,m[0]);	//初始化 
    int status=1;
	enum state{
		conti=1,
		error=-1,
		push=2,
		index=3,
		resize=4,
		file=5,
		save=6,
		addnum=7,
		minnum=8,
		multnum=9,
		divnum=10,
		change=11,
		dir=12,
		delete_stack=13,
		now_use=14,
	};

	while(status){
		printf(">>");
		char str1[100];
		scanf(" %s",str1);
		status=str2order(str1,m[index_of_stack_list]);
		if(status<0){
			break;
			//exit(1);
		}
		else if(status==2){
			DATATYPE input;
			int check_input;
			char *tmp_ptr;
			do{
				char pform[100];
				sprintf(pform," %s",DATAPRINT);
				check_input=scanf(pform,&input);
				if(check_input!=1){
					printf("push錯誤!請重新輸入一次數字\n");
				}
				fflush(stdin);
			}while(check_input!=1);
			tmp_ptr=(char *)&input;
			str2order(tmp_ptr,m[index_of_stack_list]);
		}
		else if(status==addnum||status==minnum||status==multnum||status==divnum){
			DATATYPE input;
			int check_input;
			char *tmp_ptr;
			do{
				char pform[100];
				sprintf(pform," %s",DATAPRINT);
				check_input=scanf(pform,&input);
				if(check_input!=1){
					printf("輸入類型錯誤!請重新輸入一次\n");
				}
				fflush(stdin);
			}while(check_input!=1);
			tmp_ptr=(char *)&input;
			str2order(tmp_ptr,m[index_of_stack_list]);
		}
		else if(status==index||status==resize){
			int input;
			int check_input;
			char *tmp_ptr;
			do{
				check_input=scanf(" %d",&input);
				if(check_input!=1){
					printf("輸入錯誤!請重新輸入一次正整字或零\n");
				}
				fflush(stdin);
			}while(check_input!=1);
			tmp_ptr=(char *)&input;
			str2order(tmp_ptr,m[index_of_stack_list]);
		}
		else if(status==file||status==save){
			scanf("%s",str1);
			str2order(str1,m[index_of_stack_list]);
		}
		else if(status==change){
			int cg2index,check_input;
			do{
				check_input=scanf(" %d",&cg2index);
				if(check_input!=1){
					printf("輸入index錯誤\n");
					break;
					//fflush(stdin);
				}
				else{
					if(cg2index<0||cg2index>=MAX_OF_STACK_LIST){
						printf("index不在允\許\範圍裡\n");
						check_input=-1;
						break;
					}
					else{
						if(m[cg2index]==NULL){
							m[cg2index]=(stack*)malloc(sizeof(stack));
							create_stack(m[cg2index]);
						}
						index_of_stack_list=cg2index;
						printf("轉換為 %d 堆疊\n",index_of_stack_list);
					}
				}
			}while(check_input!=1);
		}
		else if(status==dir){
			int i;
			printf("dir{");
			for(i=0;i<MAX_OF_STACK_LIST;i++){
				if(m[i]!=NULL){
					printf(" %d,",i);
				}
			}
			printf("\b }\n");
		}
		else if(status==delete_stack){
			if(index_of_stack_list==0){
				printf("編號0的堆疊不允許移除!\n");
			}
			else{
				free(m[index_of_stack_list]->element_start);
				free(m[index_of_stack_list]);
				m[index_of_stack_list]=NULL;
				index_of_stack_list=0;
				printf("轉換為 %d 堆疊\n",index_of_stack_list);
			}
		} 
		else if(status==now_use){
			printf("現在使用 編號 %d 的堆疊\n",index_of_stack_list);
		}
		fflush(stdin);
	}
}

