#include "stdafx.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>

class node
{
  public:
    int pos,w;
};

class set
{
 public:
   int ll,lr,rl,rr;
   int prev,ok;
};

set res[30][30];

node lefts[110],rights[110];
int lcount,rcount;
int find;
int L,W,C;

int abs(int i)
{
  if(i>0) return i;
  return -i;
}

void pans(int l,int r)
{
  if(l == 0 && r== 0)
    return;
  if(res[l][r].prev == 1)
  {
    printf("%d %d\n",rights[r-1].pos/2,rights[r-1].w);
    pans(l,r-1);
  }
  else
  {
    printf("%d %d\n",lefts[l-1].pos/2,lefts[l-1].w);
    pans(l-1,r);
  }
}
int cmp1(const void* a,const void* b)//左半边相对左支柱 越左力矩越大 中间的力矩为负 即顺时针
{
  node i = *(node*)a;
  node j = *(node*)b;
  return (-i.pos-3)*i.w - (-j.pos-3)*j.w;
}

int cmp2(const void* a,const void* b)
{
  node i = *(node*)a;
  node j = *(node*)b;
  return (i.pos-3)*i.w - (j.pos-3)*j.w;
}


int main()
{
   //freopen("in.txt","r",stdin);
   //freopen("out.txt","w",stdout);
   int i,c=1,j; 
   int ll,lr,rl,rr;
   while(scanf("%d%d%d",&L,&W,&C)!=EOF && L>0)
   {
     memset(res,0,sizeof(res));
     L *= 2;
     ll = rr =0; rl = lr = 3*W;//ll rr为左支柱左边 右支柱右边力矩 lr左支柱右边 rl右支柱左边
     node tmp; 
     lcount = rcount = 0;
     for(i=0;i<C;i++)
     {
       scanf("%d%d",&tmp.pos,&tmp.w);
       tmp.pos*=2;
      if(tmp.pos<0)
         lefts[lcount++] = tmp;
       else
         rights[rcount++] = tmp;
     }
     qsort(lefts,lcount,sizeof(node),cmp1);
     qsort(rights,rcount,sizeof(node),cmp2);
     
     set tmpset = {ll,lr,rl,rr,0,1};
     res[0][0] = tmpset;
     for(i=0;i<=lcount;i++)
      for(j=0;j<=rcount;j++)
      {
        if(i-1>=0 && res[i-1][j].ok == 1)
            {
                  tmpset = res[i-1][j];
                  //放了第i个物体
                 if(lefts[i-1].pos < -3)
                   tmpset.ll += (-3-lefts[i-1].pos)*lefts[i-1].w; 
                 else
                   tmpset.lr += (lefts[i-1].pos+3)*lefts[i-1].w;
                 if(lefts[i-1].pos < 3)
                   tmpset.rl += (3 - lefts[i-1].pos)*lefts[i-1].w;
                 //else
                   //tmpset.rr += (lefts[i-1].pos - 3)*lefts[i-1].w;//never occur
                 if(tmpset.ll < tmpset.lr && tmpset.rl>tmpset.rr)//平衡
                 {
                    tmpset.ok = 1;
                    tmpset.prev = -1;
                    res[i][j] = tmpset;
                 }
                 else
                   {
                     res[i][j].ok = 0;
                 }
            }
              
              
         if(res[i][j].ok) 
              continue;
         if(j-1>=0 && res[i][j-1].ok == 1)
            {
              tmpset = res[i][j-1];
               //if(rights[j-1].pos < -3)
                 //tmpset.ll += (-3-rights[j-1].pos)*rights[j-1].w; 
               //else
                 tmpset.lr += (rights[j-1].pos+3)*rights[j-1].w;
               if(rights[j-1].pos < 3)
                 tmpset.rl += (3 - rights[j-1].pos)*rights[j-1].w;
               else
                 tmpset.rr += (rights[j-1].pos - 3)*rights[j-1].w;
              if(tmpset.ll < tmpset.lr && tmpset.rl>tmpset.rr)
                 {
                    tmpset.ok = 1;
                    tmpset.prev = 1;
                    res[i][j] = tmpset;
                 }
                 else
                   {
                     res[i][j].ok = 0;
                 }
            }                      


      }
      printf("Case %d:\n",c++);
       if(res[lcount][rcount].ok == 1)
         pans(lcount,rcount);
       else
        printf("Impossible\n");
   }
   return 0;
}