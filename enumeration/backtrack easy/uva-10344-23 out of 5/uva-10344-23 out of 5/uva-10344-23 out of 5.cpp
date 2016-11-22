// uva-10344-23 out of 5.cpp : 定义控制台应用程序的入口点。
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
int a[5];

int dfs(int cur,int sum)
{
	int res = 0;
	int temp;
	if(cur==5)
	{
		if(sum==23)
			return 1;
		else 
			return 0;
	}
	for(int i = cur;i<5;i++)
	{
		if(cur==0)
		{
			temp = a[0];
			a[0] = a[i];
			a[i] = temp;
			res = dfs(cur+1,a[0]);
			if(res)
				return 1;
			temp = a[0];
			a[0] = a[i];
			a[i] = temp;
		}
		else
		{
			temp = a[cur];
			a[cur] = a[i];
			a[i] = temp;
			res = dfs(cur+1,sum+a[cur])|dfs(cur+1,sum-a[cur])|dfs(cur+1,sum*a[cur]);
			if(res)
				return 1;
			temp = a[cur];
			a[cur] = a[i];
			a[i] = temp;
		}
	}
	return 0;
}

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	while(scanf("%d%d%d%d%d",&a[0],&a[1],&a[2],&a[3],&a[4]))
	{
		if(a[0]==0&&a[1]==0&&a[2]==0&&a[3]==0&&a[4]==0)
			break;
		int res = dfs(0,0);
		if(res)
			printf("Possible\n");
		else
			printf("Impossible\n");
	}
	return 0;
}

