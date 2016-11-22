// uva-321-new villa.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cmath>
using namespace std;
int Switch[12][12], stnum[12];
bool vis[100003], door[12][12];
int r, d, s;
struct node
{
    int room, step, lstate, begin; // 所在的房间号、当前步数，当前所有灯的的状态，其前一步记录位置
} path[100003];
bool insert(int s)
{
    int h = path[s].lstate * 10 + path[s].room - 1;
    if(vis[h])
        return false;
    return vis[h]=true;
}
int change(int rnum)
{
    for(int i=0; i<15; i++)
        if((1<<i) == rnum)
            return i + 1;
    return 0;
}
void print(int s)
{
    int u = path[s].begin;
    if(s)
        print(u);
    if(path[u].room != path[s].room)
        printf("- Move to room %d.\n", path[s].room);
    else if(path[u].lstate < path[s].lstate)
        printf("- Switch on light in room %d.\n", change(path[s].lstate - path[u].lstate));
    else if(path[u].lstate > path[s].lstate)
        printf("- Switch off light in room %d.\n", change(path[u].lstate - path[s].lstate));
}
void bfs()
{
    memset(vis, false, sizeof(vis));
    int front = 0, rear = 1;
    path[0].begin = 0, path[0].step = 0;
    path[0].lstate = 1, path[0].room = 1;
    insert(0);
    while(front < rear)
    {
        int x = path[front].room, y;
        if(x==r&&path[front].lstate==(1<<(r-1)))//只有最后一个灯亮
        {
            printf("The problem can be solved in %d steps:\n", path[front].step);
            print(front);
            return ;
        }
        for(int i=1; i<=r; i++)
            if(door[x][i]&&(1<<(i-1))&path[front].lstate)//可以进入i号房间 灯亮
            {
                path[rear].begin = front;
                path[rear].room = i;
                path[rear].step = path[front].step + 1;
                path[rear].lstate = path[front].lstate;
                if(insert(rear))
                    rear++;
            }
        for(int i=0; i<stnum[x]; i++)//呆在x不动  开关其他房间灯
        {
            y = Switch[x][i];
            path[rear].begin = front;
            path[rear].room = x;
            if((1<<(y-1))&path[front].lstate)//当前灯状态中y号开灯
                path[rear].lstate = path[front].lstate - (1<<(y-1));
            else
                path[rear].lstate = path[front].lstate + (1<<(y-1));//y关灯 
            path[rear].step = path[front].step + 1;
            if(1<<(x-1)&path[rear].lstate && insert(rear))
                rear++;
        }
        front++;
    }
    puts("The problem cannot be solved.");
}
int main()
{
    int x, y, t = 1;
    while(scanf("%d%d%d", &r, &d, &s), r+d+s)
    {
        memset(stnum, 0, sizeof(stnum));
        memset(door, false, sizeof(door));
        for(int i=0; i<d; i++)
        {
            scanf("%d%d", &x, &y);
            door[x][y] = door[y][x] = true;
        }
        for(int i=0; i<s; i++)
        {
            scanf("%d%d", &x, &y);
            Switch[x][stnum[x]++]=y;
        }
        printf("Villa #%d\n", t++);
        bfs();
        puts("");
    }
    return 0;
}


