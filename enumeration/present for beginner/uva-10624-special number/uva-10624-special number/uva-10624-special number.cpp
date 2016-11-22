// uva-10624-special number.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <cstdio>
#include <iostream>
#include <string.h>
#include <math.h>
#include <vector>
#include<iomanip>
#include <ctype.h>
#include <algorithm>
using namespace std;
int n,m;
char a[35];
int mod(int k)
{
	int res = 0;
	for(int i = 0;i<k;i++)
	{
		res = (res*10+a[i])%(k);
	}
	return res;
}
int dfs(int cur)
{
	if(cur>=m)
		return 1;
	for(int i = 0;i<10;i++)
	{
		if(cur==0&&i==0)
			continue;
		a[cur] = i;
		if(cur<n-1||(cur>=n-1&&!mod(cur+1)))
		{
			if(dfs(cur+1))
				return 1;
		}
	}
	return 0;
}
int main()
{
	//freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	int t;
	int ncase = 1;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d",&n,&m);
		memset(a,0,sizeof(a));
		printf("Case %d: ",ncase++);
		int res = dfs(0);
		if(res)
		{
			for(int i = 0;i<m;i++)
			{
				printf("%c",a[i]+'0');
			}
		}
		else
		{
			printf("-1");
		}
		printf("\n");
	}
	return 0;
}

