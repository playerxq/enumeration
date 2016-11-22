// uva-301-transportation.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAXN 24
typedef struct ticket{
    int from, to;
    int price, people;
}ticket;

ticket route[MAXN];
int visit[MAXN];
int road[10];
int max;

int judge(int cur, int n, int sum, int flag)
{
    int i, temp;
    for(temp=0,i=cur+flag; i<=n; ++i)//将后续所有订单相加
        temp += route[i].price*route[i].people;
    if(max > sum+temp) return 0;
    else return 1;
}

int Traverse(int cur, int room, int n, int sum)//cur张订单
{
    int temp, i, j, store1, store2, flag;
    if(cur > n)
    {
        max = max > sum ? max : sum;
        return sum;    
    }
    flag = 1;
    for(i=route[cur].from; i<route[cur].to; ++i)//road[i]为第i个站的人数 加上第cur订单的人数看是否超值
    {
        if(road[i]+route[cur].people > room) 
        {
            flag = 0;
            break;
        }
    }
    if(flag)
    {
        if(judge(cur, n, sum, 0))//订单取得
        {
            visit[cur] = -1;
            for(i=route[cur].from; i<route[cur].to; ++i) road[i] += route[cur].people;
            Traverse(cur+1,room, n, sum+route[cur].price*route[cur].people);
            for(i=route[cur].from; i<route[cur].to; ++i) road[i] -= route[cur].people;
            visit[cur] = 0;
        }
    }
    if(judge(cur, n, sum, 1))//订单作废
    Traverse(cur+1, room, n, sum);
    return 0;
}

int main()
{

    int num, city, order, i, cnt;
    while(scanf("%d%d%d", &num, &city, &order) != EOF)
    {
        if(!num && !city && !order) break;
        memset(visit, 0, sizeof(visit));
        memset(road, 0, sizeof(road));
        for(i=1; i<=order; ++i)
        {
            scanf("%d%d%d", &route[i].from, &route[i].to, &route[i].people);
            route[i].price = route[i].to - route[i].from;
        }
        max = -1;
        cnt = 0;
        Traverse(1, num, order, cnt);//从第一张订单开始考虑
        printf("%d\n", max);
    }
    return 0;
}

