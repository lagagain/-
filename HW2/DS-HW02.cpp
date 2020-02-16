#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define HELP "²�檺���ʦ�����,���@�Ӱ��|�e��,�A�i�H�復���H�U�ާ@(�Ȥp�g����)\n\tpush ���\n\tpop\n\tshow\t��ܩҦ�����\n�H��:\n\tsize\t�d�ݤ����Ӽ�\n\tcapacity\t�d�ݮe���j�p\n\tresize\t���]�e���j�p\n\tisempty\t�߰ݮe���O�_����\n\tclear\t�M�Ůe��\n\tindex\t�d�ݯS�w���ު�����\n\tsort\t�ƧǮe�����e\n�M��L���O:\n\thelp\t��ܦ��T��\n\thelp-all\t��ܧ�h���U�T��\n\texit\t���}\n"
#define HELP_MORE "��h:\n\tchange index_of_stack\t�ഫ���s��index�����|,�d��0~9�����\n\tnow_use\t��ܲ{�b�ϥΪ����|�s��\n\tdelete\t�R���ثe�ϥΪ����|�Ŷ��A�`�N�s��0���i����\n\tdir\t�C�X�Ҧ��w�g�إߪ����|�s��\n\tcgindex2 index ���\t���ܯS�w���ު��ȡA�䤤index��������Ʃιs\n\tmax\t�̤j��\n\tmin\t�̤p��\n\tsum\t�[�`\n\tavg\t����\n\taddnum ���\t�N�C�@�����[��\n\tminnum ���\t�N�C�@�������\n\tmultnum ���\t�N�C�@�������Y��\n\tdivnum ���\t�N�C�@�������Y��\n\tfile �ɮצW��\t���J�ɮפ��e����|\n\tsave �ɮצW��\t�x�s���|���e���ɮ�\n\n\t�A�i�H�즲��r�ɮ�(�@�Φh��)�쥻�����ɪ��ϼФW,�N�|�w���s�J���|,\n\t�A�i�H�� ��V��W�B�U �ϥξ��v���O\n" 
#define SWAP(a,b,t) ((t)=(a), (a)=(b), (b)=(t)) 
#define DATATYPE int
#define DATAPRINT "%d"
#define MAX_OF_STACK_LIST 10 
#define base 5
/*�禡�B�����ŧi*/
typedef struct stack stack; 
int str2order(char str[],stack *e);


/*�إ߰��|����������e*/
struct stack{
    int num;        //�����ثe�s�J�ƥ�-1,�Y�O���̤j�����ޭ� 
    int space;      //�����ثe�̤j�Ŷ�
    DATATYPE *element_start;     //��ڤ���,�s��Ʀr���
};

/*�إ߰��|*/
int create_stack(stack *e){
    e->num=-1;
    e->space=base;
    e->element_start=(DATATYPE *)malloc(sizeof(DATATYPE)*e->space);
    return 0;
}

/*��J�Ʀr*/
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

/*���X�Ʀr*/
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
		printf("�S�����\n");
		return NULL;
	}
}

/*��ܰ��|���e*/
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

/*���J�ɮצܰ��|*/
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
				printf("�Ʀr�s������\n");
				fscanf(fp,"%c");
				fflush(stdin);
			}
			fflush(stdin);
		}
		fclose(fp);
		return 0;
	}
	else{
		printf("�}�ɥ���!\n");
		return -1;
	}
}
/*�x�s���|���e���ɮ�*/
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
	    printf("�x�s����\n");
	    return 0;
    }
    else{
    	printf("�x�s����!\n");
    	return -1;
    }
} 
/*�p����|�����`�X*/
DATATYPE sum_stack(stack e){
	DATATYPE sum=0;
	int i;
	for(i=0;i<=e.num;i++){
		sum+=e.element_start[i];
	}
	//char pform[100];
	//sprintf(pform,"�`�M��%s\n",DATAPRINT);
	//printf(pform,sum);
	return sum;
}

/*�p����|����������*/
double avg_stack(stack e){
	double avg;
	DATATYPE sum=sum_stack(e);
	if(e.num<0){
		printf("�S������\n");
		return -1;
	}
	else{
		avg=(double)sum/(e.num+1);
		printf("������%lf\n",avg);
		return avg;	
	}
}

/*���|���e���̤j����*/
DATATYPE max_in_stack(stack e){
	int i;
	DATATYPE max;
	if(e.num<0){
		printf("���|����\n");
		return NULL;
	}
	else{
		for(i=1,max=*(e.element_start);i<=e.num;i++){
			if(e.element_start[i]>max){
				max=e.element_start[i];
			}
		}
		char pform[100];
		sprintf(pform,"�̤j�Ȭ�%s\n",DATAPRINT);
		printf(pform,max);
		return max;
	}
}



/*���|���e���̤p����*/
DATATYPE min_in_stack(stack e){
	int i;
	DATATYPE min;
	if(e.num<0){
		printf("���|����\n");
		return NULL;
	}
	else{
		for(i=1,min=*(e.element_start);i<=e.num;i++){
			if(e.element_start[i]<min){
				min=e.element_start[i];
			}
		}
		char pform[100];
		sprintf(pform,"�̤p�Ȭ�%s\n",DATAPRINT);
		printf(pform,min);
		return min;
	}
}

