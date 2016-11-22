// uva-322-ships.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <cstdio>
#include <iostream>
#include <string.h>
#include <math.h>
#include <vector>
#include<iomanip>
#include <ctype.h>
#include <algorithm>
using namespace std;
int h,w;
char s[20][20];
int a[20][20];//0 未判断 1 已有 -1 没有 
int b[20][20];//0 未判断 1 已有 -1 没有 
int used[20][20];//7 pieces
int zero[256];
int num_one;//已经确定有船的方个数
int num_zero;//未确定的方格数
int num_piece;
int num_avail;//当前船的旋转状态下的可行解数目
int res_avail;//总共的可行解数目
int pos_in;
int pos[256];
int pre_pos[256];//只需最多保存1组解的未填入点  pos与pre_pos不同说明多个可行解
int i1,i2,i3,i4,i5,i6,i7;
typedef struct Po
{
	int x;
	int y;
} P;
P parr[7];
int piece[7][4][4][2] = 
{
	{
		{{0,0},{0,1},{1,1},{1,0}}
	},
	{
		{{0,0},{0,1},{0,2},{0,3}},
		{{0,0},{1,0},{2,0},{3,0}}
	},
	{
		{{0,0},{1,0},{0,1},{1,-1}},
		{{0,0},{1,0},{1,1},{2,1}}
	},
	{
		{{0,0},{0,1},{1,1},{1,2}},
		{{0,0},{1,0},{1,-1},{2,-1}}
	},
	{
		{{0,0},{1,0},{1,1},{1,2}},
		{{0,0},{1,0},{2,0},{2,-1}},
		{{0,0},{0,1},{0,2},{1,2}},
		{{0,0},{0,1},{1,0},{2,0}}
	},
	{
		{{0,0},{1,0},{1,-1},{1,-2}},
		{{0,0},{0,1},{1,1},{2,1}},
		{{0,0},{0,1},{0,2},{1,0}},
		{{0,0},{1,0},{2,0},{2,1}}
	},
	{
		{{0,0},{1,0},{1,-1},{1,1}},
		{{0,0},{1,0},{2,0},{1,-1}},
		{{0,0},{0,1},{0,2},{1,1}},
		{{0,0},{1,0},{2,0},{1,1}}
	}
};
int ok(int x, int y)
{
	if(x>=0&&x<h&&y>=0&&y<w)
		return 1;
	return 0;
}
int ok_piece(int x, int y,int angle, int id)
{
	//按id号piece的第angle的旋转图形  从0,0开始第一找到点为x,y看是否满足
	for(int i = 0;i<4;i++)
	{
		int nx = x+piece[id-1][angle][i][0];
		int ny = y+piece[id-1][angle][i][1];
		if(!ok(nx,ny))
			return 0;
		if(b[nx][ny]!=1)
			return 0;
	}
	return 1;
}
void change_piece(int x, int y, int angle, int id, int v)
{
	for(int i = 0;i<4;i++)
	{
		int nx = x+piece[id-1][angle][i][0];
		int ny = y+piece[id-1][angle][i][1];
		b[nx][ny] = v;
		if(v==-1)
		{
			if(used[nx][ny]==1)//原来是1
				num_one--;//消掉一个1
		}
		else
		{
			if(used[nx][ny]==1)//原来是1
				num_one++;//还原一个1
		}
	}
}
int same()//判断当前的未使用的那些0方格与之前的某个可行解对应的0方格是否一样
{
	if(pre_pos[0]!=pos[0])
		return 0;
	if(pos[0]==0)
		return 0;
	for(int i = 1;i<=pos[0];i++)
		if(pos[i]!=pre_pos[i])
			return 0;
	return 1;
}
int check()//1 当前解可以被忽略  0 当前解增加一个可行解
{
	//计算当前的可行解中b中为1的点 即没有使用过的点
	int k = 1;
	if(pos_in==0)
	{
		for(int i = 0;i<h;i++)
		{
			for(int j = 0;j<w;j++)
			{
				if(b[i][j]==1)
				{
					int in = i*w+j;
					pre_pos[k++] = in;
				}
			}
		}
		if(k>1)
		{
			sort(pre_pos+1,pre_pos+k-1);
		}
		pre_pos[0] = k-1;//长度
		pos_in++;
		num_avail++;
		return 1;
	}
	else
	{
		for(int i = 0;i<h;i++)
		{
			for(int j = 0;j<w;j++)
			{
				if(b[i][j]==1)
				{
					int in = i*w+j;
					pos[k++] = in;
				}
			}
		}
		if(k>1)
		{
			sort(pos,pos+k-1);
		}
		pos[0] = k-1;
		if(same())//有一样的  应该是一类解  放弃当前解
			return 1;
		num_avail++;
		return 0;
	}
}
int flag;
void dfs(int id)//当前每个形状已经固定
{
	if(id==8)
	{
		if(num_one==0)//原来的1全部消掉
		{
			if(check())
			{
				return;
			}
			else
			{
				if(num_avail>1)
				{
					flag = 0;//得到两类可行解  放弃
					return;
				}
			}
		}
	}
	else
	{
		int angle;
		switch(id)
		{
		case 1:
			angle = i1;
			break;
		case 2:
			angle = i2;
			break;
		case 3:
			angle = i3;
			break;
		case 4:
			angle = i4;
			break;
		case 5:
			angle = i5;
			break;
		case 6:
			angle = i6;
			break;
		case 7:
			angle = i7;
			break;
		}
		for(int i = 0;i<h&&flag;i++)
		{
			for(int j = 0;j<w&&flag;j++)
			{
				if(ok_piece(i,j,angle,id))
				{
					change_piece(i,j,angle,id,-1);
					parr[id-1].x = i;
					parr[id-1].y = j;
					dfs(id+1);
					change_piece(i,j,angle,id,1);
				}
			}
		}	
	}
	return;
}

