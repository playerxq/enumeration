// uva-639-dont get rooked.cpp : 定义控制台应用程序的入口点。
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
char s[5][5];
int used[5][5];
int temp_res;
int maxn;
int dfs(int x, int y)
{
	for(int i = 0;i<n;i++)
	{
		for(int j = 0;j<n;j++)
		{
			if(s[i][j]=='.'&&used[i][j]==0)
			{
				int ok = 1;
				for(int k = i-1;k>=0&&ok;k--)//up
				{
					if(used[k][j]==1)
					{
						ok = 0;
						break;
					}
					else if(s[k][j]=='X')
					{
						ok = 1;
						break;
					}
					else
						continue;
				}
				for(int k = i+1;k<n&&ok;k++)//down
				{
					if(used[k][j]==1)
					{
						ok = 0;
						break;
					}
					else if(s[k][j]=='X')
					{
						ok = 1;
						break;
					}
					else
						continue;
				}
				for(int k = j-1;k>=0&&ok;k--)//left
				{
					if(used[i][k]==1)
					{
						ok = 0;
						break;
					}
					else if(s[i][k]=='X')
					{
						ok = 1;
						break;
					}
					else
						continue;
				}
				for(int k = j+1;k<n&&ok;k++)//right
				{
					if(used[i][k]==1)
					{
						ok = 0;
						break;
					}
					else if(s[i][k]=='X')
					{
						ok = 1;
						break;
					}
					else
						continue;
				}
				if(ok)
				{
					used[i][j] = 1;
					temp_res++;
					dfs(i,j);
					if(temp_res>maxn)
						maxn = temp_res;
					temp_res--;
					used[i][j] = 0;
				}
			}//end if
		}
	}//end for
	return temp_res;
}

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	while(scanf("%d",&n))
	{
		if(n==0)
			break;
		getchar();
		memset(s,0,sizeof(s));
		for(int i = 0;i<n;i++)
			gets(s[i]);
		memset(used,0,sizeof(used));
		maxn = 0;
		for(int i = 0;i<n;i++)
		{
			for(int j = 0;j<n;j++)
			{
				if(s[i][j]=='.')
				{
					used[i][j] = 1;
					temp_res = 1;
					dfs(i,j);
					if(temp_res>maxn)
						maxn = temp_res;
					temp_res = 0;
					used[i][j] = 0;
				}
			}
		}
		printf("%d\n",maxn);
	}
	return 0;
}

