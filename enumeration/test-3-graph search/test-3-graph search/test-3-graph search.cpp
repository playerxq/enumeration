// test-3-graph search.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <cstdio>
#include <iostream>
#include <string.h>
#include <math.h>
#include<iomanip>
#include <ctype.h>
#include <algorithm>
using namespace std;
const int maxn = 30;

int d;
int e;
int f;
int a,b;
int v[maxn];
int res[maxn];
int min_m = maxn*maxn;//最小分数的父母要尽可能小
int min_d;
int ok;
int sub_ok;
void dfs(int cur)
{
	if(cur==d&&e*b==a*f)//e/f == a/b
	{
		if(v[d-1]<min_m)
		{
			for(int i = 0;i<d;i++)
			{
				res[i] = v[i];//保存结果
			}
		}
		min_d = d;
		ok = 1;
		sub_ok = 1;//当前分支结束
	}
	else
	{
		int t = b*f;
		int s = a*f - e*b;
		int h = 0;
		if(s<0)
			return;
		if(cur>0)
			h = v[cur-1]+1;
		else
			h = 2;
		while((d-cur)*t>=s*h)
		{
			v[cur] = h;
			e = e*h + f;
			f = f*h;
			//if(!dfs(cur+1))
			dfs(cur+1);
				//return 0;
			f = f/h;
			e = (e-f)/h;
			if(cur==d-1&&sub_ok)
			{
				sub_ok = 0;
				return;
			}
			h++;
		}
;
	}
}

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	scanf("%d%d",&a,&b);
	d = 1;
	while(d<maxn&&!ok)
	{
		e = 0;
		f = 1;
		memset(v,0,sizeof(v));
		memset(res,0,sizeof(res));
		dfs(0);
		d++;
	}
	for(int i = 0;i<min_d;i++)
	{
		printf("1/%d",res[i]);
		if(i<min_d-1)
			printf("+");
	}
	printf("\n");
	return 0;
}

