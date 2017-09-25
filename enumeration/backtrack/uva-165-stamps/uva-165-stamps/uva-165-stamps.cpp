// uva-165-stamps.cpp : 定义控制台应用程序的入口点。
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
const int maxl = 10000;
int h,k;
int x[10];//升序
//已经选定x[1:i-1]的最大连续邮资区间为1:r，则x[i]可以选的值为x[i-1]+1:r+1
int bestx[10];//当前最优解
int maxvalue;
int y[maxl+1];//使用不超过h张x[1:i]的邮票贴出k的最少票数y[k]
const int maxint = 1<<30;

void dfs(int cur, int r)//r-1为1:cur-2的连续邮资上届
{
	for(int i = 0;i<=x[cur-2]*(h-1);i++)
	{
		if(y[i]<h)//前cur-2张构成的某个邮资i用的票数少于h 则可以用h-y[i]来增加x[cur-1]
		{
			for(int j = 1;j<=h-y[i];j++)
			{
				if(y[i]+j<y[i+x[cur-1]*j])
					y[i+x[cur-1]*j] = y[i]+j;
			}
		}
	}
	//计算1:cur-1的连续区间r
	while(y[r]<maxint) r++;//r-1为1:cur-1的上届
	if(cur>k)
	{
		if(r-1>maxvalue)
		{
			maxvalue = r-1;
			for(int i = 1;i<=k;i++)
				bestx[i] = x[i];
		}
		return;
	}
	int* z = new int[maxl+1];
	for(int i = 1;i<=maxl;i++)
		z[i] = y[i];
	for(int  j=x[cur-1]+1;j<=r;j++)
	{
		x[cur] = j;
		dfs(cur+1,r);
		for(int i = 1;i<=maxl;i++)
			y[i] = z[i];
	}
	delete[] z;
}


int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	while(scanf("%d%d",&h,&k))
	{
		if(h==0&&k==0)
			break;
		memset(x,0,sizeof(x));
		memset(y,0,sizeof(y));
		x[1] = 1;
		y[0] = 0;
		maxvalue = 0;
		for(int i = 1;i<maxl+1;i++)
			y[i] = maxint;
		dfs(2,1);
		for(int i = 1;i<=k;i++)
		{
			printf("%3d",bestx[i]);
		}
		printf(" ->%3d\n",maxvalue);
	}
	return 0;
}

