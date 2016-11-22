// uva-104420-knight in fen.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<stdio.h>
#include<string.h>
int a[5][5],move[8][2]={{-1,-2},{-1,2},{-2,1},{-2,-1},{2,1},{2,-1},{1,-2},{1,2}},
    b[5][5]={{1,1,1,1,1},{0,1,1,1,1},{0,0,2,1,1},{0,0,0,0,1},{0,0,0,0,0}},min;
int dfs(int x,int y,int step,int way)//way  跳过来的方向
{
	int i,j,X,Y,sum=0,t;
	if (step>=min) return 0;
	for (i=0;i<5;i++)
		for (j=0;j<5;j++)
			if (a[i][j]!=b[i][j]) ++sum;
	if (sum==0) //达到目标状态
	{
		if (step<min) 
			min=step; 
		return 0;
	}
	if ((sum+1)/2+step>=min) 
		return 0; //SUM表示与目标状态不同的位置个数，则最少需要(移动一次最多2个位置与目标状态相同）sum/2+sum%2=（sum+1）/2步才能变为目标状态
	for (i=0;i<8;i++)
	{
		X=x+move[i][0];
		Y=y+move[i][1];
		if ((X>=0)&&(X<5)&&(Y>=0)&&(Y<5)&&(way+i!=7)) //初始化move时将相反跳法的下标和为7，这样就可以每次避免走回头路省略判重过程
		{//way+i不为7则i与来时方向不反  不是返回的跳法
			t=a[x][y];a[x][y]=a[X][Y];a[X][Y]=t;
			dfs(X,Y,step+1,i);
			t=a[x][y];a[x][y]=a[X][Y];a[X][Y]=t;
		}
	}
}
int main()
{int i,j,x,y,n;
 char s[6];
 scanf("%d\n",&n);
 while (n--)
 {
  for (i=0;i<5;i++)
  {gets(s);
   for (j=0;s[j]!='\0';j++)
   if (s[j]==' ') {a[i][j]=2;x=i;y=j;}
             else a[i][j]=s[j]-'0';
  }
  min=11;//至多11步
  dfs(x,y,0,8);//way = 8  不可能有相反向  为初始化
  if (min==11) printf("Unsolvable in less than 11 move(s).\n");
  else printf("Solvable in %d move(s).\n",min);
 }
 return 0;
}

