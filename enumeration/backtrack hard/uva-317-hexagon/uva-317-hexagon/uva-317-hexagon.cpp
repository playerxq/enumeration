//1 长度5的边不能与两边任何一个相同
//由上可以推得5两边不能有超过或等于3个边有相同值 即3个不同值全出现 没有3个一样的边 即2个2个一组 5长度的单成一组
//若5两边的4 4相同  则另两个方向不可能再有4 4相同  只能5两边各3 4相同
#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define N 5
int n, Max, num[N][N];
const int yes[3] = {5, 6, 8};
const int no[3] = {5, 7, 7}; 

int main(){
    scanf("%d", &n);
    for (int t = 1; t <= n; t++){
	// Init.
	memset(num, 0, sizeof(num));
	Max = 0;

	// Read.
	for (int i = 1; i <= 3; i++){
	    for (int j = 0; j < 3; j++)
			scanf("%d", &num[i][j]);
	    sort(num[i], num[i] + 3);
	}
	
	// Handle.
	for (int k = 0; k <= 3; k++)//k = 0 三格方向均为3 4相同  否则 某个方向有4 4相同
	{
	    int sum = 0;
	    for (int i = 1; i <= 3; i++)
		{
			if (i == k)
			{
				for (int j = 0; j < 3; j++)
					sum += num[i][j] * yes[j];
			}
			else
			{
				for (int j = 0; j < 3; j++)
					sum += num[i][j] * no[j];
			}
	    }
	    if (sum > Max)
		Max = sum;
	}

		printf("Test #%d\n%d\n\n", t, Max);
    }
    return 0;
}