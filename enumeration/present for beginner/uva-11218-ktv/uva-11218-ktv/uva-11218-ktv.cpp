// uva-11218-ktv.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cmath>
using namespace std;
int num, _max;
bool vis[11];
struct group
{
    int a, b, c, d;
} g[85];
void dfs(int cur, int score)
{
    if(cur >= 3)
    {
        if(_max < score)
            _max = score;
        return ;
    }
    for(int i=0; i<num; i++)
        if(vis[g[i].a] && vis[g[i].b] && vis[g[i].c])//可以取三个人
        {
            vis[g[i].a] = vis[g[i].b] = vis[g[i].c] = false;
            dfs(cur + 1, score + g[i].d);
            vis[g[i].a] = vis[g[i].b] = vis[g[i].c] = true;
        }
}
int main()
{
    int cc = 1;
    memset(vis, true, sizeof(vis));
    while(scanf("%d", &num) && num)
    {
        _max = -1;
        for(int i=0; i<num; i++)
            scanf("%d%d%d%d", &g[i].a, &g[i].b, &g[i].c, &g[i].d);
        dfs(0, 0);
        printf("Case %d: %d\n", cc++, _max);
    }
    return 0;
}


