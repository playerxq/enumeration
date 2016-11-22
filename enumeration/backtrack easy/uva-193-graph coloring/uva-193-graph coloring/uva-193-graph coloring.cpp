// uva-193-graph coloring.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <cstdlib>

using namespace std ;

const int maxn = 100 + 10 ;

int g[maxn][maxn] , color[maxn] , tcolor[maxn] , vis[maxn] ;

int m , n , k , ans ;

void init()
{
    memset( vis , 0 , sizeof( vis ) ) ;
    memset( color , 0 , sizeof( color ) ) ;
    memset( tcolor , 0 , sizeof( tcolor ) ) ;
    memset( g , 0 , sizeof( g ) ) ;
    ans = 0 ;
    return ;
}

void input()
{
    cin >> n >> k ;
    for( int i = 0 ; i < k ; ++i )
    {
        int u , v ;
        cin >> u >> v ;
        g[u][v] = g[v][u] = 1 ;
    }
    return ;
}

void dfs( int cur  )
{
    if( cur > n )
    {
        int tans = 0 ;
        for( int i = 1 ; i <= n ; ++i )
			if( tcolor[i] )
				tans++ ;
        if( tans > ans )
        {
            ans = tans ;
            memcpy( color , tcolor , sizeof( tcolor ) ) ;
        }
    }
    else
    {
        if( cur == 0 )//start  paint from 1:black or white
        {
           //vis[1] = 1 ;
           tcolor[1] = 1 ;
           dfs( cur+1 ) ;
           tcolor[1] = 0 ;
           //vis[1] = 0 ;
           dfs( cur+1 ) ;
        }
        else
        {
            int flag = 0 ;
            for( int v = 1 ; v <= n ; ++v )
				if( g[cur][v] && tcolor[v] )
				{
					flag = 1 ; break ;
				}
			if( flag )
			{
				dfs( cur+1 ) ;
			}
            else
            {
                //vis[cur] = 1 ;
                tcolor[cur] = 1 ;
                dfs( cur+1 ) ;
                //vis[cur] = 0 ;
                tcolor[cur] = 0 ;
                dfs( cur+1 ) ;
            }
        }
    }
    return ;
}

void solve()
{
    dfs( 0 ) ;
    return ;
}

void output()
{
    cout << ans << endl ;
    int cnt = 0 ;
    for( int i = 1 ; i <= n ; ++i )
    if( color[i] )
    {
        if( ++cnt < ans )
        cout << i << " " ;
        else
        cout << i ;
    }
    cout << endl ;
    return ;
}

int main()
{
    cin >> m ;
    while( m-- )
    {
        init() ;
        input() ;
        solve() ;
        output() ;
    }
    return 0 ;
}
