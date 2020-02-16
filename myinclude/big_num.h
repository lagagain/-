#include<stdlib.h>
#include<stdio.h>
#include<iostream>
#include<string.h>
#include<math.h>
#include<time.h>
#include<stdbool.h>
#include<vector>
#include<string>
//#define DEBUG
/*-------------------------------------------------------*/
/*-------------------------------------------------------*/
using namespace std;

typedef long long LONG;
/*-------------------------------------------------------*/
/*-------------------------------------------------------*/
namespace big_num_evir
{
	static int MAX=15;
	static LONG base=1e+05;
	static int cnt=0;
	
	static int MAX_cg=0,Base_cg=0;
	bool cg_MAX(int inp)
	{
		if(MAX_cg==0)
		{
			MAX=inp;
			MAX_cg++;
			return true;
		}
		else
			return false;
	}
	bool cg_base(LONG inp)
	{
		if(Base_cg==0)
		{
			base=inp;
			Base_cg++;
			return true;
		}
		else
			return false;
	}
	
}
/*-------------------------------------------------------*/
/*-------------------------------------------------------*/
#define EVIR big_num_evir
#define OUTN 5
class big_num
{
	bool sb;	//正負
	string ID; 
	
	public:
		vector<LONG> num[2];
		vector<LONG> tmp;
		
		big_num(void);
		big_num(string);
		big_num(LONG,LONG=0,LONG=0);
		~big_num();
		big_num(vector<LONG>,vector<LONG>,int=0);
		big_num(vector<LONG>);
		big_num& operator=(big_num);
		
		void check(void);
		void clear(void);
		void cgsb(void);
		bool right(void);
		bool right(int);
		bool left(void);
		bool left(int);
		bool cp(big_num);
		int compare(big_num);
		LONG the_big(void);
		int the_num(void);
		
		bool addone();
		bool add(int, int=0);
		bool add(vector<LONG>,vector<LONG>);
		bool add(big_num);
		bool add(vector<LONG>);
		
		bool minone();
		bool min(int,int=0);
		bool min(vector<LONG>,vector<LONG>);
		bool min(big_num);
		bool min(vector<LONG>);
		
		bool mult(int);
		bool multten();
		
		bool div(int);
		bool divten();		
		bool div(vector<LONG>);								//////////////////////////////////////////
		bool div(vector<LONG>,vector<LONG>);
		bool div(big_num);
		
		bool cale_a(vector<LONG>,int=0);
		
		
/*
		
		template<typename t_type>
		bool add(t_type input);
		
		template<typename t_type>
		bool min(t_type input);
		
		
		bool mult(vector<LONG>);
		bool mult(vector<LONG>,vector<LONG>);

		big_num operator ++(int);
		bin_num& operator ++(int);
		void operator --();
		void operator --(int);
		
		template<typename t_type>
		big_num operator +(t_type);
		template<typename t_type>
		big_num operator -(t_type);
		
*/
		void cg_name(string);
		void show(int=0);
		void showID(int=0);
};
/*-------------------------------------------------------*/
bool big_num::cale_a(vector<LONG> inp,int sb)
{
	if(sb==0)
	{
		return add(inp); 
	}
	else
	{
		return min(inp);
	}
}
/*-------------------------------------------------------*/
bool big_num::min(vector<LONG> inp)
{
	for(int i=0;i<inp.size();i++)
	{
		if(inp[i]<0)
		{
			cout<<"輸入錯誤!! add(vec)"<<endl;
			return false; 
		}
	}
	big_num tmp(inp);
	min(tmp);
	return true;
}
/*-------------------------------------------------------*/
bool big_num::add(vector<LONG> inp)
{
	for(int i=0;i<inp.size();i++)
	{
		if(inp[i]<0)
		{
			cout<<"輸入錯誤!! add(vec)"<<endl;
			return false; 
		}
	}
	big_num tmp(inp);
	add(tmp);
	return true;
}
/*-------------------------------------------------------*/
inline int big_num::the_num(void)
{
	LONG n=num[0].size()-1;
	if(num[0][n]!=0)
		return n;
	else
	{
		n=0;
		while(num[1][n]==0&&
			n!=num[1].size())
		{
			n++;
		}
		return (n+1)*(-1);
	} 
}
/*-------------------------------------------------------*/
inline LONG big_num::the_big(void)
{
//	show(1);
	LONG n=num[0].size()-1;
	if(num[0][n]!=0)
		return num[0][n];
	else
	{
		n=0;
		while(num[1][n]==0&&
			n!=num[1].size()-1)
		{
			n++;
		}
//		cout<<"num[1]["<<n<<"]值為"<<num[1][n]<<endl; 
		if(num[1][n]==0)
			return -1;
		return num[1][n];
	} 
}
/*-------------------------------------------------------*/
inline int big_num::compare(big_num inp)
{
	if(sb!=inp.sb)
		if(sb==true)return 0;else return 1;
	else
	{
		big_num tmp=*this;
//		tmp.cg_name("name-tmp");
#ifdef DEBUG
		tmp.showID(1);
		tmp.show(1);
		inp.showID(1);
		inp.show(1);
		cout<<"原本的";
		showID(1);
		show(1);
#endif

		tmp.min(inp);
		if(tmp.sb==sb)
			return 0;
		else
			return 1;
		
	}
#ifdef DEBUG
#endif
}

