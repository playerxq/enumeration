#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <iostream>
#include <algorithm>
using namespace std;
char substr[1000+5][15+5]={'\0'};
int subcnt=0;
char addstr[1000+5][15+5]={'\0'};
int addcnt=0;
int M=0;
char delstr[15+5]={'\0'};//delete string
char instr[15+5]={'\0'};//input string
/*struct the delstr*/
int FindDelStr()
{
	char prestr[15]={'\0'};//compare string
	char rearstr[15]={'\0'};
	int i1=0,i2=0,j=0,k=0;
	if(subcnt>=1)
	{
		strcpy(prestr,substr[0]);
		strcpy(delstr,prestr);
	}
	for(k=1;k<=subcnt-1;k++)
	{
		strcpy(rearstr,substr[k]);
		//get the delstr pattern
		i1=0;
		i2=0;
		j=0;
		while(prestr[i1]!='.'&&rearstr[i2]!='.')//~~~~~.  left of the '.'
		{
			if(prestr[i1]==rearstr[i2])
			{
				delstr[j]=prestr[i1];
			}
			else
			{
				if(prestr[i1]=='*')
				{
					//let the i2 point the left 1 bit of the '.'
					while(rearstr[i2]!='.')
					{
						i2++;
					}
					i2--;//point the left 1 bit of the '.'
					delstr[j]='*';
				}
				else
				{
					delstr[j]='?';
				}
			}
			i1++;
			i2++;
			j++;
		}
		if(prestr[i1]==rearstr[i2])//=='.' besides  i1==i2
		{
			delstr[j]='.';
			j++;
		}
		else
		{
			delstr[j]='*';
			j++;
			delstr[j]='.';
			j++;
		}
		while(prestr[i1]!='.')
		{
			i1++;
		}
		i1++;//i1 point the . right
		while(rearstr[i2]!='.')
		{
			i2++;
		}
		i2++;//i2 point the . right

		while(prestr[i1]!='\0'&&rearstr[i2]!='\0')//~~~~~.  left of the '.'
		{
			if(prestr[i1]==rearstr[i2])
			{
				delstr[j]=prestr[i1];
			}
			else
			{
				if(prestr[i1]=='*')
				{
					//let the i2 point the left 1 bit of the '\0'
					while(rearstr[i2]!='\0')
					{
						i2++;
					}
					i2--;//point the left 1 bit of the '\0'
					delstr[j]='*';
				}
				else
				{
					delstr[j]='?';
				}
			}
			i1++;
			i2++;
			j++;
		}
		if(prestr[i1]==rearstr[i2])//=='.' besides  i1==i2
		{
			delstr[j]='\0';
			j++;
		}
		else
		{
			delstr[j]='*';
			j++;
			delstr[j]='\0';
			j++;
		}
		strcpy(prestr,delstr);//next update the delstr
	}
	return(0);
}
/*test the delstr whether can test the no del string*/
bool TestNoDelStr()
{
	if(addcnt==0)
	{
		strcpy(delstr,"*.*");
		return(true);
	}
	int i=0,j=0,k=0;
	int flag=0;//flag=1 indicate it is match for the delstr
	for(k=0;k<=addcnt-1;k++)
	{
		i=0;
		j=0;
		flag=1;
		while(delstr[i]!='.'&&addstr[k][j]!='.')
		{
			if(delstr[i]!=addstr[k][j])
			{
				if(delstr[i]=='?')
				{

				}
				else if(delstr[i]=='*')
				{
					while(addstr[k][j]!='.')//let the point the '.' left one bit
					{
						j++;
					}
					j--;
				}
				else
				{
					flag=0;
					//return(true);
				}
			}
			i++;
			j++;
		}
		if(delstr[i]=='*')
		{
			i++;
		}
		if(delstr[i]!=addstr[k][j])//must reach '.' at the same times
		{
			flag=0;
		}
		i++;
		j++;//point the . right
		while(delstr[i]!='\0'&&addstr[k][j]!='\0')
		{
			if(delstr[i]!=addstr[k][j])
			{
				if(delstr[i]=='?')
				{

				}
				else if(delstr[i]=='*')
				{
					while(addstr[k][j]!='\0')//let the point the '.' left one bit
					{
						j++;
					}
					j--;
				}
				else
				{
					flag=0;
					//return(true);
				}
			}
			i++;
			j++;
		}
		if(delstr[i]=='*')
		{
			i++;
		}
		if(delstr[i]!=addstr[k][j])//must reach '\0' at the same times
		{
			flag=0;
		}
		if(flag)
		{
			return(false);
		}
	}
	return(true);//the delstr match the all addstr then return false that this delstr is invalid
}
/*main process*/
int MainProc()
{
	scanf("%d",&M);
	getchar();//eat the \n
	getchar();
	while(M--)
	{
		//init
		subcnt=0;
		addcnt=0;
		memset(delstr,'\0',sizeof(delstr));
		while(fgets(instr,15,stdin)!=NULL&&instr[0]!='\n')//not the EOF,EOF is int type
		{
			int inlen=strlen(instr);
			instr[inlen-1]='\0';//cover the \n
			inlen--;
			if(strchr(instr,'.')==NULL)
			{
				instr[inlen]='.';
				instr[inlen+1]='\0';
				inlen++;
			}
			if(instr[0]=='-')//- delete string
			{
				strcpy(substr[subcnt],instr+1);//abandon the + or -
				subcnt++;
			}
			else//+ do not delete string
			{
				strcpy(addstr[addcnt],instr+1);
				addcnt++;
			}
		}
		//test
		int i=0;
		if(addcnt>0)
		FindDelStr();//if addcnt==0  we can del *.*
		if(TestNoDelStr())//the delstr is valid
		{
			printf("DEL %s\n",delstr );
		}
		else//impossible
		{
			printf("IMPOSSIBLE\n");
		}
		//blank line between datasets
		if(M>0)
		{
			printf("\n");
		}
	}
	return(0);
}
int main(int argc, char const *argv[])
{
	/* code */
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	MainProc();
	return 0;
}
