#include "stdafx.h"
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cmath>

using namespace std ;

const int maxn = 6 ;

int ans , a[maxn] , n , icase = 0 ;

void init()
{
    ans = 0 ;
    memset( a, 0 , sizeof( a ) ) ;
    return ;
}

void input()
{
    for( int i = 0 ; i < n ; ++i )
    cin >> a[i] ;
    return ;
}

bool is_in_order()
{
    for( int i = 0 ; i < n-1 ; ++i )
    if( a[i] > a[i+1] )
    return false ;
    return true ;
}

void dfs()
{
    if( is_in_order() )
    {
        ans++ ;
    }
    else
    {
        for( int i = 0 ; i < n-1 ; ++i )
        if( a[i] > a[i+1] )
        {
            int t = a[i] ; a[i] = a[i+1] ; a[i+1] = t ;
            dfs() ;
            t = a[i] ; a[i] = a[i+1] ; a[i+1] = t ;
        }
    }
}

void solve()
{
    if( !is_in_order() )
    dfs() ;
    return ;
}



void output()
{
    cout << "There are " << ans << " swap maps for input data set " << ++icase << "." << endl ;
//    cout << ans << endl ;
    return ;
}

int main()
{
    while( cin >> n && n )
    {
        init() ;
        input() ;
        solve() ;
        output() ;
    }
    return 0 ;
}