/*-------------------------------------------------------*/
bool big_num::add(big_num inp)
{
	if(inp.sb==false)
	{
		return min(inp.num[0],inp.num[1]);
	}
	else
	{
		return add(inp.num[0],inp.num[1]);
	}
}
/*-------------------------------------------------------*/
bool big_num::min(big_num inp)
{
	if(inp.sb==true)
	{
		return min(inp.num[0],inp.num[1]);
		
	}
	else
	{
		return add(inp.num[0],inp.num[1]);
	}
}
/*-------------------------------------------------------*/
inline void big_num::showID(int nl)
{
	cout<<"ID="<<ID;
	if(nl!=0)
		cout<<endl;
}
/*-------------------------------------------------------*/
big_num& big_num:: operator=(big_num inp)
{
	cp(inp); 
}

/*-------------------------------------------------------*/
inline bool big_num::cp(big_num inp)
{
	num[0].clear();
	num[1].clear();
	sb=inp.sb;
	ID=inp.ID;
	for(int oi=0;oi<2;oi++)
	{
		for(int i=0;i<inp.num[oi].size();i++)
		{
			num[oi].push_back(inp.num[oi][i]);
		}
	}
	return true;
}
/*-------------------------------------------------------*/
inline bool big_num::min(vector<LONG> inp_s,vector<LONG> inp_b)
{
#ifdef DEBUG
	cout<<endl<<"-----------min(vec,vec)-------------"<<endl;
	showID(1);
	show(1);
	big_num test(inp_s,inp_b);
	test.show(1);
#endif

	LONG n,e;
	bool tmp_sb;
	if(sb==false)
	{
		n=inp_s.size()-1;
		for(int i=0;i<=inp_s.size()-1;i++)
		{
			if (i>num[0].size());
				num[0].push_back(0);
			num[0][i]+=inp_s[i];
		}
		n=inp_b.size()-1;
		for(int i=0;i<=inp_b.size()-1;i++)
		{
			if (i>num[1].size());
				num[1].push_back(0);
			num[1][i]+=inp_b[i];
		}
		
	}
	else
	{
		LONG inp_n,inp_e;
		n=num[0].size()-1;
		e=num[1].size()-1;
		inp_n=inp_s.size()-1;
		inp_e=inp_b.size()-1;
		tmp_sb=sb;
		
		if(n>inp_n)
		{
			n=inp_s.size()-1;
			for(int i=0;i<=inp_s.size()-1;i++)
			{
				if (i>num[0].size());
					num[0].push_back(0);
				num[0][i]-=inp_s[i];
			}
			n=inp_b.size()-1;
			for(int i=0;i<=inp_b.size()-1;i++)
			{
				if (i>num[1].size());
					num[1].push_back(0);
				num[1][i]-=inp_b[i];
			}
		
		}
		else if(n<inp_n)
		{
				
			big_num tmp(inp_s,inp_b);
			
			n=num[0].size()-1;
			for(int i=0;i<=n;i++)
			{
				if (i>inp_s.size());
					inp_s.push_back(0);
				tmp.num[0][i]-=num[0][i];
			}
			n=num[1].size()-1;
			for(int i=0;i<=n;i++)
			{
				if (i>inp_b.size());
					inp_b.push_back(0);
				tmp.num[1][i]-=num[1][i];
			}
			tmp_sb=(!(sb));
			
			tmp.sb=tmp_sb;
			cp(tmp);
		}
		else
		{
			if(num[0][n]<inp_s[inp_n])		///////////////////////////////////////
			{
				
				big_num tmp(inp_s,inp_b);
				
				n=num[0].size()-1;
				for(int i=0;i<=n;i++)
				{
					if (i>inp_s.size());
						inp_s.push_back(0);
					tmp.num[0][i]-=num[0][i];
				}
				n=num[1].size()-1;
				for(int i=0;i<=n;i++)
				{
					if (i>inp_b.size());
						inp_b.push_back(0);
					tmp.num[1][i]-=num[1][i];
				}
				tmp_sb=(!(sb));
				
				tmp.sb=tmp_sb;
				cp(tmp);
			}
			else if(num[0][n]>inp_s[inp_n])
			{
				n=inp_s.size()-1;
				for(int i=0;i<=inp_s.size()-1;i++)
				{
					if (i>num[0].size());
						num[0].push_back(0);
					num[0][i]-=inp_s[i];
				}
				n=inp_b.size()-1;
				for(int i=0;i<=inp_b.size()-1;i++)
				{
					if (i>num[1].size());
						num[1].push_back(0);
					num[1][i]-=inp_b[i];
				}
			}
			else if(num[0][n]==inp_s[inp_n])
			{
				LONG S_oi,S_i;
				LONG fin;
				int big=0;
				for(S_oi=0,fin=0;S_oi<=fin;S_oi++)
				{
					for((S_oi==0)?S_i=n:S_i=0;
						(S_oi==0)?S_i>=0:S_i<num[S_oi].size();
						(S_oi==0)?S_i--:S_i++)
						{
							if(num[S_oi][S_i]>((S_oi==0)?inp_s[S_i]:inp_b[S_i]))
							{
								big=1;
								break;
							}
							else if(num[S_oi][S_i]<((S_oi==0)?inp_s[S_i]:inp_b[S_i]))
							{
								big=2;
								break;
							}
							if((S_oi==0)&&(S_i==0)&&(big==0))
								fin++;
						}
				}
				if(big==0)
				{
					num[0].clear();
					num[1].clear();
					num[0].push_back(0);
					num[1].push_back(0);
				}
				else if(big==1)
				{
					n=inp_s.size()-1;
					for(int i=0;i<=inp_s.size()-1;i++)
					{
						if (i>num[0].size());
							num[0].push_back(0);
						num[0][i]-=inp_s[i];
					}
					n=inp_b.size()-1;
					for(int i=0;i<=inp_b.size()-1;i++)
					{
						if (i>num[1].size());
							num[1].push_back(0);
						num[1][i]-=inp_b[i];
					}
				}
				else if(big==2)
				{
				
					big_num tmp(inp_s,inp_b);
					
					n=num[0].size()-1;
					for(int i=0;i<=n;i++)
					{
						if (i>inp_s.size());
							inp_s.push_back(0);
						tmp.num[0][i]-=num[0][i];
					}
					n=num[1].size()-1;
					for(int i=0;i<=n;i++)
					{
						if (i>inp_b.size());
							inp_b.push_back(0);
						tmp.num[1][i]-=num[1][i];
					}
					tmp_sb=(!(sb));
					
					tmp.sb=tmp_sb;
					cp(tmp);
				}
				else
				{
					cout<<"嘿嘿...加錯了!"<<endl; 
				}
			}
		}
	}
#ifdef DEBUG
	showID(1);
	cout<<"檢查前";
	show(1);
	check();
	cout<<"檢查後";
	show(1); 
	cout<<"-----------結束min(vec,vec)-------------"<<endl;
#endif
	check();
	return true;
}
/*-------------------------------------------------------*/
inline bool big_num::add(vector<LONG> inp_s,vector<LONG> inp_b)
{
	LONG n,e;
	bool tmp_sb;
	if(sb==true)
	{
		n=inp_s.size()-1;
		for(int i=0;i<=inp_s.size()-1;i++)
		{
			if (i>num[0].size());
				num[0].push_back(0);
			num[0][i]+=inp_s[i];
		}
		n=inp_b.size()-1;
		for(int i=0;i<=inp_b.size()-1;i++)
		{
			if (i>num[1].size());
				num[1].push_back(0);
			num[1][i]+=inp_b[i];
		}
		
	}
	else
	{
		LONG inp_n,inp_e;
		n=num[0].size()-1;
		e=num[1].size()-1;
		inp_n=inp_s.size()-1;
		inp_e=inp_b.size()-1;
		tmp_sb=sb;
		
		if(n>inp_n)
		{
			n=inp_s.size()-1;
			for(int i=0;i<=inp_s.size()-1;i++)
			{
				if (i>num[0].size());
					num[0].push_back(0);
				num[0][i]-=inp_s[i];
			}
			n=inp_b.size()-1;
			for(int i=0;i<=inp_b.size()-1;i++)
			{
				if (i>num[1].size());
					num[1].push_back(0);
				num[1][i]-=inp_b[i];
			}
		
		}
		else if(n<inp_n)
		{
			
			big_num tmp(inp_s,inp_b);
			
			n=num[0].size()-1;
			for(int i=0;i<=n;i++)
			{
				if (i>inp_s.size());
					inp_s.push_back(0);
				tmp.num[0][i]-=num[0][i];
			}
			n=num[1].size()-1;
			for(int i=0;i<=n;i++)
			{
				if (i>inp_b.size());
					inp_b.push_back(0);
				tmp.num[1][i]-=num[1][i];
			}
			tmp_sb=(!(sb));
			
			tmp.sb=tmp_sb;
			cp(tmp);
		}
		else
		{
			if(num[0][n]<inp_s[inp_n])
			{
				
				big_num tmp(inp_s,inp_b);
				
				n=num[0].size()-1;
				for(int i=0;i<=n;i++)
				{
					if (i>inp_s.size());
						inp_s.push_back(0);
					tmp.num[0][i]-=num[0][i];
				}
				n=num[1].size()-1;
				for(int i=0;i<=n;i++)
				{
					if (i>inp_b.size());
						inp_b.push_back(0);
					tmp.num[1][i]-=num[1][i];
				}
				tmp_sb=(!(sb));
				
				tmp.sb=tmp_sb;
				cp(tmp);
			}
			else if(num[0][n]>inp_s[inp_n])
			{
				n=inp_s.size()-1;
				for(int i=0;i<=inp_s.size()-1;i++)
				{
					if (i>num[0].size());
						num[0].push_back(0);
					num[0][i]-=inp_s[i];
				}
				n=inp_b.size()-1;
				for(int i=0;i<=inp_b.size()-1;i++)
				{
					if (i>num[1].size());
						num[1].push_back(0);
					num[1][i]-=inp_b[i];
				}
			}
			else if(num[0][n]==inp_s[inp_n])
			{
				LONG S_oi,S_i;
				LONG fin;
				int big=0;
				for(S_oi=0,fin=0;S_oi<=fin;S_oi++)
				{
					for((S_oi==0)?S_i=n:S_i=0;
						(S_oi==0)?S_i>=0:S_i<num[S_oi].size();
						(S_oi==0)?S_i--:S_i++)
						{
							if(num[S_oi][S_i]>((S_oi==0)?inp_s[S_i]:inp_b[S_i]))
							{
								big=1;
								break;
							}
							else if(num[S_oi][S_i]<((S_oi==0)?inp_s[S_i]:inp_b[S_i]))
							{
								big=2;
								break;
							}
							if((S_oi==0)&&(S_i==0)&&(big==0))
								fin++;
						}
				}
				if(big==0)
				{
					num[0].clear();
					num[1].clear();
					num[0].push_back(0);
					num[1].push_back(0);
				}
				else if(big==1)
				{
					n=inp_s.size()-1;
					for(int i=0;i<=inp_s.size()-1;i++)
					{
						if (i>num[0].size());
							num[0].push_back(0);
						num[0][i]-=inp_s[i];
					}
					n=inp_b.size()-1;
					for(int i=0;i<=inp_b.size()-1;i++)
					{
						if (i>num[1].size());
							num[1].push_back(0);
						num[1][i]-=inp_b[i];
					}
				}
				else if(big==2)
				{
					
					big_num tmp(inp_s,inp_b);
					
					n=num[0].size()-1;
					for(int i=0;i<=n;i++)
					{
						if (i>inp_s.size());
							inp_s.push_back(0);
						tmp.num[0][i]-=num[0][i];
					}
					n=num[1].size()-1;
					for(int i=0;i<=n;i++)
					{
						if (i>inp_b.size());
							inp_b.push_back(0);
						tmp.num[1][i]-=num[1][i];
					}
					tmp_sb=(!(sb));
					
					tmp.sb=tmp_sb;
					cp(tmp);
				}
				else
				{
					cout<<"嘿嘿...加錯了!"<<endl; 
				}
			}
		}
	}
	check();
	return true;
}

