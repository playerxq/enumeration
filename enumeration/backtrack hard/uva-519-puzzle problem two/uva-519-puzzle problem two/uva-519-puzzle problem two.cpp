// uva-519-puzzle problem two.cpp : 定义控制台应用程序的入口点。
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
int n,m;
int a[7][7];
char s[5];
int str[4];
int str_l[4];
int str_up[4];
int num_f;
int num_i;
int num_o;
int piece[81];//保存81种piece的每种的数目  索引从0000-2222为3进制数
int three_2_digit()
{
	int sum = 0;
	for(int i = 0;i<4;i++)
	{
		sum = sum*3+str[i];
	}
	return sum;
}
void digit_2_three(int sum, int* str)
{
	int i = 3;
	while(sum/3)
	{
		str[i--] = sum%3;
		sum/=3;
	}
	str[i--] = sum;
	for(i;i>=0;i--)
		str[i] = 0;
}
void get_next(int x, int y, int*nx, int* ny)
{
	if(y==m-1)
	{
		*nx = x+1;
		*ny = 0;
	}
	else
	{
		*nx = x;
		*ny = y+1;
	}
}
int dfs(int x, int y)
{
	if(x==n)
		return 1;
	if(x==0&&y==0)
	{
		//选择放入第一个piece
		for(int i = 0;i<81;i++)
		{
			if(piece[i])
			{
				digit_2_three(i,str);
				if(str[0]==0&&str[3]==0)
				{
					piece[i]--;
					a[0][0] = i;
					int nx,ny;
					get_next(x,y,&nx,&ny);
					if(dfs(nx,ny))
						return 1;
					piece[i]++;
				}
			}
		}
	}
	else if(x==0&&y==m-1)
	{
		//右上角 根据a[0][m-2]选择
		for(int i = 0;i<81;i++)
		{
			if(piece[i])
			{
				digit_2_three(i,str);
				if(str[0]==0&&str[1]==0)
				{
					digit_2_three(a[0][m-2],str_l);
					if((str_l[1]==1&&str[3]==2)||(str_l[1]==2&&str[3]==1))
					{
						piece[i]--;
						a[0][m-1] = i;
						int nx,ny;
						get_next(x,y,&nx,&ny);
						if(dfs(nx,ny))
							return 1;
						piece[i]++;
					}
				}
			}
		}
	}
	else if(x==n-1&&y == 0)
	{
		//左下角 根据a[n-2][0]
		for(int i = 0;i<81;i++)
		{
			if(piece[i])
			{
				digit_2_three(i,str);
				if(str[2]==0&&str[3]==0)
				{
					digit_2_three(a[n-2][0],str_up);
					if((str_up[2]==1&&str[0]==2)||(str_up[2]==2&&str[0]==1))
					{
						piece[i]--;
						a[n-1][0] = i;
						int nx,ny;
						get_next(x,y,&nx,&ny);
						if(dfs(nx,ny))
							return 1;
						piece[i]++;
					}
				}
			}
		}
	}
	else if(x==n-1&&y==m-1)
	{
		//右下角 a[n-1][m-2] a[n-2][m-1]
		for(int i = 0;i<81;i++)
		{
			if(piece[i])
			{
				digit_2_three(i,str);
				if(str[1]==0&&str[2]==0)
				{
					digit_2_three(a[n-2][m-1],str_up);
					digit_2_three(a[n-1][m-2],str_l);
					if(((str_up[2]==1&&str[0]==2)||(str_up[2]==2&&str[0]==1))&&((str_l[1]==1&&str[3]==2)||(str_l[1]==2&&str[3]==1)))
					{
						piece[i]--;
						a[n-1][m-1] = i;
						int nx,ny;
						get_next(x,y,&nx,&ny);
						if(dfs(nx,ny))
							return 1;
						piece[i]++;
					}
				}
			}
		}
	}
	else if(x==0)//上边
	{
		for(int i = 0;i<81;i++)
		{
			if(piece[i])
			{
				digit_2_three(i,str);
				if(str[0]==0&&str[1]!=0&&str[3]!=0)
				{
					digit_2_three(a[0][y-1],str_l);
					if((str_l[1]==1&&str[3]==2)||(str_l[1]==2&&str[3]==1))
					{
						piece[i]--;
						a[0][y] = i;
						int nx,ny;
						get_next(x,y,&nx,&ny);
						if(dfs(nx,ny))
							return 1;
						piece[i]++;
					}
				}
			}
		}
	}
	else if(x==n-1)//下边
	{
		for(int i = 0;i<81;i++)
		{
			if(piece[i])
			{
				digit_2_three(i,str);
				if(str[2]==0&&str[1]!=0&&str[3]!=0)
				{
					digit_2_three(a[n-2][y],str_up);
					digit_2_three(a[n-1][y-1],str_l);
					if(((str_up[2]==1&&str[0]==2)||(str_up[2]==2&&str[0]==1))&&((str_l[1]==1&&str[3]==2)||(str_l[1]==2&&str[3]==1)))
					{
						piece[i]--;
						a[n-1][y] = i;
						int nx,ny;
						get_next(x,y,&nx,&ny);
						if(dfs(nx,ny))
							return 1;
						piece[i]++;
					}
				}
			}
		}
	}
	else if(y==0)//左边
	{
		for(int i = 0;i<81;i++)
		{
			if(piece[i])
			{
				digit_2_three(i,str);
				if(str[3]==0&&str[0]!=0&&str[2]!=0)
				{
					digit_2_three(a[x-1][0],str_up);
					if((str_up[2]==1&&str[0]==2)||(str_up[2]==2&&str[0]==1))
					{
						piece[i]--;
						a[x][0] = i;
						int nx,ny;
						get_next(x,y,&nx,&ny);
						if(dfs(nx,ny))
							return 1;
						piece[i]++;
					}
				}
			}
		}
	}
	else if(y==m-1)//右边
	{
		for(int i = 0;i<81;i++)
		{
			if(piece[i])
			{
				digit_2_three(i,str);
				if(str[1]==0&&str[0]!=0&&str[2]!=0)
				{
					digit_2_three(a[x][m-2],str_l);
					digit_2_three(a[x-1][m-1],str_up);
					if(((str_up[2]==1&&str[0]==2)||(str_up[2]==2&&str[0]==1))&&((str_l[1]==1&&str[3]==2)||(str_l[1]==2&&str[3]==1)))
					{
						piece[i]--;
						a[x][m-1] = i;
						int nx,ny;
						get_next(x,y,&nx,&ny);
						if(dfs(nx,ny))
							return 1;
						piece[i]++;
					}
				}
			}
		}
	}
	else//根据 a[x-1][y]与a[x][y-1]决定
	{
		for(int i = 0;i<81;i++)
		{
			if(piece[i])
			{
				digit_2_three(i,str);
				digit_2_three(a[x-1][y],str_up);
				digit_2_three(a[x][y-1],str_l);
				if(((str_up[2]==1&&str[0]==2)||(str_up[2]==2&&str[0]==1))&&((str_l[1]==1&&str[3]==2)||(str_l[1]==2&&str[3]==1)))
				{
					piece[i]--;
					a[x][y] = i;
					int nx,ny;
					get_next(x,y,&nx,&ny);
					if(dfs(nx,ny))
						return 1;
					piece[i]++;
				}
			}
		}
	}
	return 0;
}
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	while(scanf("%d%d",&n,&m))
	{
		if(n==0&&m==0)
			break;
		num_f = 0;
		num_o = 0;
		num_i = 0;
		getchar();
		memset(a,0,sizeof(a));
		memset(piece,0,sizeof(piece));
		for(int i = 0;i<n*m;i++)
		{
			gets(s);
			for(int j = 0;j<4;j++)
			{
				switch(s[j])
				{
				case 'F':
					{
						str[j] = 0;
						num_f++;
					}
					break;
				case 'O':
					{
						str[j] = 1;
						num_o++;
					}
					break;
				case 'I':
					{
						str[j] = 2;
						num_i++;
					}
					break;
				}
			}
			int form_index = three_2_digit();
			piece[form_index]++;
		}
		if((num_f!=2*(n+m))||(num_o!=num_i))
		{
			printf("NO\n");
		}
		else
		{
			int res = dfs(0,0);
			if(res)
				printf("YES\n");
			else
				printf("NO\n");
		}
	}
	return 0;
}

