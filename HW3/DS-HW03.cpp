#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h> 
#include<string.h>
 
/*����*/
#define keytype int //��¦�s�s���A 
#define KEY_PRINTF "%d"	
#define degree(x) (((x)->min_child)==NULL && ((x)->max_child)==(NULL))?(0):(((x)->min_child)!=(NULL) && ((x)->max_child)!=(NULL))?(2):(1)
#define HELP "�G���j�M��(�Ȥp�g����):\
\n\t���O �Ѽ�\t|����\
\n\tinsert ���\t|²�gi,���J�@�Ӿ�ƶi�J�G���j�M��\
\n\tn-insert   \t|²�gni,�s�򴡤J�Ҧ�\
\n\tdelete ���\t|²�gdel,�q�G���j�M�𤤧R���ӼƦr\
\n\tclear      \t|�M�ŤG���j�M��\
\n\tdisplay  \t|�ۦP���O:show,�Hinorder��ܤ��e\
\n\tshow     \t|�ۦP���O:display,�Hinorder��ܤ��e\
\n\tshowtree \t|²�gt,�H����ܤ��e\
\n\tsearch ���\t|²�gs,�j�M�Ʀr���|\
\n\thelp    \t|²�gh,������U(���T��)\
\n\texit   	\t|���}/�h�X"
 
/*�ŧi*/
struct bsTree_unit;	//��¦�椸 
typedef struct bsTree_unit unit;
bool init_bsTree_unit(unit *input);
unit *creat_bsTree(keytype key);
typedef struct{
	/*�^�ǵ��c*/
	bool err;
	unit *re;
}retype;
bool init_retype(retype *re);
retype *search_bsTree(keytype key,unit *root);
bool insert2bsTree(keytype key,unit *root);
retype* delete4bsTree(unit *root,keytype key);
void show_bsTree(unit *root,int level);
void show_bsTree_LVR(unit *root);
void print_key_path(unit *to);
enum COMMAND{
	toexit=-1,
	insert_num=1,
	ninsert_num, 
	delete_num,
	display,
	search_num,
	show_tree,
	help,
	err,
	clear,
};
COMMAND equcommand(char *command);

/*��¦�椸���c���e*/
struct bsTree_unit{
	bsTree_unit *parent, *min_child, *max_child;
	keytype key;
};

/*�禡:��l�Ʀ^�ǵ��c*/
bool init_retype(retype *re){
	re->err=false;
	re->re=NULL;
	return true;
}


/*�禡:��l�ư�¦�椸*/
bool init_bsTree_unit(unit *input){
	input->parent=input->max_child=input->min_child=NULL;
	return true;
} 

/*�禡:�إߤG���j�M��;
��J:�ڪ����; 
�^��:�إߪ���m*/
unit *creat_bsTree(keytype key) {
	unit *root=(unit *)calloc(1,sizeof(unit));
	if(root!=NULL && init_bsTree_unit(root)){
		root->key=key;
		return root;
	}
	else{
		fprintf(stderr,"�إߤG���j�M��ɥX��\n");
		return NULL;
	}
}

/*�j�M�禡;
��J:�M�䪺���,��ڦ�m 
�^��NULL��ܷj�M����;
	�^�ǵ��c��err���u��ܧ䤣��;
	�^�ǵ��c��re���̫᪺��m*/
retype *search_bsTree(keytype key,unit *root){
	if(!root){
		return NULL;
	}
	retype *re=(retype *)malloc(sizeof(retype));
	unit *now=root;
	if(re!=NULL && init_retype(re)){
		if(!root){
			return NULL;
		}
		while(key!=now->key){
			if(now->min_child!=NULL && key<=now->key){
				now=now->min_child;
			}
			else if(now->max_child!=NULL && key>=now->key){
				now=now->max_child;
			}
			else{
				re->err=true;
				break;
			}
		}
		re->re=now;
		return re;
	}
	else{
		fprintf(stderr,"�إߦ^�ǵ��c�ɥX��\n");
		return NULL;
	}
}

/*���J���*/
bool insert2bsTree(keytype key,unit *root){
	if(!root){
		return false;
	}
	retype *get_re=search_bsTree(key,root);
	bool re;
	if(!get_re){
		fprintf(stderr,"���J����\n");
		re=false;
	}
	else{
		if(get_re->err){
			/*�䤣��,�ҥH�i�H���J*/
			unit *now=get_re->re;
			unit *add=(unit *)malloc(sizeof(unit));
			init_bsTree_unit(add);
			add->key=key;
			add->parent=now;
			if(key<(now->key)){
				/*����Ȥp,�O�p���p��*/
				add->min_child=now->min_child;
				now->min_child=add;
			}
			else{
				/*����Ȥj,�O�j���p��*/
				add->max_child=now->max_child;
				now->max_child=add; 
			}
			re=true;
		}
		else{
			fprintf(stderr,"�w�g�֦��ۦP���,�G���J����!\n");
			re=false;
		}
	}
	free(get_re);
	return re;
}

