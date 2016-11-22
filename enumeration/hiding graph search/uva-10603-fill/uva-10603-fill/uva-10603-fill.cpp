// uva-10603-fill.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<cstring>
using namespace std;
#define Max 201
struct Node{
	int volume[3];
	int amount;
};
int cap[3],flag;
int d,front,rear;
int vis[Max][Max];
Node q[Max*Max];
void bfs(void){
	int i,j,amount,k;
	q[0].volume[0]=q[0].volume[1]=q[0].amount=0;
	q[0].volume[2]=cap[2];
	vis[0][0]=1;
	front=0,rear=1;
	while(front<rear){
		Node &now=q[front];
		if(now.volume[0]==d||now.volume[1]==d||now.volume[2]==d){//某杯水有d升
			flag=1;
			return ;
		}
		for(i=0;i<3;i++){
			for(j=0;j<3;j++){
				if(i!=j){//第i杯向第j杯倒
					Node &next=q[rear];
					amount=now.volume[i]<(cap[j]-now.volume[j])?now.volume[i]:cap[j]-now.volume[j];//要么将j倒满要么将i倒空
					for(k=0;k<3;k++)
						next.volume[k]=now.volume[k];
					next.volume[i]-=amount;
					next.volume[j]+=amount;
					if(!vis[next.volume[1]][next.volume[2]]){//此容量下的状态为新的 总容量一定  故只需考虑一二两个杯子
						vis[next.volume[1]][next.volume[2]]=1;
						next.amount=now.amount+amount;
						rear++;
					}
				}
			}
		}
		front++;
	}
}
int main()
{
	int i,j,test_case;
	cin >>test_case;
	while(test_case--){
		flag=0;
		memset(vis,0,sizeof(vis));
		for(i=0;i<3;i++)
			cin>>cap[i];//三水杯容量
    	cin>>d;
    	bfs();
    	if(flag==1){
			cout << q[front].amount << " " << d << endl;
    	}
		else{
			for(i=d-1;i>=0;i--){
				for(j=0;j<=rear;j++){//遍历之前得到的所有状态看最接近d的某个状态
					if(q[j].volume[0]==i||q[j].volume[1]==i||q[j].volume[2]==i){//一杯最接近即可
						flag=1;
						break;
					}
				}
				if(flag)
					break;
			}
			cout << q[j].amount <<" " <<i<<endl;
		}
	}
	return 0;
}

