// test.cpp : 定义控制台应用程序的入口点。
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
int s[10];
int comp(const void* a, const void* b)
{
	return *((int*)a)-*((int*)b);
}

void swap_s(int* a, int l, int r)
{
	int temp = a[l];
	a[l] = a[r];
	a[r] = temp;
}
int countx;
void perm(int* a, int len, int start)
{
	if(start == len)
	{
		for(int i = 0;i<len;i++)
			printf("%d ",a[i]);
		printf("\n");
		++countx;
		return;
	}
	for(int i = start;i<len;i++)
	{
		if(i==start)
		{
			perm(a,len,start+1);
		}
		else
		{
			int j;
			for(j = start;j<i;j++)
			{
				if(a[j]==a[i])
					break;
			}
			if(j==i)
			{
				swap_s(a,start,i);
				perm(a,len,start+1);
				swap_s(a,start,i);
			}
		}
	}
}

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	memset(s,0,sizeof(s));
	int t = 0;
	int n = 0;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		for(int i = 0;i<n;i++)
			scanf("%d",&s[i]);
		qsort(s,n,sizeof(int),comp);
		countx = 0;
		perm(s,n,0);
		printf("%d\n",countx);
	}
	return 0;
}
