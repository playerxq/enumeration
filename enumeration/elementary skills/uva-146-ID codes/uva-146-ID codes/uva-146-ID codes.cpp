// uva-146-ID codes.cpp : 定义控制台应用程序的入口点。
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
char s[60];
int str[60];

int get_next_perm(int* a,int len)
{
	int i = len-2;
	int min = 30;
	int min_i = 0;
	while(i>=0)
	{
		min = 30;
		min_i = i;
		int j;
		for(j = i+1;j<len;j++)
		{
			if(a[j]>a[i]&&min>a[j])
			{
				min_i = j;
				min = a[j];
			}
		}
		if(min_i==i)
		{
			i--;
			continue;
		}
		int temp = a[i];
		a[i] = a[min_i];
		a[min_i] = temp;
		sort(a+i+1,a+i+1+len-i-1);
		return 1;
	}
	return 0;
}

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	while(scanf("%s",s))
	{
		if(s[0]=='#')
			break;
		int len = strlen(s);
		for(int i = 0;i<len;i++)
		{
			str[i] = s[i]-'a';
		}
		if(!get_next_perm(str,len))
			printf("No Successor\n");
		else
		{
			for(int i = 0;i<len;i++)
				s[i] = str[i]+'a';
			printf("%s\n",s);
		}
	}
	return 0;
}

