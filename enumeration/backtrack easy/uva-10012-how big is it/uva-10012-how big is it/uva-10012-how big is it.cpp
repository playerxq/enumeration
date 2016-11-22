// uva-10012-how big is it.cpp : 定义控制台应用程序的入口点。
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
double radius[10];
double p[10];//圆心位置
double minx;

void swap_s(int a, int b)
{
	double temp = radius[a];
	radius[a] = radius[b];
	radius[b] = temp;
}

double point(int k){ //第k个圆心坐标
    double R = 0; 
    for(int j = 0 ; j < k ; j++){ //可能与前面的所有园相切
        double tempr = p[j] + 2.0*sqrt(radius[k]*radius[j]);//两个圆的距离 d = sqrt((r1+r2)^2 - (r1-r2)^2) 那么有 d  =  2.0*sqrt(r[k]*r[j]);     
        if(R < tempr)//更新为最大 
            R = tempr; 
    } 
    return R; 
} 


void distance(){ 
    double high , low; 
    high = 0 ; low = 0; 
    for(int i = 0 ; i <num ; i++){ 
        if(p[i]-radius[i] < low)  low  = p[i] - radius[i];     //更新最左边的位置 
        if(p[i]+radius[i] > high) high = p[i] + radius[i]; //更新最右边的位置 
    } 
    if(high - low < minx) 
        minx = high - low;//更新最小距离 
}
void dfs(int cur)
{
	if(cur==num)
	{
		distance();
	}
	else
	{
		for(int i = cur;i<num;i++)
		{
			swap_s(cur,i);
			double R = point(cur);
			if(R+radius[0]+radius[cur]<minx)
			{
				p[cur] = R;
				dfs(cur+1);
			}
			swap_s(cur,i);
		}
	}
}

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int n = 0;
	scanf("%d",&n);
	while(n--)
	{
		scanf("%d",&num);
		memset(radius,0,sizeof(radius));
		memset(p,0,sizeof(p));
		for(int i = 0;i<num;i++)
		{
			scanf("%lf",&radius[i]);
		}
		minx = 1<<30;
		dfs(0);
		printf("%.3lf\n",minx);
	}
	return 0;
}

