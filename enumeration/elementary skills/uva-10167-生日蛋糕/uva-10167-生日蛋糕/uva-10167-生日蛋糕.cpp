#include "stdafx.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
using namespace std;

struct POINT 
{
	int x,y;
}point[110];


void solve(int num)
{
	int u,d,l;
	for (int A = -100; A <= 100; ++ A)
	{
		for (int B = -100; B <= 100; ++ B)
		{
			u = d = 0;
			for (int i = 0; i < num; ++ i)
			{
				l = point[i].x * A + point[i].y * B;//Ax+By = 0  ¿ÉÁîx = B y = -A ¼ÆËã²æ»ý
				if (l > 0)
				{
					u ++;
				}
				else if (l < 0)
				{
					d ++;
				}
				else
					break;
				if (u == num / 2 && d == num / 2)
				{
					printf("%d %d\n", A, B);
					return;
				}

			}
		}
	}

}

int main()
{
	int N;
	while (scanf("%d", &N) == 1 && N)
	{
		int x,y, num = 0;
		for (int i = 0; i < 2 * N; i ++)
		{
			scanf("%d %d", &x, &y);
			if (x >= -100 && x <= 100 && y >= -100 && y <= 100)
			{
				point[num].x = x;
				point[num ++].y = y;
			}
		}
		solve(num);
	}
	return 0;
}