//判断当前区域内1形成的图案是否是7个piece  是的话有几组可行方案
int getpiece()//
{
	int sum = 0;//可行解数目
	
	for(i1 = 0;i1<1;i1++)//方块  一种
	{
		if(h==1||w==1)
			continue;
		for(i2 = 0;i2<2;i2++)//竖线  二种
		{
			if(i2==0&&w<4)
				continue;
			if(i2==1&&h<4)
				continue;
			for(i3 = 0;i3<2;i3++)//右折
			{
				if(i3==0&&w<3)
				continue;
				if(i3==1&&h<3)
					continue;
				for(i4 = 0;i4<2;i4++)//左折
				{
					if(i4==0&&w<3)
						continue;
					if(i4==1&&h<3)
						continue;
					for(i5 = 0;i5<4;i5++)//右弯
					{
						if((i5==0||i5==2)&&w<3)
							continue;
						if((i5==1||i5==3)&&h<3)
							continue;
						for(i6 = 0;i6<4;i6++)//左弯
						{
							if((i6==0||i6==2)&&w<3)
								continue;
							if((i6==1||i6==3)&&h<3)
								continue;
							for(i7 = 0;i7<4;i7++)//三角
							{
								if((i7==0||i7==2)&&w<3)
									continue;
								if((i7==1||i7==3)&&h<3)
									continue;
								//确定每种形状当前旋转状态
								//看当前区域是否有此旋转状态的可行解
								num_avail = 0;//当前形状可行解数目
								flag = 1;
								dfs(1);
								sum+=num_avail;
								if(sum>1)
									return sum;//已经找到多个可行解  不用继续搜索
							}
						}
					}
				}
			}
		}
	}
	return sum;
}
//res_avail表示当前某个0被指派为miss -1的时候一共存在的可行解数目  若res_avail=1则可输出yes
void get_avail()
{
	memcpy(b,a,sizeof(a));
	pos_in = 0;
	memset(pos,0,sizeof(pos));
	memset(pre_pos,0,sizeof(pre_pos));
	for(int i = 0;i<h;i++)
	{
		for(int j = 0;j<w;j++)
		{
			if(b[i][j]==0)//选取0翻转为1看当前的状态下可行解数目
			{
				b[i][j] = 1;
			}
		}
	}
	res_avail=getpiece();//得到当前翻转状态的可行解数目
}
//将某个0置为miss -1  若存在某个miss使得res_avail = 1则为yes 若所有miss均使得res_avail不为1 则为no
int miss()
{
	for(int i = 0;i<h;i++)
	{
		for(int j = 0;j<w;j++)
		{
			if(a[i][j]==0)
			{
				a[i][j] = -1;//miss
				res_avail = 0;
				get_avail();
				if(res_avail==1)
					return 1;
				a[i][j] = 0;
			}
		}
	}
	return 0;
}
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int ncase = 1;
	while(scanf("%d%d",&w,&h))
	{
		if(w==0&&h==0)
			break;
		memset(s,0,sizeof(s));
		memset(a,0,sizeof(a));
		memset(used,0,sizeof(used));
		memset(zero,0,sizeof(zero));
		getchar();
		for(int i = 0;i<h;i++)
		{
			gets(s[i]);
		}
		//if(ncase>1)
			//printf("\n");
		printf("Game #%d\n",ncase++);
		num_one = 0;
		num_zero = 0;
		for(int i = 0;i<h;i++)
		{
			for(int j = 0;j<w;j++)
			{
				if(s[i][j]=='.')
				{
					a[i][j] = 0;//为0  说明未知
					zero[num_zero++] = i*w+j;
				}
				else if(s[i][j]=='o')
					a[i][j] = -1;//确定没船
				else
				{
					a[i][j] = 1;//确定有船
					used[i][j] = 1;
					num_one++;
				}
			}
		}
		if(num_one+num_zero<=28)
		{
			printf("yes.\n");
		}
		else if(num_one==28)//判断当前是否已经构成可行解
		{
			for(int i = 0;i<h;i++)
			   for(int j = 0;j<w;j++)
					if(a[i][j]==0)
						a[i][j] = -1;
			get_avail();
			if(getpiece())
			{
				printf("yes.\n");
			}
			else
			{
				printf("no.\n");
			}
		}
		else if(num_one+num_zero==28)
		{
			for(int i = 0;i<h;i++)
			   for(int j = 0;j<w;j++)
					if(a[i][j]==0)
						a[i][j] = 1;
			get_avail();
			if(getpiece())
			{
				printf("yes.\n");
			}
			else
			{
				printf("no.\n");
			}
		}
		else
		{
			int res = miss();
			if(res)
				printf("yes.\n");
			else
				printf("no.\n");
		}
		printf("\n");
		getchar();
	}
	return 0;
}

