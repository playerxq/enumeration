// uva-10887-concatenation language.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cmath>

using namespace std;
const int MAXSIZE = 2250002;
int num, head[MAXSIZE], next[MAXSIZE];
char a[1502][11], b[1502][11], c[MAXSIZE][22];
int Hash(char *str)
{
    int seed = 131, sum = 0;
    while(*str)
        sum = sum * seed + (*str++);
    return (sum & 0x7FFFFFFF) % MAXSIZE;
}
void Hash_Insert(int s)
{
    int h = Hash(c[s]);
    int u = head[h];
    while(u)
    {
        if(!strcmp(c[s], c[u]))
        {
            return ;
        }
        u = next[u];
    }
    next[s] = head[h];
    head[h] = s;
    ++num;
}
int main()
{
    int t, n, m, cct = 0;
    scanf("%d", &t);
    while(t--)
    {
        num = 1;
        memset(head, 0, sizeof(head));
        scanf("%d%d", &n, &m);
        getchar();
        for(int i=0; i<n; i++)
            gets(a[i]);
        for(int i=0; i<m; i++)
            gets(b[i]);
        for(int i=0; i<n; i++)
            for(int j=0; j<m; j++)
            {
                sprintf(c[num],"%s%s", a[i], b[j]);//a b合并最多2250000种
                Hash_Insert(num);
            }
        printf("Case %d: %d\n", ++cct, num-1);
    }
    return 0;
}