/*-------------------------------------------------------*/
inline bool big_num::div(big_num inp)
{
	sb=(sb==inp.sb);
	return div(inp.num[0],inp.num[1]);
}
/*-------------------------------------------------------*/
inline bool big_num::div(vector<LONG> oinp,vector<LONG> obinp)
{
	using namespace EVIR;
	big_num tmp;
	for(int i=0;i<oinp.size();i++)
	{
		if(oinp[i]<0)
		{
			cout<<"輸入錯誤!"<<endl;
			return false; 
		}
	}
	for(int i=0;i<obinp.size();i++)
	{
		if(obinp[i]<0)
		{
			cout<<"輸入錯誤!"<<endl;
			return false; 
		}
	}
	
	big_num inp(oinp,obinp);
	big_num ans(0);
	if(inp.the_big()<0)
	{
		cout<<"分母為零"<<endl;
		return false; 
	}
	while(1)
	{
/*		cout<<"原本";
		showID(1);
		show(1);
*/
		big_num tmp_ans((LONG)1);
		tmp=inp;
		LONG ten_time=0,l_time=0;
		
//		cout<<"  tmp.the_num"<<tmp.the_num()<<"  the_num"<<the_num()<<endl;
		while(tmp.the_num()>the_num())
		{
			tmp.right();
			l_time--;
		}
//		cout<<"移動"<<l_time<<endl; 
//		system("pause");
		
		while(tmp.the_num()<the_num())
		{
			tmp.left();
			l_time++;
		}
		
		LONG mult_time;
//		cout<<"取log "<<(LONG)log10(tmp.the_big())<<"    "<<(LONG)log10(the_big())<<endl;
		mult_time=(LONG)(log10(tmp.the_big())-log10(the_big()));
//		cout<<"差了"<<mult_time<<endl;
		while(mult_time<0)
		{
			tmp.multten();
			ten_time++;
			mult_time++;
		}
		while(mult_time>0)
		{
			tmp.divten();
			ten_time--;
			mult_time--;
		}
		if(tmp.the_big()>the_big())
		{
			tmp.divten();
			ten_time--;
		}
		while(compare(tmp)==1)
		{
			tmp.divten();
			ten_time--;
		}
		
		min(tmp);
		for(int i=1;i<=abs(l_time);i++)
		{
			if(l_time>0)
				tmp_ans.left();
			else if(l_time<0)
				tmp_ans.right();
		}
		for(int i=1;i<=abs(ten_time);i++)
		{
			if(ten_time>0)
				tmp_ans.multten();
			else if(ten_time<0)
				tmp_ans.divten();
		}
		
		if(the_num()==(MAX)*(-1))
			break;
#ifdef DEBUG
		cout<<"減去";
		tmp.show(1);
		cout<<"剩餘";
		show(1);
		cout<<"答案加";
		tmp_ans.show(1); 
#endif
		ans.add(tmp_ans);
#ifdef DEBUG
		cout<<"Ans: ";
		ans.show(1); 
		cout<<endl;
		for(int i=1;i<=10000000;i++);
#endif
		
		
		
		if(the_big()<0)
			break;
		
	}
	
	*this=ans;
#ifdef DEBUG
#endif
	return true;
} 
/*-------------------------------------------------------*/
inline bool big_num::div(vector<LONG> oinp)
{
	using namespace EVIR;
	big_num tmp;
	for(int i=0;i<oinp.size();i++)
	{
		if(oinp[i]<0)
		{
			cout<<"輸入錯誤!"<<endl;
			return false; 
		}
	}
	
	big_num inp(oinp);
	big_num ans(0);
	if(inp.the_big()<0)
	{
		cout<<"分母為零"<<endl;
		return false; 
	}
	while(1)
	{
/*		cout<<"原本";
		showID(1);
		show(1);
*/
		big_num tmp_ans(1);
		tmp=inp;
		LONG ten_time=0,l_time=0;
		
//		cout<<"  tmp.the_num"<<tmp.the_num()<<"  the_num"<<the_num()<<endl;
		while(tmp.the_num()>the_num())
		{
			tmp.right();
			l_time--;
		}
//		cout<<"移動"<<l_time<<endl; 
//		system("pause");
		
		while(tmp.the_num()<the_num())
		{
			tmp.left();
			l_time++;
		}
		
		LONG mult_time;
//		cout<<"取log "<<(LONG)log10(tmp.the_big())<<"    "<<(LONG)log10(the_big())<<endl;
		mult_time=(LONG)(log10(tmp.the_big())-log10(the_big()));
//		cout<<"差了"<<mult_time<<endl;
		while(mult_time<0)
		{
			tmp.multten();
			ten_time++;
			mult_time++;
		}
		while(mult_time>0)
		{
			tmp.divten();
			ten_time--;
			mult_time--;
		}
		if(tmp.the_big()>the_big())
		{
			tmp.divten();
			ten_time--;
		}
		while(compare(tmp)==1)
		{
			tmp.divten();
			ten_time--;
		}
		
		min(tmp);
		for(int i=1;i<=abs(l_time);i++)
		{
			if(l_time>0)
				tmp_ans.left();
			else if(l_time<0)
				tmp_ans.right();
		}
		for(int i=1;i<=abs(ten_time);i++)
		{
			if(ten_time>0)
				tmp_ans.multten();
			else if(ten_time<0)
				tmp_ans.divten();
		}
		
		if(the_num()==(MAX)*(-1))
			break;
#ifdef DEBUG
		cout<<"減去";
		tmp.show(1);
		cout<<"剩餘";
		show(1);
		cout<<"答案加";
		tmp_ans.show(1); 
#endif
		ans.add(tmp_ans);
#ifdef DEBUG
		cout<<"Ans: ";
		ans.show(1); 
		cout<<endl;
		for(int i=1;i<=10000000;i++);
#endif
		
		
		
		if(the_big()<0)
			break;
		
	}
	
	*this=ans;
#ifdef DEBUG
#endif
	return true;
} 
/*-------------------------------------------------------*/
inline bool big_num::divten()
{
	div(10);
}
/*-------------------------------------------------------*/
inline bool big_num::right(int n)
{
	for(int i=1;i<=n;i++)
	{
		right();
	}
	return true;
}
/*-------------------------------------------------------*/
inline bool big_num::left(int n)
{
	for(int i=1;i<=n;i++)
	{
		left();
	}
	return true;
}
/*-------------------------------------------------------*/
inline bool big_num::left(void)
{
	int n=num[0].size()-1;
	num[0].push_back(num[0][n]);
	for(int i=n-1;i>=0;i--)
	{
		num[0][i+1]=num[0][i];
	}
	
	n=num[1].size()-1;
	num[0][0]=num[1][0];
	for(int i=1;i<=n;i++)
	{
		num[1][i-1]=num[1][i];
	}
	num[1][n]=0;
	check();
	return true;
} 
/*-------------------------------------------------------*/
inline bool big_num::right(void)
{
	int n=num[1].size()-1;
	num[1].push_back(num[1][n]);
	for(int i=n-1;i>=0;i--)
	{
		num[1][i+1]=num[1][i];
	}
	
	n=num[0].size()-1;
	num[1][0]=num[0][0];
	for(int i=1;i<=n;i++)
	{
		num[0][i-1]=num[0][i];
	}
	num[0][n]=0;
	check();
	return true;
}
/*-------------------------------------------------------*/
inline bool big_num::div(int inp)
{
	using namespace EVIR;
	if(inp<0)
	{
		sb=(!(sb));
		inp=abs(inp);
	}
	else if(inp==0)
	{
		cout<<"分母為0"<<endl;
		return false; 
	}

	LONG tmp=0;
	for(int i=num[0].size()-1;i>=0;i--)
	{
		num[0][i]+=tmp*base;
		tmp=num[0][i]%inp;
		num[0][i]/=inp;
	}
	for(int i=0;i<num[1].size();i++)
	{
		num[1][i]+=tmp*base;
		tmp=num[1][i]%inp;
		num[1][i]/=inp;
		if((tmp!=0)&&(num[1].size()<MAX+1))
		{
			num[1].push_back(0);
		}
	}
	check();
	return true;
}
/*-------------------------------------------------------*/
inline bool big_num::multten()
{
	return mult(10);
}
/*-------------------------------------------------------*/
bool big_num::mult(int inp)
{
	if(inp<0)
	{
		sb=(!(sb));
		inp=abs(inp);
	}
	
	for(int oi=0;oi<2;oi++)
	{
		for(int i=0;i<num[oi].size();i++)
		{
			num[oi][i]*=inp;
		}
	}
	#ifdef DEBUG
		cout<<"ID="<<ID<<endl;
		show();
		cout<<endl;
	#endif
	check();
}
/*-------------------------------------------------------*/
bool big_num::min(int s,int b)
{
	using namespace EVIR;
	if(s<0||b<0)
	{
		cout<<"輸入錯誤"<<endl;
		return false; 
	}
	if(sb==true)
	{
		if(num[0].size()!=1) 
		{ 
			num[0][0]-=s;
			num[1][0]-=b;
		}
		else
		{
			if(num[0][0]>s)
			{
				num[0][0]-=s;
				num[1][0]-=b;
			}
			else if(num[0][0]==s)
			{
				if(num[1][0]>=b)
				{
					num[0][0]-=s;
					num[1][0]-=b;
				}
				else
				{
					num[0][0]=s-num[0][0];
					num[1][0]=b-num[1][0];
					sb=(!(sb));
				}
			} 
			else
			{
				num[0][0]=s-num[0][0];
				num[1][0]=b-num[1][0];
				sb=(!(sb));
			}
		}
	}
	else
	{
		num[0][0]+=s;
		num[1][0]+=b;
	}
	
	check();
	#ifdef DEBUG
		cout<<"-"<<s<<"&"<<b<<endl;
		cout<<"ID="<<ID<<endl;
		show();
		cout<<endl;
	#endif
	return true;
}
/*-------------------------------------------------------*/
bool big_num::add(int s, int b)
{
	using namespace EVIR;
	if(s<0||b<0)
	{
		cout<<"輸入錯誤"<<endl;
		return false; 
	}
	if(sb==true)
	{
		num[0][0]+=s;
		num[1][0]+=b;
	}
	else if(num[0].size()!=1) 
	{
		num[0][0]-=s;
		num[1][0]-=b;
	}
	else
	{
		if(num[0][0]>s)
		{
			num[0][0]-=s;
			num[1][0]-=b;
		}
		else if(num[0][0]==s)
		{
			if(num[1][0]>=b)
			{
				num[0][0]-=s;
				num[1][0]-=b;
			}
			else
			{
				num[0][0]=s-num[0][0];
				num[1][0]=b-num[1][0];
				sb=(!(sb));
			}
		} 
		else
		{
			num[0][0]=s-num[0][0];
			num[1][0]=b-num[1][0];
			sb=(!(sb));
		}
	}
	
	
	#ifdef DEBUG
		cout<<"+"<<s<<"&"<<b<<endl;
		cout<<"ID="<<ID<<endl;
		show();
		cout<<endl;
	#endif
	check();
	return true;
}
/*-------------------------------------------------------*/
bool big_num::minone()
{
	if(sb==false)
	{
		num[0][0]++;
	}
	else
		num[0][0]--;
	check();
	 #ifdef DEBUG
//		cout<<"-1"<<endl;
		cout<<"ID="<<ID<<endl;
		show();
		cout<<endl;
	#endif
	return true;
}
/*-------------------------------------------------------*/
bool big_num::addone()
{
	if(sb==true)
	{
		num[0][0]++;
	}
	else
	{
		num[0][0]--;
	}
	check();
	#ifdef DEBUG
//		cout<<"+1"<<endl;
		cout<<"ID="<<ID<<endl;
		show();
		cout<<endl;
	#endif
	return true;
} 
/*-------------------------------------------------------*/
inline void big_num::cgsb(void)
{
	if(num[0][num[0].size()-1]<0)
	{
		sb=(!sb);
		num[0][num[0].size()-1]=abs(num[0][num[0].size()-1]);
	}
}
/*-------------------------------------------------------*/
void big_num::check(void)
{
	using namespace EVIR;
/*	big_num *tt=new big_num(num[0],num[1],sb);
	tt->cg_name("暫時大數字");
#ifdef DEBUG
	cout<<"ID="<<tt->ID<<endl;
	tt->show();
	cout<<endl;
#endif
*/	
	LONG tmp=0;
//	vector<LONG>::iterator it;
//	vector<LONG> *it;
/*	for(it=num[1].rbegin(); it>=nu[1].rend() ; it--)
	{
		(*it)+=tmp;
		if(*it>base)
		{
			tmp=(*it)/base;
			(*it)%=base;
		}
		else if(*it<0)
		{
			tmp=-1;
			(*it)+=base;
			if(*it<0)
				it++;
		}
	else
		{
			tmp=0;
		}

	}
*/ 
	for(int i=num[1].size()-1;i>=0;i--)
	{
//		if(tmp>0)
			num[1][i]+=tmp;
//		else if(tmp<0)
//			num[1][i]-=abs(tmp);
		if(num[1][i]>=base)
		{
			tmp=num[1][i]/base;
			num[1][i]%=base;
		}
		else if(num[1][i]<0)
		{
			tmp=0;
			do{
				num[1][i]+=base;
				tmp--;
			}while(num[1][i]<0);
//			if(num[1][i]<0)
//				i++;
		}
		else
		{
			tmp=0;
		}
		if(i==0)
		{
			if(tmp>0)
			{
				num[0][0]+=tmp;
				tmp=0;
			}
			else if(tmp<0)
			{
				num[0][0]+=tmp;
				tmp=0;
//				num[1][i]-=base;
				num[1][i]=abs(num[1][i]);
				break;
			}
		}
		 
	}
/*	
	for(it=num[0].begin();it!=num[0].end();it++)
	{
		(*it)+=tmp;
		if(*it>base)
		{
			tmp=(*it)/base;
			(*it)%=base;
		}
		else if(*it<0)
		{
			tmp=-1;
			(*it)+=base;
			if(*it<0)
				it++;
		}
		else
		{
			tmp=0;
		}		
		if((tmp!=0)&&(it==num[0].rbegin()))
		{
			num[0].push_back(0);
		}
	}
*/
bool stop=false;
	for(int i=0;i<num[0].size();i++)
	{

//		if(tmp>0)
			num[0][i]+=tmp;
//		else if(tmp<0)
//			num[1][i]-=abs(tmp);

		if(num[0][i]>=base)
		{
			tmp=num[0][i]/base;
			num[0][i]%=base;
		}
		else if(num[0][i]<0)
		{
			do{
				num[0][i]+=base;
				tmp--;
			}while(num[0][i]<0);
			tmp=0;
//			if(num[0][i]<0)
//				i--;
		}
		else
		{
			tmp=0;
		}
		
		if(i==num[0].size()-1)
		{
			if(tmp>0)
				num[0].push_back(0);
/*			else if((tmp<0)&&(stop==false))
			{
				stop=true;
				sb=(!sb);
				while(tmp!=0)
				{
					num[0][i]-=base;
					num[0][i]++;
					tmp++;
				}
				num[0][i]=abs(num[0][i]);
				break;
			}
*/		}
	}


//	it=num[0].rbegin();
	int i=num[0].size()-1;	
	sb=((num[0][i]>=0)==sb);
	
	while(num[1].size()>MAX)
	{
		num[1].pop_back();
	}
	
	clear();
//	delete tt;
} 
/*-------------------------------------------------------*/
void big_num::clear(void)
{
	using namespace EVIR;
	for(int i=0;i<2;i++)
	{
		int j;
		j=num[i].size()-1;
		while((num[i][j]==0)&&(j>0))
		{
			num[i].pop_back();
			j=num[i].size()-1;	
		}
/*
		while((*(num[i].rbegin())==0)&&(num[i].rbegin()!=num[i].rend()))
			num[i].pop_back();
*/
	}
} 
/*-------------------------------------------------------*/
big_num::big_num(vector<LONG> inpa,vector<LONG> inpb,int isb)
{
	using namespace EVIR;
	sb=(isb==0);
	num[0]=inpa;
	num[1]=inpb;
	bool check_inp=true;
	for(int oi=0;oi<2;oi++)
	{
		for(int i=0;i<num[oi].size();i++)
		{
			if(!check_inp)
				break;
			if(num[oi][i]<0)
			{
				cout<<"輸入有錯!!"<<endl;
				check_inp=false;
				break;
			}
		}
	}
	if(check_inp)
	{	
		sb=true;
		char name[50];
		sprintf(name,"default-%d",cnt);
		cnt++;
		ID=name;
		check();
	#ifdef DEBUG
		cout<<"ID="<<ID<<endl;
		show();
		cout<<endl;
	#endif
	}
	else
	{
		delete this;
		exit(1);
	}
}
/*-------------------------------------------------------*/
big_num::big_num(vector<LONG> inpa)
{
	using namespace EVIR;
	num[0]=inpa;
	bool check_inp=true;
	for(int i=0;i<num[0].size();i++)
	{
		if(!check_inp)
			break;
		if(num[0][i]<0)
		{
			cout<<"輸入有錯!!"<<endl;
			check_inp=false;
			break;
		}
	}
	if(check_inp)
	{	
		sb=true;
		num[1].push_back(0);
		char name[50];
		sprintf(name,"default-%d",cnt);
		cnt++;
		ID=name;
		check();
	#ifdef DEBUG
		cout<<"ID="<<ID<<endl;
		show();
		cout<<endl;
	#endif
	}
	else
	{
		delete this;
		exit(1);
	}
}
/*-------------------------------------------------------*/
big_num::~big_num()
{
	#ifdef DEBUG
		cout<<"ID="<<ID;
		cout<<" 解構"<<endl;
	#endif	
}
/*-------------------------------------------------------*/
big_num::big_num(LONG s,LONG d,LONG tsb)
{
	using namespace EVIR;
	sb=(tsb==0);
	num[0].push_back(abs(s));
	num[1].push_back(abs(d)*base/10);
	char name[50];
	sprintf(name,"default-%d",cnt);
	cnt++;
	ID=name;
	check();
	#ifdef DEBUG
		cout<<"ID="<<ID<<endl;
		show();
		cout<<endl;
	#endif
}

