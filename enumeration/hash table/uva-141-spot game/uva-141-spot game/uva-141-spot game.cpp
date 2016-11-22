// uva-141-spot game.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cmath>

using namespace std;
const int MAXSIZE = 2505;
int n, num, cct;
char a[52][52], b[52][52], c[405][MAXSIZE];
void Hash() // 将二维数组转化为一维数组存起来
{
    int cct = -1;
    for(int i=1; i<=n; i++)
        for(int j=1; j<=n; j++)
            c[num][++cct] = b[i][j];
    ++num;
}
int Search()
{
    for(int k=0; k<cct; k++)//对以保存的每个图
    {
        int nn = 0, ff=1;
        for(int i=1; ff&&i<=n; i++)
            for(int j=1; ff&&j<=n; j++)
                if(c[k][nn++] != b[i][j])
                {
                    ff = 0;
                    break;
                }
        if(ff)//与某个已存图相同
            return 1;
    }
    return 0;
}
int main()
{
    int i, N, x[102], y[102];
    char str[102];
    while(scanf("%d", &n), n)
    {
        int flag = 1;
        cct = num = 0;
        memset(a, '0', sizeof(a));
        for(i=1; i<=n; i++)
            a[i][n+1] = 0;
        N = 2*n;
        for(i=1; i<=N; i++)
            scanf("%d %d %c", &x[i], &y[i], &str[i]);
        for(i=1; i<=N; i++)
        {
            if(str[i] == '+')
                a[x[i]][y[i]] = '1';
            else
                a[x[i]][y[i]] = '0';
            memcpy(b, a, sizeof(a));
            if(Search())//原图
                break;
            Hash();
            for(int j=1; j<=n; j++)
                for(int k=1; k<=n; k++)
                    b[k][n-j+1] = a[j][k];//顺时针90
            if(Search())
                break;
            Hash();
            for(int j=1; j<=n; j++)
                for(int k=1; k<=n; k++)
                    b[n-k+1][j] = a[j][k];//逆时针90
            if(Search())
                break;
            Hash();
            for(int j=1; j<=n; j++)
                for(int k=1; k<=n; k++)//翻转
                    b[j][n-k+1] = a[j][k];
            if(Search())
                break;
            Hash();
            cct = num;
        }
        if(i % 2)
            flag = 2;
        if(i<=N)
            printf("Player %d wins on move %d\n", flag, i);
        else
            puts("Draw");
    }
    return 0;
}

