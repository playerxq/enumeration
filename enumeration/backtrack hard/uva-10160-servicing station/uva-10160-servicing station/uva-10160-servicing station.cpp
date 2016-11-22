/*
1：用邻接表代替邻接矩阵来存放关系。可以减少一点搜索次数。
2：每次找到一个放置方案，保存下个数，如果之后搜索过程中个数超过这个个数。就可以直接结束这次搜索。
3：如果一个点已经搜索过了。并且该点没被覆盖到， 并且之后的点没有连接到改点，那么该点永远不会被覆盖到，就可以直接结束这条的搜索。
有一点的要注意的是。标记覆盖不能用单纯的0,1来标记。因为一个点是可以重复覆盖的。我用的是vis[] ++, vis[]--的方法来标记的
*/
#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

int n, m;
int x, y;
int snum[40];//度数
int map[40][40];
int f[40];
int minn;

bool cmp(int a, int b)
{
    return a > b;
}

void dfs(int star, int num, int tnum)//star当前考虑的城市 //num 已经覆盖过的点 //tnum 设置服务点数目
{
    if (tnum >= minn)
		return;
    if (num == n)
    {
		minn = tnum;
		return;
    }
    if (star > n)
		return;
    for (int i = 1; i < star; i ++)//对已经考虑过的城市 若其未被覆盖且最大的邻接城市已经被考虑 即star后没有其他城市与i邻接 则其之后不可能再被覆盖 返回分支
		if (!f[i] && map[i][0] < star)
			return;
    int jia = 0;
	//按是否在star处设置服务点分支
    for (int i = 0; i < snum[star]; i ++)//遍历star的邻接城市
    {
		if (f[map[star][i]] == 0)//找到未覆盖过的邻接点
			jia ++;
		f[map[star][i]] ++;//加一层覆盖
    }
    if (jia)//有新找到的覆盖点
		dfs(star + 1, num + jia, tnum + 1);
    for (int i = 0; i < snum[star]; i ++)
    {
		f[map[star][i]] --;
    }
    dfs(star + 1, num, tnum);
}
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
    while (scanf("%d%d", &n, &m) != EOF && n + m)
    {
		minn = n;
		memset(snum, 0, sizeof(snum));
		memset(map, 0, sizeof(map));
		memset(f, 0, sizeof(f));
		for (int i = 0; i < m; i ++)
		{
			scanf("%d%d", &x, &y);
			map[x][snum[x] ++] = y;
			map[y][snum[y] ++] = x;
		}
		for (int i = 1; i <= n; i++) 
		{
			map[i][snum[i] ++] = i;//增加自己到自己的覆盖
			sort(map[i], map[i] + snum[i], cmp);//邻接到的城市降序排序
		}
		dfs(1, 0, 0);
		printf("%d\n", minn);
    }
    return 0;
}