// test-difficult string.cpp : 定义控制台应用程序的入口点。
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
const int maxn = 26;
int s[maxn];
int n;
int L;
int cnt;
int dfs(int cur)
{
	if(cnt++==n)
	{
		for(int i = 0;i<cur;i++)
			printf("%c",'A'+s[i]);
		printf("\n");
		return 0;
	}
	else
	{
		for(int i = 0;i<L;i++)
		{
			s[cur] = i;
			int ok = 1;
			for(int j = 1;j*2<=cur+1;j++)
			{
				int equal = 1;
				for(int k = 0;k<j;k++)
				{
					if(s[cur-k]!=s[cur-j-k])
					{
						equal = 0;
						break;
					}
				}
				if(equal)
				{
					ok = 0;
					break;
				}
			}
			if(ok)
				if(!dfs(cur+1))
					return 0;//find a string
		}
	}
	return 1;
}

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	scanf("%d%d",&n,&L);
	dfs(0);
	return 0;
}

