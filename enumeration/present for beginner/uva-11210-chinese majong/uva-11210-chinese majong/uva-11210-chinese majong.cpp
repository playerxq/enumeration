// uva-11210-chinese majong.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <cstdio>
#include <iostream>
#include <string>
#include <string.h>
#include <math.h>
#include <vector>
#include <map>
#include<iomanip>
#include <ctype.h>
#include <algorithm>
using namespace std;
int n;  
int hand[14];  //手里的牌
int cnt[35], tmp_cnt[35];  //手里某种牌的牌数
char str[10];  
map<string, int>majiang;  
  
char buf[][6] = {  
    "1T","2T","3T","4T","5T","6T","7T","8T","9T", // 0~8  
    "1S","2S","3S","4S","5S","6S","7S","8S","9S", // 9~17  
    "1W","2W","3W","4W","5W","6W","7W","8W","9W", // 18~26   
    "DONG","NAN","XI","BEI",                      // 27~30  
    "ZHONG","FA","BAI"                            // 31~33  
};
inline void read(){  
    memset(cnt, 0, sizeof(cnt));  
    hand[0] = majiang[str];  
    ++cnt[hand[0]];  
  
    for(int i=1; i<13; ++i){  
        scanf("%s", str);  
        hand[i] = majiang[str];  
        ++cnt[hand[i]];  
    }     
}
// 判断能否组成顺子,i是顺子中最小的那张  
inline bool isChow(int i){  
    return (i<=6 || i>=9&&i<=15 || i>=18&&i<=24) &&   
            cnt[i]>=1 && cnt[i+1]>=1 && cnt[i+2]>=1;  
}
int check(int cur)
{
	if(cur>=14)
		return 1;
	if(cur==0)
	{
		for(int i = 0;i<13;i++)
		{
			for(int j = i+1;j<14;j++)
			{
				if(hand[i]==hand[j])//第一个对子
				{
					cnt[hand[i]]--;
					cnt[hand[j]]--;
					if(check(cur+2))
						return 1;
					cnt[hand[i]]++;
					cnt[hand[j]]++;
				}
			}
		}
	}
	else
	{
		for(int i = 0;i<34;i++)
		{
			if(cnt[i]>0)
			{
				if(cnt[i]<3&&!isChow(i))
					return 0;
				if(cnt[i]>=3)
				{
					cnt[i]-=3;
					if(check(cur+3))
						return 1;
					cnt[i]+=3;
				}
				if(isChow(i))
				{
					--cnt[i]; --cnt[i+1]; --cnt[i+2];  
					if(check(cur+3)) return 1;  
					++cnt[i]; ++cnt[i+1]; ++cnt[i+2]; 
				}
			}
		}
	}
	return 0;
}
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int cas=1;  
  
    // init  
    majiang.clear();  
    for(int i=0; i<34; ++i)  
        majiang[buf[i]] = i;  
  
    while(~scanf("%s", str) && str[0]!='0'){  
         
        read();  
        printf("Case %d:", cas++);  
  
        memcpy(tmp_cnt, cnt, sizeof(cnt));  
        bool ok=false;  
  
        for(int i=0; i<34; ++i)if(cnt[i]!=4){  
            hand[13] = i;  
            ++cnt[i];  
            if(check(0))   
                printf(" %s", buf[i]), ok=true;   
            memcpy(cnt,tmp_cnt,sizeof(tmp_cnt));  
  
        }  
        if(!ok) puts(" Not ready");  
        else puts("");  
  
    } 
	return 0;
}

