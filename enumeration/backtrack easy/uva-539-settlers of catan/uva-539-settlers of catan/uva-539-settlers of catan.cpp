// uva-539-settlers of catan.cpp : 定义控制台应用程序的入口点。
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
int n,r;
int edge[30][30];
int used[30][30];
int longest_path;
int temp_path;

int dfs(int cur)
{
	for(int i = 0;i<n;i++)
	{
		if(edge[cur][i]==1&&used[cur][i]==0)
		{
			used[cur][i] = 1;
			used[i][cur] = 1;
			temp_path++;
			
			if(temp_path>longest_path)
				longest_path = temp_path;
			dfs(i);
			temp_path--;
			used[cur][i] = 0;
			used[i][cur] = 0;
		}
	}
	return temp_path;
}

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	while(scanf("%d%d",&n,&r))
	{
		if(n==0&&r==0)
			break;
		memset(edge,0,sizeof(edge));
		memset(used,0,sizeof(used));
		int node1,node2;
		for(int i = 0;i<r;i++)
		{
			scanf("%d%d",&node1,&node2);
			edge[node1][node2] = 1;
			edge[node2][node1] = 1;
		}
		temp_path = longest_path = 0;
		for(int i = 0;i<n;i++)
			dfs(i);
		printf("%d\n",longest_path);
	}
	return 0;
}

