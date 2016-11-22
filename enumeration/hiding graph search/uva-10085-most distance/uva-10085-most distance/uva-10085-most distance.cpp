// uva-10085-most distance.cpp : 定义控制台应用程序的入口点。
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
typedef int state[9];
const int maxn = 1000000;
const int maxstep = 1000;
const int maxhash = 1000003;
int head[maxhash],next[maxn];
state st[maxn];
int dist[maxn];
int a[3][3];
const int dx[] = {-1,1,0,0};
const int dy[] = {0,0,-1,1};
int maxcnt;
int res[9];
int start[9];
char step[maxn];
char save[100];
int back[maxn];//当前状态的上一个状态
int maxindex;
void initial_table()
{
	memset(head,0,sizeof(head));
	memset(step,0,sizeof(step));
	memset(back,0,sizeof(back));
}
int hash(state& s)
{
	int v = 0;
	for(int i = 0;i<9;i++)
		v = v*10+s[i];
	return v%maxhash;
}
int try_insert(int s)
{
	int h = hash(st[s]);//得到哈希值
	int u = head[h];//第一个st的索引
	while(u)
	{
		if(memcmp(st[u],st[s],sizeof(st[s]))==0) return 0;
		u = next[u];
	}
	next[s] = head[h];
	head[h] = s;
	return 1;
}
int bfs()
{
	initial_table();
	int front = 1;
	int rear = 2;
	memcpy(st[front],start,sizeof(start));
	while(front<rear)
	{
		state& s = st[front];
		int z;
		for(z = 0;z<9;z++)
		{
			if(!s[z])
				break;
		}
		int x = z/3;
		int y = z%3;
		int flag = 0;
		for(int i = 0;i<4;i++)
		{
			int nx = x+dx[i];
			int ny = y+dy[i];
			int nz = 3*nx+ny;
			if(nx>=0&&nx<3&&ny>=0&&ny<3)
			{
				state& t = st[rear];
				memcpy(&t,&s,sizeof(s));
				t[nz] = s[z];
				t[z] = s[nz];
				dist[rear] = dist[front]+1;
				if(try_insert(rear))
				{
					back[rear] = front;
					if(i==0)
					{
						step[rear] = 'U';
					}
					else if(i==1)
					{
						step[rear] = 'D';
					}
					else if(i==2)
					{
						step[rear] = 'L';
					}
					else
					{
						step[rear] = 'R';
					}
					rear++;
				}
			}
		}
		front++;
	}
	return rear-1;
}

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int t;
	int ncase = 1;
	scanf("%d",&t);
	while(t--)
	{
		int sum = 0;
		for(int i = 0;i<9;i++)
			scanf("%d",&start[i]);
		maxcnt = 0;
		int goal = bfs();
		printf("Puzzle #%d\n",ncase++);
		for(int i = 0;i<9;i++)
		{
			printf("%d",st[goal][i]);
			if(i%3==2)
				printf("\n");
			else
				printf(" ");
		}
		while(goal)  
        {  
            save[++sum] = step[goal];  //倒序路径
            goal = back[goal];  
        }  
        for (int i=sum-1; i; i--)  
            printf("%c", save[i]);
		printf("\n\n");
	}
	return 0;
}

