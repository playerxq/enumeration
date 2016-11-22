// uva-188-perfect hash.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cmath>

using namespace std;

int main()
{
#ifdef test
    freopen("sample.txt", "r", stdin);
#endif
    char str[1000];
    int sum, tot, len, tot_l;
    int a[20], num;
    while(gets(str) != NULL)
    {
        int _min = 0x7FFFFFFF;
        num = len = sum = tot = 0;
        tot_l = strlen(str);
        for(int i=0; i<=tot_l; i++)
        {
            if(str[i] == ' ' && str[i-1] == ' ') // 将多余的空格滤去
                continue;
            if(str[i] == ' ' || i == tot_l)
            {
                for(--len; len>-1; len--)
                    sum += (str[i-len-1]-'a'+1)*(int)pow(32.0, (double)len);
                a[num++] = sum;
                if(_min > a[num-1]) // C 从最小的Wi开始找
                    _min = a[num-1];
                len = sum = 0;
                continue;
            }
            ++len;
        }
        int C = _min;
        while(1)
        {
            int flag = 0;
            for(int i=0; i < num-1; i++)
                for(int j=i+1; j<num; j++)
                {
                    int t1 = C/a[i];
                    int t2 = C/a[j];
                    if(t1%num == t2%num)
                    {
                        C = min((t1+1)*a[i], (t2+1)*a[j]);
                        flag = 1;
                    }
                }
            if(!flag)
                break;
        }
        printf("%s\n",str);
        printf("%d\n\n", C);
    }
    return 0;
}


