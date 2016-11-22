// uva-167-successor.cpp : 定义控制台应用程序的入口点。
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
int a[8][8];
int maxv[8];
int vis[3][20];
int maxn;

void get_max()
{
	for(int i = 0;i<8;i++)
	{
		int maxt = 0;
		for(int j = 0;j<8;j++)
		{
			if(maxt<a[i][j])
				maxt = a[i][j];
		}
		maxv[i] = maxt;
	}
}

int ok(int x, int y,int sum)
{
	if(!vis[0][y] && !vis[1][x+y] && !vis[2][x-y+8])
	{
		sum+= a[x][y];
		for(int i = x+1;i<8;i++)
		{
			sum+=maxv[i];
		}
		if(sum<maxn)
			return 0;
		else 
			return 1;
	}
	return 0;
}
void dfs(int cur,int sum)
{
	if(cur==8)
	{
		if(sum>maxn)
			maxn = sum;
		return;
	}
	for(int i = 0;i<8;i++)
	{
		if(ok(cur,i,sum))
		{
			vis[0][i] = vis[1][cur+i] = vis[2][cur-i+8] = 1;
			dfs(cur+1,sum+a[cur][i]);
			vis[0][i] = vis[1][cur+i] = vis[2][cur-i+8] = 0;
		}
	}
}

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int k;
	scanf("%d",&k);
	while(k--)
	{
		for(int i = 0;i<8;i++)
			for(int j = 0;j<8;j++)
				scanf("%d",&a[i][j]);
		maxn = 0;
		memset(vis,0,sizeof(vis));
		get_max();
		dfs(0,0);
		printf("%5d\n",maxn);
	}
	return 0;
}
