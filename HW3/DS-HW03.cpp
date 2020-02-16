#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h> 
#include<string.h>
 
/*巨集*/
#define keytype int //基礎存存型態 
#define KEY_PRINTF "%d"	
#define degree(x) (((x)->min_child)==NULL && ((x)->max_child)==(NULL))?(0):(((x)->min_child)!=(NULL) && ((x)->max_child)!=(NULL))?(2):(1)
#define HELP "二元搜尋樹(僅小寫有效):\
\n\t指令 參數\t|說明\
\n\tinsert 整數\t|簡寫i,插入一個整數進入二元搜尋樹\
\n\tn-insert   \t|簡寫ni,連續插入模式\
\n\tdelete 整數\t|簡寫del,從二元搜尋樹中刪除該數字\
\n\tclear      \t|清空二元搜尋樹\
\n\tdisplay  \t|相同指令:show,以inorder顯示內容\
\n\tshow     \t|相同指令:display,以inorder顯示內容\
\n\tshowtree \t|簡寫t,以樹狀顯示內容\
\n\tsearch 整數\t|簡寫s,搜尋數字路徑\
\n\thelp    \t|簡寫h,顯示幫助(此訊息)\
\n\texit   	\t|離開/退出"
 
/*宣告*/
struct bsTree_unit;	//基礎單元 
typedef struct bsTree_unit unit;
bool init_bsTree_unit(unit *input);
unit *creat_bsTree(keytype key);
typedef struct{
	/*回傳結構*/
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

/*基礎單元結構內容*/
struct bsTree_unit{
	bsTree_unit *parent, *min_child, *max_child;
	keytype key;
};

/*函式:初始化回傳結構*/
bool init_retype(retype *re){
	re->err=false;
	re->re=NULL;
	return true;
}


/*函式:初始化基礎單元*/
bool init_bsTree_unit(unit *input){
	input->parent=input->max_child=input->min_child=NULL;
	return true;
} 

/*函式:建立二元搜尋樹;
輸入:根的鍵值; 
回傳:建立的位置*/
unit *creat_bsTree(keytype key) {
	unit *root=(unit *)calloc(1,sizeof(unit));
	if(root!=NULL && init_bsTree_unit(root)){
		root->key=key;
		return root;
	}
	else{
		fprintf(stderr,"建立二元搜尋樹時出錯\n");
		return NULL;
	}
}

/*搜尋函式;
輸入:尋找的鍵值,樹根位置 
回傳NULL表示搜尋失敗;
	回傳結構的err為真表示找不到;
	回傳結構的re為最後的位置*/
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
		fprintf(stderr,"建立回傳結構時出錯\n");
		return NULL;
	}
}

/*插入鍵值*/
bool insert2bsTree(keytype key,unit *root){
	if(!root){
		return false;
	}
	retype *get_re=search_bsTree(key,root);
	bool re;
	if(!get_re){
		fprintf(stderr,"插入失敗\n");
		re=false;
	}
	else{
		if(get_re->err){
			/*找不到,所以可以插入*/
			unit *now=get_re->re;
			unit *add=(unit *)malloc(sizeof(unit));
			init_bsTree_unit(add);
			add->key=key;
			add->parent=now;
			if(key<(now->key)){
				/*比鍵值小,是小的小孩*/
				add->min_child=now->min_child;
				now->min_child=add;
			}
			else{
				/*比鍵值大,是大的小孩*/
				add->max_child=now->max_child;
				now->max_child=add; 
			}
			re=true;
		}
		else{
			fprintf(stderr,"已經擁有相同鍵值,故插入失敗!\n");
			re=false;
		}
	}
	free(get_re);
	return re;
}

/*從root為樹根的二元搜尋樹中刪除鍵值為key的節點;
回傳retype的指標
retype的err為假表示移除成功,反之則否;
retype的re為父節點或繼承的小孩(如果沒有父節點);
err為假且re==NULL表示樹已空)*/
retype* delete4bsTree(unit *root,keytype key){
	if(!root){
		return NULL;
	}
	retype *get_re=search_bsTree(key,root);
	retype *re=(retype *)malloc(sizeof(re));
	init_retype(re);
	if(!get_re){
		fprintf(stderr,"移除失敗\n");
		re->err=true;
	}
	else{
		if(get_re->err){
			/*找不到,所以不必移除*/
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
						/*尋找最大的小孩中最小的*/
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

/*以樹狀的方式進行顯示;
輸入:樹根,和樹根的等級*/
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

/*以inorder走訪二元搜尋樹*/
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

/*依鍵值顯示行徑路徑*/
void print_key_path(unit *to){
	if(to->parent!=NULL){
		print_key_path(to->parent);
	}
	char pform[50];
	sprintf(pform," -> %s",KEY_PRINTF);
	printf(pform,to->key);
}

/*轉換指令*/
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

	unit *root=NULL;	/*樹根節點 */ 
	keytype input;	/*接收的參數 */ 
	COMMAND cg;	/*轉換為的指令 */
	char command[100];	/*輸入的指令 */ 
	printf(HELP);	/*顯示幫助 */ 
	printf("\n");  
	do{
		printf(">>");
		/*printf("1.插入  2.刪除  3.顯示  4.搜尋  5.顯示(樹)  6.離開\n請選擇操作:"); */
		while(scanf(" %s",command)!=1){
			printf("輸入失敗\n");
		}
		cg=equcommand(command);
		switch (cg){
			case insert_num:
				{
					if(scanf(" %d",&input)!=1){
						printf("插入數字失敗!\n");
						printf("insert需要一個整數,例如:insert 12\n");
						printf("需要其他說明請輸入help\n");
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
						printf("樹已經空了\n");
						break;
					}
					if(scanf(" %d",&input)!=1){
						printf("刪除數字失敗!\n");
						printf("delete需要一個整數,例如:delete 12\n");
						printf("需要其他說明請輸入help\n");
						break;
					}
					bool flag=false;	//是否是根結點 
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
						printf("搜尋失敗!\n");
						printf("search需要一個整數,例如:search 12\n");
						printf("需要其他說明請輸入help\n");
						break;
					}
					retype *get_re=search_bsTree(input,root);
					if(get_re!=NULL){
						print_key_path((get_re)->re);
						if(get_re->err){
							printf(" (未找到)");
						} 
					}else{
						printf("(未找到)");
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
				printf("未知的指令!!\n");
				printf("如需幫助請輸入help\n");
				break;
			case toexit:
				printf("即將結束程式\n");
				break;
			case ninsert_num:
				{
					int cnt;	/*輸入數量*/
					int i;
					printf("進入連續插入模式\n");
					fflush(stdin);
					printf("請輸入個數(需要連續插入多少數字?/負數將無視):");
					while(scanf(" %d",&cnt)!=1){
						printf("失敗\n請輸入正整數,或不輸入數字則輸入零\n");
						fflush(stdin);
					} 
					for(i=1;i<=cnt;i++){
						printf("請輸入第%d個數字:",i);
						while(scanf(" %d",&input)!=1){
							printf("插入數字失敗,請重新輸入第%d個數字:",i);
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
					printf("清理完成\n");
					break;
				}
			default:
				printf("未知的錯誤!!\n");
		}
		fflush(stdin);	/*清除上一個指令的殘留*/ 
	}while(cg!=toexit);
	
	return 0;
}

