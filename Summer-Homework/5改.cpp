#include<iostream>
#include<stdio.h>
#include<cstdlib>
#include<string>
#include"myinclude\\big_num.h">
using namespace std;

int main(void)
{
	big_num *a,*b;
	string input_is,tmp_str;
	char *get_input;
	char equ;
	int go=1;
	while(go)
	{
		//��J
		//�P�_��J
		//���~���}
		int check_input;
		do{
			int single_cnt=0;
			printf(">> ");
			cin>>input_is;
			get_input=(char *)calloc(input_is.length(),sizeof(char));
			for(int i=0;i<input_is.length();i++)
			{
				get_input[i]=input_is[i];
			}
			if(strcmp(get_input,"q")==0||strcmp(get_input,"Q")==0)
			{
				cout<<"�Y�N���}"<<endl;
				exit(0); 
			}
			for(int i=0;i<input_is.length();i++)
			{
				if(input_is[i]>='0'&&input_is[i]<='9'||input_is[i]=='+'||input_is[i]=='-'||input_is[i]=='*'||input_is[i]=='/'||input_is[i]==' ')
				{
					check_input=3;
				}
				
				else
					check_input=1;
			}
			free(get_input);
			int status=0;
			int mark;
			for(int i=0;i<input_is.length();i++)
			{
				if(status==0)
				{
					if(i!=0&&(!(input_is[i]>='0'&&input_is[i]<='9')))
					{
						status++;
						get_input=(char*)malloc(sizeof(char)*(i+3));
						for(int si=0;si<i;si++)
						{
							get_input[si]=input_is[si];
							get_input[si+1]='\0';
//							cout<<get_input[si];
						}
						cout<<endl;
						tmp_str=string(get_input);
						a=new big_num(tmp_str);
//						a->show(1);
						mark=i;
						equ=input_is[i];
//						cout<<equ<<endl;
					}
				}
				else if(status==1)
				{
					if(i!=(mark+1)&&(!(input_is[i]>='0'&&input_is[i]<='9')))
					{
						status++;
						check_input=2;
					}
				}
				else
					check_input=2;
			}
			if(check_input!=3)
				printf(">> �ڤ����D���p��!!\n");
			else
			{
				get_input=(char *)realloc(get_input,sizeof(char)*(input_is.length()-mark+3));
				for(int i=mark+1;i<input_is.length();i++)
				{
					if(input_is[i]=='\n'||input_is[i]=='\r')
						continue;
					get_input[i]=input_is[i];
					get_input[i+1]='\0';
				}
				string ntmp_str;
				ntmp_str=string(get_input+mark+1);
				b=new big_num(ntmp_str);
			}
		}while(check_input!=3);
		//���T�p��
		//�[��������} 
		
		
		switch(equ)
		{
			case '+':
				a->add(*b); 
				a->show(1);
				break;
			case '-':
				a->min(*b);
				a->show(1);
				break;
			case '*':
				cout<<"sorry,�o���\��|����@"<<endl; 
				break;
			case '/':
				a->div(*b);
				a->show(1);
				break;
			case 'q':
			case 'Q':
				go=0;
				break;
			default:
				printf(">> �ڤ����D���p��!!\n");
		}
		

	}

} 