/*�qroot����ڪ��G���j�M�𤤧R����Ȭ�key���`�I;
�^��retype������
retype��err������ܲ������\,�Ϥ��h�_;
retype��re�����`�I���~�Ӫ��p��(�p�G�S�����`�I);
err�����Bre==NULL��ܾ�w��)*/
retype* delete4bsTree(unit *root,keytype key){
	if(!root){
		return NULL;
	}
	retype *get_re=search_bsTree(key,root);
	retype *re=(retype *)malloc(sizeof(re));
	init_retype(re);
	if(!get_re){
		fprintf(stderr,"��������\n");
		re->err=true;
	}
	else{
		if(get_re->err){
			/*�䤣��,�ҥH��������*/
			re->err=true;
		}
		else{
			unit *now=get_re->re;
			unit *parent=now->parent;
			switch (degree(now)){
				case 0:
					{
						if(parent!=NULL){
							if(parent->min_child==now){
								parent->min_child=NULL;
							}
							else{
								parent->max_child=NULL;
							}
							(re->re)=parent;
						}else{
							root=NULL;
						}
						free(now);
						break;
					}
				case 1:
					{
						unit *parent=now->parent;
						unit *child;
						if(now->min_child!=NULL){
							child=now->min_child; 
						}else{
							child=now->max_child;
						}
						child->parent=parent;
						if(parent!=NULL){
							if(parent->min_child==now){
								parent->min_child=child;
							}else{
								parent->max_child=child;
							}
							(re->re)=parent;
						}else{
							root=child;
							re->re=child;
						}
						free(now);
						break;
					}
				case 2:
					{
						unit *child=now->max_child;
						/*�M��̤j���p�Ĥ��̤p��*/
						while(child->min_child!=NULL){
							child=child->min_child;
						}
						unit *new_parent=(unit *)malloc(sizeof(unit));
						init_bsTree_unit(new_parent);
						new_parent->key=child->key;
						delete4bsTree(root,child->key);
						new_parent->parent=now->parent;
						new_parent->max_child=now->max_child;
						new_parent->min_child=now->min_child;
						if(now->parent!=NULL){
							if(now->parent->max_child==now){
								now->parent->max_child=new_parent;
							}else{
								now->parent->min_child=new_parent;
							}
						}else{
							root=new_parent;
							re->re=new_parent;
						}
						if(now->max_child!=NULL){
							now->max_child->parent=new_parent;
						}
						if(now->min_child!=NULL){
							now->min_child->parent=new_parent;
						}
						free(now);
						break;
					}
			}
			re->err=false;
		}
	}
	free(get_re);
	return re;
}

/*�H�𪬪��覡�i�����;
��J:���,�M��ڪ�����*/
void show_bsTree(unit *root,int level){
	if(root==NULL){
		return;
	}
	int i;
	for(i=0;i<level;i++){
		printf("|   ");
	}
	printf("\n");
	for(i=0;i<level;i++){
		printf("|%c%c%c",(i==level-1)?'-':' ',(i==level-1)?'-':' ',(i==level-1)?'-':' ');
	}
	printf(" ");
	printf(KEY_PRINTF,root->key);
	printf("\n");
	if(root->min_child!=NULL){
		show_bsTree(root->min_child,level+1);
	}
	if(root->max_child!=NULL){
		show_bsTree(root->max_child,level+1);
	}
	return;
	
}

/*�Hinorder���X�G���j�M��*/
void show_bsTree_LVR(unit *root){
	if(root==NULL){
		return;
	}
	if(root->min_child){
		show_bsTree_LVR(root->min_child);
	}
	char pform[20];
	sprintf(pform,"< %s >",KEY_PRINTF);
	printf(pform,root->key);
	if(root->max_child){
		show_bsTree_LVR(root->max_child);
	}
	return;
}

/*�������ܦ�|���|*/
void print_key_path(unit *to){
	if(to->parent!=NULL){
		print_key_path(to->parent);
	}
	char pform[50];
	sprintf(pform," -> %s",KEY_PRINTF);
	printf(pform,to->key);
}