/*-------------------------------------------------------*/

inline void big_num::cg_name(string name)
{
	ID=name;
	cout<<"已經更改名稱為"<<ID<<endl; 
}

/*-------------------------------------------------------*/
big_num::big_num(void){
	using namespace EVIR;
	
	sb=true;
	num[0].push_back(0);
	num[1].push_back(0);
	char name[100];
	sprintf(name,"default-%d",cnt);
	ID=name;
	cnt++;
	
	#ifdef DEBUG
		cout<<"ID="<<ID<<endl;
		show();
		cout<<endl;
	#endif
}
/*-------------------------------------------------------*/
inline void big_num::show(int nl)
{
	if(sb==false)
		cout<<'-';
	for(int oi=0;oi<2;oi++)
	{
		int i;
		for((oi==0)?i=num[oi].size()-1:i=0;
			(oi==0)?i>=0:i<num[oi].size();
			(oi==0)?i--:i++)
			{
				if((oi==0)&&(i==num[oi].size()-1))
					cout<<num[oi][i]<<' ';
				else
					printf("%05d ",num[oi][i]);
				
				if((oi==0)&&(i==0))
					cout<<"\b.";
			}
	}
	if(nl!=0)
		cout<<endl;
}
/*-------------------------------------------------------*/
big_num::big_num(string input_num)
{
    int status=0;
    int dcnt=0;
    bool insb=true;
    for(int i=0;i<input_num.length();i++)
    {
//    	show(1);
        if((char)input_num[i]>='0'&&(char)input_num[i]<='9'||(char)input_num[i]=='.'||(char)input_num[i]=='-')
        {
            if((char)input_num[i]=='.')
            {
                if(status!=0)
                {
                    cout<<"error!!"<<endl;
                    exit(0);
                }
                else
                    status=1;
                continue;
            }
            else if(input_num[i]=='-'&&i==0)
            {
            	insb=sb=false;
	            num[0].push_back(0);
	            num[1].push_back(0);
	            continue;
            }
            else if(input_num[i]=='-')
            {
            	cout<<"error!!"<<endl;
            	exit(0);
            }
        }
        else
        {
            cout<<"error!!"<<endl;
            exit(0);
        }
        if(i==0)
        {
            num[0].push_back(0);
            num[1].push_back(0);
            
            multten();
            add((int)((char)input_num[i]-'0'));

    	}
		else
        {
            multten();
            add((int)((char)input_num[i]-'0'));

        }
        if(status==1)
        {
            dcnt++;
        }
    }
    for(int i=1;i<=dcnt;i++)
    {
    	divten();
    }
    sb=insb;
}
/*-------------------------------------------------------*/
#undef OUTN
#undef EVIR
/*-------------------------------------------------------*/
/*-------------------------------------------------------*/