/*���ܯS�w���ު���*/
int change_index_in_stack(stack *e,int index,DATATYPE num){
	if(index<0||index>e->num){
		printf("index�ȿ��~!\n");
		return -1;
	}
	else{
		e->element_start[index]=num;
		return 0;
	}
	return 0;
}

/*�N���|���C�@�����[�W�Y���Ʀr*/
int stack_add_num(DATATYPE num,stack *e){
	int i;
	for(i=0;i<=e->num;i++){
		e->element_start[i]+=num;
	}
	return 0;
}

/*�N���|���C�@������Y���Ʀr*/
int stack_min_num(DATATYPE num,stack *e){
	int i;
	for(i=0;i<=e->num;i++){
		e->element_start[i]-=num;
	}
	return 0;
}

/*�N���|���C�@�������W�Y���Ʀr*/
int stack_mult_num(DATATYPE num,stack *e){
	int i;
	for(i=0;i<=e->num;i++){
		e->element_start[i]*=num;
	}
	return 0;
}

/*�N���|���C�@�������Y���Ʀr*/
int stack_div_num(DATATYPE num,stack *e){
	int i;
	if(num!=0){
		for(i=0;i<=e->num;i++){
			e->element_start[i]/=num;
		}
	}
	else{
		printf("���i���H�s\n");
		return -1;
	}
	return 0;
}


/*�ഫ�r�ꬰ�R�O*/
int str2order(char str[],stack *e){
	enum order_type{
		zero,
		help,
		help_all,
		push,
		pop,
		show,
		exit,
		/*************�s�W�\��*****************/
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
			 	printf("�����Ӽ�%d\n",e->num+1);
			 }
			 else{
			 	printf("�ثe����\n");
			 }
			 order=zero;
			 status=restart;
			 return 1;
		}
		else if(strcmp(str,"capacity")==0){
			order=capacity;
			printf("�e���j�p%d\n",e->space);
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
			//printf("�o��\�\\��|������\n");
			status=conti;
			return 4;
		}
		else if(strcmp(str,"sort")==0){
			order=sort;
			//printf("�o��\�\\��|������\n");
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
			sprintf(pform,"�`�M��%s\n",DATAPRINT);
			printf(pform,sum_stack(*e));
			order=zero;
			return 1;
		}
		else if(strcmp(str,"avg")==0){
			order=avg;
			avg_stack(*e);
			//printf("������%lf\n",avg_stack(*e));
			order=zero;
			return 1;
		}
		else if(strcmp(str,"max")==0){
			order=max;
			max_in_stack(*e);
			//char pform[100];
			//sprintf(pform,"�̤j�Ȭ�%s\n",DATAPRINT);
			//printf(pform,max_in_stack(*e));
			order=zero;
			return 1;
		}
		else if(strcmp(str,"min")==0){
			order=min;
			min_in_stack(*e);
			//printf("�̤p�Ȭ�%d\n",min_in_stack(*e));
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
				printf("���楢��\n\n���O�榡�� cgindex2 index data\n\t�䤤index���Ӭ���Ʃιs\n\tdata�����\n");
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
			printf("�d�L�����O!\n");
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
				printf("�d�L����\n");
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
				printf("���~�����O\n");
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
/*��l��*/
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
		printf("�������~���p\n");
		return -1;
	}
	return 0;
}


/*�D�{��*/
int main(int argc,char *argv[]){
	printf(HELP);
    stack *m[MAX_OF_STACK_LIST];	//�O�����|��m���M��
	int i_for_init;
	for(i_for_init=0;i_for_init<MAX_OF_STACK_LIST;i_for_init++){
		m[i_for_init]=NULL;
	}
	m[0]=(stack *)malloc(sizeof(stack));
    create_stack(m[0]);	//�إ߲Ĥ@�Ӱ��| 
    int index_of_stack_list=0;	//�{�b�ϥΪ����|,��l��0 
	init(argc,argv,m[0]);	//��l�� 
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
					printf("push���~!�Э��s��J�@���Ʀr\n");
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
					printf("��J�������~!�Э��s��J�@��\n");
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
					printf("��J���~!�Э��s��J�@������r�ιs\n");
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
					printf("��Jindex���~\n");
					break;
					//fflush(stdin);
				}
				else{
					if(cg2index<0||cg2index>=MAX_OF_STACK_LIST){
						printf("index���b��\�\\�d���\n");
						check_input=-1;
						break;
					}
					else{
						if(m[cg2index]==NULL){
							m[cg2index]=(stack*)malloc(sizeof(stack));
							create_stack(m[cg2index]);
						}
						index_of_stack_list=cg2index;
						printf("�ഫ�� %d ���|\n",index_of_stack_list);
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
				printf("�s��0�����|�����\����!\n");
			}
			else{
				free(m[index_of_stack_list]->element_start);
				free(m[index_of_stack_list]);
				m[index_of_stack_list]=NULL;
				index_of_stack_list=0;
				printf("�ഫ�� %d ���|\n",index_of_stack_list);
			}
		} 
		else if(status==now_use){
			printf("�{�b�ϥ� �s�� %d �����|\n",index_of_stack_list);
		}
		fflush(stdin);
	}
}

