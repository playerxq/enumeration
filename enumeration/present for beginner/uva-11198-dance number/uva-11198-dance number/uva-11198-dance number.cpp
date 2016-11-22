// uva-11198-dance number.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<stdio.h>
#include<string.h>
#include<math.h>
struct node
{
	int a[9],time;
}q[40321];
int prime[16]={0,0,1,1,0,1,0,1,0,0,0,1,0,1,0,0},visit[40321],
    Exp[11]={0,1,1,2,6,24,120,720,5040},top,tail,f;//7!为第8位的指标   逆序数*阶乘数为排列映射的值

int hash(int team[])
{
	 int I,J,K,S=0;
	 for (I=8;I>=2;I--)//第一位逆序数为0  不考虑
	 {
		  K=0;
		  for (J=1;J<I;J++)
		  if (abs(team[J])>abs(team[I])) ++K;//逆序数
		  S=S+K*Exp[I];
	 }
     return S;
};
int main()
{
	int n=0,i,j,k,team[9],t,temp;
    while (scanf("%d",&q[1].a[1]),q[1].a[1])
    {
		for (i=2;i<=8;i++)
			scanf("%d",&q[1].a[i]);
		memset(visit,0,sizeof(visit));
		visit[hash(q[1].a)]=1;//初始排列
		top=1; tail=1; f=0;
		q[1].time=0;

		while ((f==0)&&(top<=tail))  //以后bfs还是写成非递归的安全，栈溢出真的很蛋疼，找了一上午才想到
		{
			if (hash(q[top].a)==0) 
			{
				f=1;break;
			}
			for (i=1;i<=7;i++)//j是否可以换到i旁边
				for (j=i+1;j<=8;j++)
				{
					if ((q[top].a[i]*q[top].a[j]<0)&&(prime[abs(q[top].a[i])+abs(q[top].a[j])]==1))
					{
						for (k=1;k<=8;k++)   
							team[k]=q[top].a[k];  
						t=team[j];
						for (k=j;k>i;k--)    
							team[k]=team[k-1];    
						temp=team[i+1]; 
						team[i+1]=t;//j换到i右边
						if (visit[hash(team)]==0) 
						{
							visit[hash(team)]=1; //状态入队
							++tail; 
							for (k=1;k<=8;k++) 
								q[tail].a[k]=team[k];
							q[tail].time=q[top].time+1;
						}

					team[i+1]=temp;   team[i]=t;//放到左边
					if (visit[hash(team)]==0) 
					{
						visit[hash(team)]=1; 
						++tail; 
						for (k=1;k<=8;k++) 
							q[tail].a[k]=team[k];
						q[tail].time=q[top].time+1;
					}
 
					for (k=1;k<=8;k++)   
						team[k]=q[top].a[k];  
					t=team[i];
					for (k=i;k<j;k++)    
						team[k]=team[k+1];    
					temp=team[j-1]; 
					team[j-1]=t;  //i换到j的左边
					if (visit[hash(team)]==0) 
					{
						visit[hash(team)]=1; 
						++tail; 
						for (k=1;k<=8;k++) 
							q[tail].a[k]=team[k];
						q[tail].time=q[top].time+1;
					}

					team[j-1]=temp;   team[j]=t;  //i换到j右边
					if (visit[hash(team)]==0) 
					{
						visit[hash(team)]=1; 
						++tail; 
						for (k=1;k<=8;k++) 
							q[tail].a[k]=team[k];
						q[tail].time=q[top].time+1;
					}
				}
			}
			++top;
		}
		printf("Case %d: ",++n);
		if (f)  printf("%d\n",q[top].time);
		else   printf("-1\n");
	}
 return 0;
}



