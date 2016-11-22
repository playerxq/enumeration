// uva-10591-happy number.cpp : 定义控制台应用程序的入口点。
//最大的数是10^9, 那么各个位数上都最大的话就是9个9， 平方和为9*9*9 = 729,  所以只要开个730+的数组即可。

#include "stdafx.h"
#include<iostream> 
#include<cstdio> 
#include<cstring> 
using namespace std; 
int hash[810]; 
 
inline int getSum(int n){ 
    int sum=0; 
    while(n){ 
        int t = n%10; 
        sum += t*t; 
        n /= 10; 
    } 
    return sum; 
} 
 
int main(){ 
    int T, cas=1; 
    scanf("%d", &T); 
    while(T--){ 
        int N, M; 
        memset(hash, 0, sizeof(hash)); 
        scanf("%d", &N); 
        M = N; 
        bool flag=false; 
        int cnt=1; 
        while(M=getSum(M)){ 
            if(M==1) {flag=true; break;} 
            else if(hash[M] || M==N){break;} 
            hash[M] = 1; 
        } 
 
        printf("Case #%d: ", cas++); 
        if(flag) printf("%d is a Happy number.\n", N); 
        else printf("%d is an Unhappy number.\n", N); 
    } 
    return 0; 
} 

