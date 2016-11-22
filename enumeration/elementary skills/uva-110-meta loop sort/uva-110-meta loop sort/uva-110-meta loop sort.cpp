// uva-110-meta loop sort.cpp : 定义控制台应用程序的入口点。
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
int a[10];
int s[10];
int used[10];
void dfs(int cur,int n_space)
{
	if(cur==n)
	{
		for(int i = 0;i<n_space;i++)
			printf(" ");
		printf("writeln(");
		for(int i = 0;i<n-1;i++)
			printf("%c,",s[i]+'a');
		printf("%c)\n",s[n-1]+'a');
		return;
	}
	//当前只扩展a[cur]
	int temp;
	for(int m = 0;m<n_space;m++)
		printf(" ");
	printf("if %c < %c then\n",a[cur]+'a',s[0]+'a');
	temp = s[cur];
	for(int k = cur;k>0;k--)
		s[k] = s[k-1];
	s[0] = a[cur];
	dfs(cur+1,n_space+2);
	for(int k = 0;k<cur;k++)
		s[k] = s[k+1];
	s[cur] = temp;
	for(int j = 1;j<cur;j++)
	{
		for(int i = 0;i<n_space;i++)
				printf(" ");
		printf("else if %c < %c then\n",a[cur]+'a',s[j]+'a');
		temp = s[cur];
		for(int k = cur;k>j;k--)
			s[k] = s[k-1];
		s[j] = a[cur];
		dfs(cur+1,n_space+2);
		for(int k = j;k<cur;k++)
			s[k] = s[k+1];
		s[cur] = temp;
	}
	for(int m = 0;m<n_space;m++)
		printf(" ");
	printf("else\n");
	temp = s[cur];
	s[cur] = a[cur];
	dfs(cur+1,n_space+2);
	s[cur] = temp;
}


void output()
{
	s[0] = 0;
	dfs(1,2);
}

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int T;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		memset(s,0,sizeof(s));
		memset(used,0,sizeof(used));
		for(int i = 0;i<10;i++)
			a[i] = i;
		printf("program sort(input,output);\n");
		printf("var\n");
		for(int i = 0;i<n-1;i++)
			printf("%c,",'a'+i);
		printf("%c ",'a'+n-1);
		printf(": integer;\n");
		printf("begin\n");
		printf("  readln(");
		for(int i = 0;i<n-1;i++)
			printf("%c,",'a'+i);
		printf("%c);\n",'a'+n-1);
		output();
		printf("end.\n");
		if(T)
			printf("\n");
	}
	return 0;
}

