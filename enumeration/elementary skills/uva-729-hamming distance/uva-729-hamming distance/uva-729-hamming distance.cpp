// uva-729-hamming distance.cpp : 定义控制台应用程序的入口点。
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
int a[20];
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int T;
	int N,H;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&N,&H);
		memset(a,0,sizeof(a));
		for(int i = N-H;i<N;i++)
			a[i] = 1;
		do
		{
			for(int i = 0;i<N;i++)
				printf("%d",a[i]);
			printf("\n");
		}while(next_permutation(a,a+N));
		if(T)
			printf("\n");
	}
	return 0;
}