/*�ഫ���O*/
COMMAND equcommand(char *str){
	if(strcmp(str,"insert")==0||strcmp(str,"i")==0){
		return insert_num;
	}
	else if(strcmp(str,"n-insert")==0||strcmp(str,"ni")==0){
		return ninsert_num;
	}
	else if(strcmp(str,"delete")==0||strcmp(str,"del")==0){
		return delete_num;
	}
	else if(strcmp(str,"display")==0||strcmp(str,"show")==0){
		return display;
	}
	else if(strcmp(str,"showtree")==0||strcmp(str,"t")==0){
		return show_tree;
	}
	else if(strcmp(str,"search")==0||strcmp(str,"s")==0){
		return search_num;
	}
	else if(strcmp(str,"help")==0||strcmp(str,"h")==0){
		return help;
	}
	else if(strcmp(str,"exit")==0){
		return toexit;
	}
	else if(strcmp(str,"clear")==0){
		return clear;
	}
	else{
		return err;
	}
} 

int main(void){

	unit *root=NULL;	/*��ڸ`�I */ 
	keytype input;	/*�������Ѽ� */ 
	COMMAND cg;	/*�ഫ�������O */
	char command[100];	/*��J�����O */ 
	printf(HELP);	/*������U */ 
	printf("\n");  
	do{
		printf(">>");
		/*printf("1.���J  2.�R��  3.���  4.�j�M  5.���(��)  6.���}\n�п�ܾާ@:"); */
		while(scanf(" %s",command)!=1){
			printf("��J����\n");
		}
		cg=equcommand(command);
		switch (cg){
			case insert_num:
				{
					if(scanf(" %d",&input)!=1){
						printf("���J�Ʀr����!\n");
						printf("insert�ݭn�@�Ӿ��,�Ҧp:insert 12\n");
						printf("�ݭn��L�����п�Jhelp\n");
						break;
					}
					if(root==NULL){
						root=creat_bsTree(input);
					}else{
						insert2bsTree(input,root);
					}
					break;
				}
			case delete_num:
				{
					if(root==NULL){
						printf("��w�g�ŤF\n");
						break;
					}
					if(scanf(" %d",&input)!=1){
						printf("�R���Ʀr����!\n");
						printf("delete�ݭn�@�Ӿ��,�Ҧp:delete 12\n");
						printf("�ݭn��L�����п�Jhelp\n");
						break;
					}
					bool flag=false;	//�O�_�O�ڵ��I 
					if(input==root->key){
						flag=true;
					}
					retype *get_re;
					get_re=delete4bsTree(root,input);
					if(flag){
						if(get_re){
							root=get_re->re;	
						}
					}
					free(get_re);
					break;
				}
			case display:
				if(root!=NULL){
					show_bsTree_LVR(root);
					printf("\n");
				}
				break;
			case search_num:
				{
					if(scanf(" %d",&input)!=1){
						printf("�j�M����!\n");
						printf("search�ݭn�@�Ӿ��,�Ҧp:search 12\n");
						printf("�ݭn��L�����п�Jhelp\n");
						break;
					}
					retype *get_re=search_bsTree(input,root);
					if(get_re!=NULL){
						print_key_path((get_re)->re);
						if(get_re->err){
							printf(" (�����)");
						} 
					}else{
						printf("(�����)");
					}
					printf("\n");
					break;
				}
			case show_tree:
				show_bsTree(root,0);
				printf("\n");
				break;
			case help:
				printf(HELP);
				printf("\n");
				break;
			case err: 
				printf("���������O!!\n");
				printf("�p�����U�п�Jhelp\n");
				break;
			case toexit:
				printf("�Y�N�����{��\n");
				break;
			case ninsert_num:
				{
					int cnt;	/*��J�ƶq*/
					int i;
					printf("�i�J�s�򴡤J�Ҧ�\n");
					fflush(stdin);
					printf("�п�J�Ӽ�(�ݭn�s�򴡤J�h�ּƦr?/�t�ƱN�L��):");
					while(scanf(" %d",&cnt)!=1){
						printf("����\n�п�J�����,�Τ���J�Ʀr�h��J�s\n");
						fflush(stdin);
					} 
					for(i=1;i<=cnt;i++){
						printf("�п�J��%d�ӼƦr:",i);
						while(scanf(" %d",&input)!=1){
							printf("���J�Ʀr����,�Э��s��J��%d�ӼƦr:",i);
							fflush(stdin);
						}
						if(root==NULL){
							root=creat_bsTree(input);
						}else{
							insert2bsTree(input,root);
						}
					}
					break;
				}
			case clear:
				{
					while(root!=NULL){
						retype *get_re;
						get_re=delete4bsTree(root,root->key);
						if(get_re){
							root=get_re->re;
							free(get_re);
						}
					}
					printf("�M�z����\n");
					break;
				}
			default:
				printf("���������~!!\n");
		}
		fflush(stdin);	/*�M���W�@�ӫ��O���ݯd*/ 
	}while(cg!=toexit);
	
	return 0;
}

