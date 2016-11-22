// hdu-1381-hashx.cpp : 定义控制台应用程序的入口点。
//用nc进制的数表示字符串，枚举长度为n的子串计算值，重复的去掉

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
#define N 16000007  
int hashx[8000000],assi[27],n,nc;  
char str[N];  
int a[N],len; 
int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
	int t,i,j,sum,k;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d %d",&n,&nc);
		getchar();
		scanf("%s",str);
		len = strlen(str);
		k = 0;
		for(i = 0; i < len; i++)  //转化为整数
        {  
            a[i] = str[i] - 'a';  
        }
		i = 0;
		while(str[i]!='\0')  //对每个数字  转化为nc进制的数字
        {  
            if(assi[a[i]]==0)  
                assi[a[i]]=k++;  
            if(k==nc)  
                break;  
            i++;  
        } 
		int cnt=len-n+1;//n长度子串个数
		for(i=0;i<len-n+1;i++)  //每个子串
        {  
            sum=0;  
            for(j=i;j<i+n;j++)  //计算值
            {  
                sum=sum*nc+assi[a[j]];  
            }  
            sum%=N;  
            if(hashx[sum]==0)  
                hashx[sum]=1;  
            else  //遇到有重复的  去掉
                cnt--;  
        }  
        printf("%d\n",cnt);  
        if(t>0)  
            printf("\n");
	}
}

