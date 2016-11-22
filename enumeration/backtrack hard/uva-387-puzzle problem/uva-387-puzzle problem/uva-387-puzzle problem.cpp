// uva-387-puzzle problem.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <cstdio>
#include <iostream>
#include <string.h>
#include <vector>
#include <math.h>
#include<iomanip>
#include <ctype.h>
#include <algorithm>
using namespace std;
int num;
int a[4][4];
typedef unsigned int form;
form all_piece;
typedef vector<form> form_piece;//某个piece的所有掩码
typedef vector<form_piece> ve;//所有piece的掩码
vector<form> res;
typedef struct node
{
	int ro;
	int co;
} node;
void get_min_max(int r, int c,node* maxn )//得到piece最左下和右上的点
{
	for(int i = 0;i<r;i++)
	{
		for(int j = 0;j<c;j++)
		{
			if(a[i][j]==1)
			{
				if(i>maxn->ro)
					maxn->ro = i;
				if(j>maxn->co)
					maxn->co = j;
			}
		}
	}
}
void translate(form_piece& fo_piece,node maxn)//将piece移到子图左下脚
{
	//
	form form_p;//掩码
	form_p = 0;
	for(int i = 0;i<4;i++)
	{
		for(int j = 0;j<4;j++)
		{
			if(a[i][j])
				form_p |= 1<<(i*4+j);//计算掩码  16位
		}
	}
	unsigned int temp = form_p;
	for(int i = 0;i<4-maxn.ro;i++)
	{
		for(int j = 0;j<4-maxn.co;j++)
		{
			form_p<<=(4*i+j);
			fo_piece.push_back(form_p);
			form_p = temp;
		}
	}	
}
int ok(unsigned short int a, unsigned short int b)
{
	unsigned int t = a&b;
	if(t!=0)
		return 0;
	return 1;
}
int dfs(int cur,unsigned int all,ve& v)
{
	if(cur==num)
	{
		if((all&0xFFFF)==0xFFFF)
			return 1;
		return 0;
	}
	for(int i = 0;i<v[cur].size();i++)
	{
		if(ok(all,v[cur][i]))
		{
			all|=v[cur][i];
			res.push_back(v[cur][i]);
			if(dfs(cur+1,all,v))
			{
				return 1;
			}
			res.pop_back();
			all&=(~v[cur][i]);
		}
	}
	return 0;
}
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int case_p = 1;
	while(scanf("%d",&num))
	{
		if(num==0)
			break;
		if(case_p!=1)
			printf("\n");
		case_p++;
		ve ve_piece;
		all_piece = 0;
		ve_piece.clear();
		res.clear();
		for(int i = 0;i<num;i++)
		{
			int r,c;
			scanf("%d%d",&r,&c);
			getchar();
			char ch;
			memset(a,0,sizeof(a));
			for(int j = 0;j<r;j++)
			{
				for(int k = 0;k<c;k++)
				{
					scanf("%c",&ch);
					a[j][k] = ch-'0';
				}
				getchar();
			}
			node minn,maxn;
			maxn.co = maxn.ro = 0;
			get_min_max(r,c,&maxn);
			form_piece pe;
			translate(pe,maxn);
			ve_piece.push_back(pe);
		}
		//
		int f = dfs(0,0,ve_piece);
		//out res
		if(!f)
		{
			printf("No solution possible\n");
		}
		else
		{
			unsigned int t;
			for(int i = num-1;i>=0;i--)
			{
				t = res[i];
				res.pop_back();
				for(int j = 0;j<16;j++)
				{
					if((t&(1<<j))!=0)
						a[j/4][j%4] = i+1;
				}
			}
			for(int i = 0;i<4;i++)
			{
				for(int j = 0;j<4;j++)
				{
					printf("%d",a[i][j]);
				}
				printf("\n");
			}
		}
	}
	return 0;
}

