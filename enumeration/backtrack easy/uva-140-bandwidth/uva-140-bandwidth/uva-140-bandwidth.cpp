// uva-140-bandwidth.cpp : 定义控制台应用程序的入口点。
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
char s[100];
char temp[12];
int edge[30][30];
int len;
int cnt;
int minx;
char name[10];
char best[10];
int used[10];
int band[10];
void swap_s(int a, int b)
{
	char t = name[a];
	name[a] = name[b];
	name[b] = t;
}
void insert(char c)
{
	for(int i = 0;i<cnt;i++)
		if(name[i]==c)
			return;
	name[cnt++] = c;
}
void dfs(int cur,int m)
{
	if(cur==cnt)
	{
		if(m<minx)
		{
			for(int i = 0;i<cnt;i++)
				best[i] = name[i];
			minx = m;
		}
		return;
	}
	else
	{
		for(int i = cur;i<cnt;i++)
		{
			swap_s(cur,i);
			if(strcmp(name,"CDBGAFEH")==0)
			{
				int p = 1;
			}
			int t = band[cur];
			for(int j = cur-1;j>=0;j--)
			{
				if(edge[name[cur]-'A'][name[j]-'A']==1||edge[name[j]-'A'][name[cur]-'A']==1)
				{
					band[cur] = cur-j;
				}
			}
			int temp_max = 0;
			for(int k = 0;k<cnt;k++)
			{
				if(band[k]>temp_max)
					temp_max = band[k];
			}
			if(temp_max<=minx)
				dfs(cur+1,temp_max);
			band[cur] = t;
			swap_s(cur,i);
		}
	}
}

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	while(gets(s))
	{
		if(s[0]=='#')
			break;
		
		memset(edge,0,sizeof(edge));
		len = strlen(s);
		int i = 0;
		cnt = 0;
		while(i<len)
		{
			memset(temp,0,sizeof(temp));
			int l = 0;
			while(i<len&&s[i]!=';')
			{
				temp[l++] = s[i];
				i++;
			}
			insert(temp[0]);
			for(int j = 2;j<strlen(temp);j++)
			{
				edge[temp[0]-'A'][temp[j]-'A'] = 1;
				edge[temp[j]-'A'][temp[0]-'A'] = 1;
				insert(temp[j]);
			}
			i++;
		}
		minx = 1<<15;
		sort(name,name+cnt);
		for(int i = 0;i<cnt;i++)
		{
			memset(band,0,sizeof(band));
			swap_s(0,i);
			dfs(1,0);
			swap_s(0,i);
		}
		for(int i = 0;i<cnt;i++)
		{
			printf("%c ",best[i]);
		}
		printf("-> %d\n",minx);
	}
	return 0;
}

