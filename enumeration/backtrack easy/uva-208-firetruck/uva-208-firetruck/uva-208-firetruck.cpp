// uva-208-firetruck.cpp : 定义控制台应用程序的入口点。
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
int des;
int edge[25][25];
int foyld[25][25];//whether des can reach using different points
int vis[25];
int path[25];
int sum;
int count_node;
const int maxint = 1<<15;

void dfs(int cur,int cnt)
{
	if(cur==des)
	{
		for(int i = 0;i<cnt-1;i++)
			printf("%d ",path[i]);
		printf("%d\n",path[cnt-1]);
		sum++;
		return;
	}
	for(int i = 1;i<=count_node;i++)
	{
		if(vis[i]==0&&edge[cur][i]&&foyld[i][des]!=maxint)
		{
			vis[i] = 1;
			int t = path[cnt];
			path[cnt] = i;
			dfs(i,cnt+1);
			vis[i] = 0;
			path[cnt] = t;
		}
	}
}

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int ncase = 1;
	while(scanf("%d",&des)!=EOF)
	{
		int from,to;
		memset(edge,0,sizeof(edge));
		memset(vis,0,sizeof(vis));
		memset(path,0,sizeof(path));
		for(int i = 0;i<25;i++)
			for(int j = 0;j<25;j++)
				foyld[i][j] = maxint;
		while(scanf("%d%d",&from,&to))
		{
			if(from==0&&to==0)
				break;
			edge[from][to] = 1;
			edge[to][from] = 1;
			foyld[from][to] = 1;
			foyld[to][from] = 1;
			if(from>count_node)
				count_node = from;
			if(to>count_node)
				count_node = to;
		}
		for(int k = 1;k<=count_node;k++)
		{
			for(int i = 1;i<=count_node;i++)
			{
				for(int j = 1;j<=count_node;j++)
				{
					if(foyld[i][j]>foyld[i][k]+foyld[k][j])//i->j由i->k k->j更新
						foyld[i][j] = foyld[i][k]+foyld[k][j];
				}
			}
		}
		printf("CASE %d:\n",ncase++);
		sum = 0;
		vis[1] = 1;
		path[0] = 1;
		dfs(1,1);
		printf("There are %d routes from the firestation to streetcorner %d.\n",sum,des);
	}
	return 0;
}

