// uva-529-addition chain.cpp : 定义控制台应用程序的入口点。
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
int n;
int min_len;
int a[10010];
int b[10010];
int dfs(int cur)
{
	if(a[cur-1]==n)
	{
		if(cur<=min_len)
		{
			min_len = cur;
			for(int i = 0;i<cur;i++)
				b[i] = a[i];
		}
		return 1;
	}
	for(int i = cur-1;i>=0;i--)
	{
		if(a[cur-1]+a[i]<=n)
		{
			a[cur] = a[cur-1]+a[i];
			if(a[cur]*pow(2,(double)(min_len-cur-1))>=n)
			{
				dfs(cur+1);
			}
		}
	}
}
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	while(scanf("%d",&n))
	{
		if(n==0)
			break;
		memset(a,0,sizeof(a));
		memset(b,0,sizeof(b));
		min_len = n;
		a[0] = 1;
		dfs(1);
		for(int i = 0;i<min_len-1;i++)
				printf("%d ",b[i]);
		printf("%d\n",b[min_len-1]);
	}
	return 0;
}

