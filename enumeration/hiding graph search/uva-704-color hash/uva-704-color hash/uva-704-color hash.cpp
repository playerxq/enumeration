// uva-704-color hash.cpp : 定义控制台应用程序的入口点。
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
const int maxn = 1000000;
typedef int State[24];
int start[24];
int now[24];
int final[24] = {0,3, 4, 3, 0, 5, 6, 5, 0, 1, 2, 1, 0, 7, 8, 7, 0, 9, 10, 9, 0, 1, 2, 1};
int step[maxn], father[maxn], path[maxn];
int que[maxn][24];
map<string, int>vis; 
map<string, int>back_vis; //反向bfs
int back_father[maxn], back_path[maxn]; 
// 旋转函数 
void rotate(int *next, int *origin, int dir){ 
    if(dir==1){ // 左盘顺时针转 
        next[0] = origin[10], next[1] = origin[11]; 
        memcpy(next+2, origin, sizeof(int)*10);  // 大块的，连续数组元素的用memcpy节约时间 
        memcpy(next+12, origin+12, sizeof(int)*9); 
        next[21]=origin[7], next[22] = origin[8], next[23] = origin[9]; 
    } 
    else if(dir==2){ // 右盘顺时针转 
        memcpy(next+12, origin+14, sizeof(int)*10); 
        next[22] = origin[12], next[23] = origin[13]; 
        memcpy(next, origin, sizeof(int)*9); 
        next[9] = next[21], next[10] = next[22], next[11] = next[23];    
    } 
    else if(dir==3){ // 左盘逆时针转 
        memcpy(next, origin+2, sizeof(int)*10); 
        next[10] = origin[0], next[11] = origin[1]; 
        memcpy(next+12, origin+12, sizeof(int)*9); 
        next[21]=next[9], next[22]=next[10], next[23]=next[11]; 
    } 
    else if(dir==4){ // 右盘逆时针转 
        next[12] = origin[22],  next[13] = origin[23]; 
        memcpy(next+14, origin+12, sizeof(int)*10); 
        memcpy(next, origin, sizeof(int)*9); 
        next[9] = next[21], next[10] = next[22], next[11] = next[23];     
    } 
} 
// 把状态转换成字符串 
inline string change_state(State &s){  
    string str; 
    for(int i=0; i<24; ++i) 
        str += s[i]+'0'; 
    return str; 
}
inline int try_to_insert(int s){ 
    string str = change_state(que[s]); 
    if(!vis[str]){ 
        vis[str]=1;  
        return true; 
    } 
    return false; 
} 
inline int back_try_to_insert(int s){ 
   string str = change_state(que[s]); 
    if(!back_vis[str]){ 
        back_vis[str]=s; //保存队列中的位置，而不是1或者true,方便后面输出路径 
        return true; 
    } 
    return false;     
} 
int same(int* a)
{
	for(int i = 0;i<24;i++)
		if(a[i]!=final[i])
			return 0;
	return 1;
}
bool back_bfs(){ //逆向搜索 
    memset(back_father, 0, sizeof(back_father)); 
    step[0] = step[1] = 0; 
    back_vis.clear(); 
    back_vis[change_state(final)] = 1; 
    int front=0, rear=1; 
    memcpy(que[0], final, sizeof(final)); 
 
    while(front < rear){ 
        State &s = que[front]; 
        if(step[front] > 8){ // 超过8步不再搜索 
            ++front; continue; 
        } 
        for(int i=1; i<=4; ++i){ 
            State &next = que[rear]; 
            rotate(next, s, i); 
            step[rear] = step[front]+1; 
            if(back_try_to_insert(rear)){ 
                back_father[rear] = front;  
                switch(i){ // 因为是逆向搜索，所以方向保存的也要是相反的 
                    case 1:back_path[rear] = 3;break; 
                    case 2:back_path[rear] = 4;break; 
                    case 3:back_path[rear] = 1;break; 
                    case 4:back_path[rear] = 2;break; 
                } 
                rear++; 
            } 
        } 
        ++front; 
    } 
    return false; 
}
void output_positive(int now)
{
	if(now)
	{
		output_positive(father[now]);
		printf("%d",path[now]);
	}
}
void out_put_neposi(int back_start)
{
	if(back_start)
	{
		printf("%d",back_path[back_start]);
		out_put_neposi(back_father[back_start]);
	}
}
bool bfs()//正向bfs
{
	memset(father,0,sizeof(father));
	step[0] = 0;
	vis.clear();
	vis[change_state(start)] = 1; 
	int front = 0;
	int rear = 1;
	 memcpy(que[0], start, sizeof(start));
	 while(front<rear)
	 {
		 State& now = que[front];
		 if(step[front]>8)
		 {
			 ++front;
			 continue;
		 }
		 if(back_vis[change_state(now)])
		 {
			int back_start = back_vis[change_state(now)];
			output_positive(front);
			out_put_neposi(back_start);
			printf("\n");
			return true;
		 }
		 for(int i = 1;i<5;i++)
		 {
			State &next = que[rear]; 
            rotate(next, now, i); 
            step[rear] = step[front]+1; 
			if(try_to_insert(rear)){ 
                father[rear] = front;  
                switch(i){ //  
                    case 1:path[rear] = 1;break; 
                    case 2:path[rear] = 2;break; 
                    case 3:path[rear] = 3;break; 
                    case 4:path[rear] = 4;break; 
                } 
                rear++; 
            } 
		 }
		 front++;
	 }
	 return false;
}
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int t;
	scanf("%d",&t);
	while(t--)
	{
		for(int i = 0;i<24;i++)
			scanf("%d",&start[i]);
		if(same(start))
			printf("PUZZLE ALREADY SOLVED\n");
		else
		{
			back_bfs();
			int res = bfs();
			if(!res)
				printf("NO SOLUTION WAS FOUND IN 16 STEPS\n");
		}
	}
	return 0;
}

