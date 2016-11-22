// uva-216-get in line.cpp : 定义控制台应用程序的入口点。
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
int num;
int location[10][2];
double feet[10];
int res[10];
int temp_res[10];
double sum;
double minx;

void swap_s(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

double get_dis(int a, int b)
{
	double x = location[b][0]-location[a][0];
	double y = location[b][1]-location[a][1];
	return sqrt((double)(x*x+y*y));
}

int perm(int cur)
{
	if(cur==num)
	{
		if(sum<minx)
		{
			minx = sum;
			for(int i = 0;i<num;i++)
			{
				res[i] = temp_res[i];
			}
		}
		return 1;
	}
	for(int i = cur;i<num;i++)
	{
		swap_s(&temp_res[i],&temp_res[cur]);
		double dis = 0;
		if(cur>0)
		{
			dis = get_dis(temp_res[cur-1],temp_res[cur]);
		}
		sum+=dis;
		if(sum>minx)
		{
			sum-=dis;
			swap_s(&temp_res[i],&temp_res[cur]);
			continue;
		}
		perm(cur+1);
		sum-=dis;
		swap_s(&temp_res[i],&temp_res[cur]);
	}
	return 0;
}

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int ncase = 1;
	while(scanf("%d",&num))
	{
		if(num==0)
			break;
		memset(location,0,sizeof(location));
		memset(feet,0,sizeof(feet));
		memset(res,0,sizeof(res));
		memset(temp_res,0,sizeof(temp_res));
		sum = 0;
		minx = 1<<30;
		for(int i = 0;i<num;i++)
		{
			scanf("%d%d",&location[i][0],&location[i][1]);
			temp_res[i] = i;
		}
		perm(0);
		for(int i = 0;i<num-1;i++)
		{
			feet[i] = get_dis(res[i],res[i+1]);
		}
		printf("**********************************************************\n");
		printf("Network #%d\n",ncase++);
		for(int i = 0;i<num-1;i++)
		{
			printf("Cable requirement to connect (%d,%d) to (%d,%d) is %.2lf feet.\n",location[res[i]][0],location[res[i]][1],location[res[i+1]][0],location[res[i+1]][1],feet[i]+16);
		}
		printf("Number of feet of cable required is %.2lf.\n",minx+16*(num-1));
	}
	return 0;
}

