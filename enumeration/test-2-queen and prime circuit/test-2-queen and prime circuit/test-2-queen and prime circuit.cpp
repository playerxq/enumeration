// test-2-queen and prime circuit.cpp : 定义控制台应用程序的入口点。
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
const int maxn = 20;
//queen
/*

int vis[3][maxn];
int n;
int tot;
void search(int cur)
{
	int i,j;
	if(cur==n)
	{
		tot++;
	}
	else
	{
		for(i = 0;i<n;i++)
		{
			if(!vis[0][i]&&!vis[1][cur+i]&&!vis[2][cur-i+n])
			{
				vis[0][i] = vis[1][i+cur] = vis[2][cur-i+n] = 1;
				search(1+cur);
				vis[0][i] = vis[1][i+cur] = vis[2][cur-i+n] = 0;
			}
		}
	}
}

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	memset(vis,0,sizeof(vis));
	scanf("%d",&n);
	search(0);
	printf("%d\n",tot);
	return 0;
}

*/
// prime circuit
int n;
int a[maxn];
int vis[maxn];
int is_prime[maxn+maxn];
void judge_prime()
{
	is_prime[1] = is_prime[2] = 0;
	for(int i = 2;i<maxn+maxn;i++)
	{
		if(is_prime[i]==0)
		{
			for(int j= i+i;j<maxn+maxn;j+=i)
				is_prime[j] = 1;
		}
	}
}

void dfs(int cur)
{
	if(cur == n+1 && !is_prime[a[cur-1]+a[1]])
	{
		for(int i = 1;i<=n;i++)
			printf("%d ",a[i]);
		printf("\n");
		return;
	}
	else
	{
		for(int i = 2;i<=n;i++)
		{
			if(vis[i]==0&&!is_prime[i+a[cur-1]])
			{
				a[cur] = i;
				vis[i] = 1;
				dfs(cur+1);
				vis[i] = 0;
			}
		}
	}
}

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	memset(vis,0,sizeof(vis));
	memset(a,0,sizeof(a));
	memset(is_prime,0,sizeof(is_prime));
	scanf("%d",&n);
	judge_prime();
	a[1] = 1;
	dfs(2);
	return 0;
}