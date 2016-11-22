// hdu-1496-equations.cpp : 定义控制台应用程序的入口点。
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
int f1[1000001];//正的
int f2[1000001];//负的
int a,b,c,d;
int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
	while(scanf("%d %d %d %d",&a,&b,&c,&d)!=EOF)
	{
		if((a<0&&b<0&&c<0&&d<0)||(a>0&&b>0&&c>0&&d>0))
		{
			printf("0\n");
			continue;
		}
		memset(f1, 0, sizeof(f1));  
        memset(f2, 0, sizeof(f2));  
		int k,sum;
		for(int i = 1;i<=100;i++)
		{
			for(int j = 1;j<=100;j++)
			{
				k = a*i*i+b*j*j;
				if(k>=0) f1[k]++;
				else
					f2[-k]++;
			}
		}
		sum = 0;
		for(int i = 1;i<=100;i++)
		{
			for(int j = 1;j<=100;j++)
			{
				k = c*i*i+d*j*j;
				if(k>0)
					sum+=f2[k];//恰好为0的匹配数
				else
					sum+=f1[-k];
			}
		}
		printf("%d\n",16*sum);
	}
}

