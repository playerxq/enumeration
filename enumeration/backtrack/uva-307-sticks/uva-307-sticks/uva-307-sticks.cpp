// uva-307-sticks.cpp : 定义控制台应用程序的入口点。
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
int tot_len;
int part_num;
int stick[65];
int vist[65];
int cmp(const void* a,const void* b)  
{  
    return *(int*)b-*(int*)a;  
} 
int initial_len;
 bool dfs(int now, int index, int cnt) {//每个棍子都从大道小填入子棍子
	 if(initial_len * cnt == tot_len) 
		 return true;
     for(int i = index; i < part_num; i++) {
         if(vist[i] || (i && !vist[i-1] && stick[i] == stick[i-1])) 
			 continue;
         if(now + stick[i] == initial_len) 
		 {
             vist[i] = true;
             if(dfs(0, 0, cnt + 1)) return true;//新填充棍子 重新考虑所有的子棍子
             vist[i] = false;
             return false;//剪枝
         } 
		 else if(now + stick[i] < initial_len) 
		 {
             vist[i] = true;
             if(dfs(now + stick[i], i + 1, cnt)) return true;//从i+1开始考虑 之前1:i的子棍子由于排序故不必考虑
             vist[i] = false;
             if(now == 0) return false;//剪枝
         }
     }
     return false;
}

int main(void)  
{  
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
    while(scanf("%d",&part_num))  //n组数据
    {  
		if(part_num==0)
			break;
       memset(stick,0,sizeof(stick));
	   memset(vist,0,sizeof(vist));
        tot_len = 0;
  
        for(int i=0;i<part_num;i++)  
        {  
            scanf("%d",&stick[i]);
            tot_len+=stick[i];  //总长度
        }  
  
        qsort(stick,part_num,sizeof(int),cmp);  //降序
        int maxlen=stick[0];   //最大的棒为InitLen的搜索起点  
  
        bool flag=false;   
        for(initial_len=maxlen;initial_len<tot_len/2+1;initial_len++)  //InitLen:原始棒长  
        {   //剪枝2,InitLen必是sumlen的约数  
			memset(vist,0,sizeof(vist));
            if(!(tot_len%initial_len) && dfs(0,0,0))  //对每个新测试的initLen 开始dfs
            {  
                cout<<initial_len<<endl;  //找到一个即结束
                flag=true;  
                break;  
            }  
        }  
        if(!flag)  
            cout<<tot_len<<endl;  
  
    }  
    return 0;  
}

