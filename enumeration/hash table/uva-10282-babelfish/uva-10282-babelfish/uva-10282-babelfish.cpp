// uva-10282-babelfish.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<string.h>
using namespace std;
struct list
{
    int leap;
    char str[100];//当前节点到root的代表的字符串
    struct list *next[26];//下一层26个字母
};
struct list *tree;//字典树
struct list *code()
{
    int i;
    struct list *p;
    p=new list;
    for(i=0;i<26;i++)
    {
        p->next[i]=NULL;
    }
    p->leap=0;
    return p;
}
void insert(char str1[],char str2[])
{
    int n,i,w;
    n=strlen(str1);
    struct list *p;
    p=tree;
    for(i=0;i<n;i++)
    {
        w=str1[i]-'a';
        if(p->next[w]==NULL)
        {
            p->next[w]=code();
        }
        p=p->next[w];
    }
    p->leap=1;
    strcpy(p->str,str2);
}
void search(char str[])
{
    int i,n,w;
    struct list *p;
    p=tree;
    n=strlen(str);
    for(i=0;i<n;i++)
    {
        w=str[i]-'a';
        if(p->next[w]==NULL)break;
        p=p->next[w];
    }
    if(i<n||p->leap==0)
    cout<<"eh"<<endl;
    else
    {
        cout<<p->str<<endl;
    }
}
int main()
{
    int i,len;
    char strr[100],str[100],str1[100],str2[100];
    tree=code();
    while(gets(strr))
    {
        len=strlen(strr);
        if(len==0)break;
        int w=0;
        for(i=0;i<len;i++)
        {
            if(strr[i]==' ')w=i+1;
            else
            {
                if(w==0)
                {
                    str1[i]=strr[i];
                }
                else
                {
                    str2[i-w]=strr[i];
                }
            }
        }
        str1[w-1]='\0';
        str2[len-w]='\0';
        insert(str2,str1);
    }
    while(gets(str))
    {
        search(str);
    }
    return 0;
}








