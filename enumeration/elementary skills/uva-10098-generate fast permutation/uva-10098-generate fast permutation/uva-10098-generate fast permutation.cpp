// uva-10098-generate fast permutation.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <cstdio>
#include <iostream>
#include <string.h>
#include <math.h>
#include<iomanip>
#include <ctype.h>
#include <algorithm>
using namespace std;
char s[15];
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int n;
	int case_n = 0;
	scanf("%d",&n);
	getchar();
	int nm = n;
	while(n--)
	{
		case_n++;
		scanf("%s",s);
		int len = strlen(s);
		sort(s,s+len);
		do
		{
			printf("%s\n",s);
		}while(next_permutation(s,s+len));
		printf("\n");
	}
	return 0;
}

