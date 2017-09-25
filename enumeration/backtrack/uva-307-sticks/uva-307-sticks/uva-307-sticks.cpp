// uva-307-sticks.cpp : �������̨Ӧ�ó������ڵ㡣
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
 bool dfs(int now, int index, int cnt) {//ÿ�����Ӷ��Ӵ��С�����ӹ���
	 if(initial_len * cnt == tot_len) 
		 return true;
     for(int i = index; i < part_num; i++) {
         if(vist[i] || (i && !vist[i-1] && stick[i] == stick[i-1])) 
			 continue;
         if(now + stick[i] == initial_len) 
		 {
             vist[i] = true;
             if(dfs(0, 0, cnt + 1)) return true;//�������� ���¿������е��ӹ���
             vist[i] = false;
             return false;//��֦
         } 
		 else if(now + stick[i] < initial_len) 
		 {
             vist[i] = true;
             if(dfs(now + stick[i], i + 1, cnt)) return true;//��i+1��ʼ���� ֮ǰ1:i���ӹ�����������ʲ��ؿ���
             vist[i] = false;
             if(now == 0) return false;//��֦
         }
     }
     return false;
}

int main(void)  
{  
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
    while(scanf("%d",&part_num))  //n������
    {  
		if(part_num==0)
			break;
       memset(stick,0,sizeof(stick));
	   memset(vist,0,sizeof(vist));
        tot_len = 0;
  
        for(int i=0;i<part_num;i++)  
        {  
            scanf("%d",&stick[i]);
            tot_len+=stick[i];  //�ܳ���
        }  
  
        qsort(stick,part_num,sizeof(int),cmp);  //����
        int maxlen=stick[0];   //���İ�ΪInitLen���������  
  
        bool flag=false;   
        for(initial_len=maxlen;initial_len<tot_len/2+1;initial_len++)  //InitLen:ԭʼ����  
        {   //��֦2,InitLen����sumlen��Լ��  
			memset(vist,0,sizeof(vist));
            if(!(tot_len%initial_len) && dfs(0,0,0))  //��ÿ���²��Ե�initLen ��ʼdfs
            {  
                cout<<initial_len<<endl;  //�ҵ�һ��������
                flag=true;  
                break;  
            }  
        }  
        if(!flag)  
            cout<<tot_len<<endl;  
  
    }  
    return 0;  
}

