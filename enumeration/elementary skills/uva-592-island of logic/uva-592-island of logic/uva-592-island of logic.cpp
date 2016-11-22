/*
    思路：枚举所有情况。
    this is impossible. 所以情况都不满足条件。
    No facts are deducible. 有满足条件的情况，但是情况之间没有交集，也就是说原条件不能推导出任何结论来。
    fact： 满足条件的情况之间的交集。
*/
#include "stdafx.h"
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

char kind[][20] = {"divine", "human", "evil"};
const int MAX_P = 5+5; //最大人数
int person[MAX_P]; //记录ABCD是人是妖
char name[MAX_P];  //记录对应的名字(考虑到只出现人名A、C，而不出现B等情况)
int name_order[MAX_P]; //记录A、B、C、D、E分别出现的顺序
int lying[MAX_P];  //0:lying 1:not lying
int time; //0:day, 1:night
int cur_p; //人数
struct line //台词
{
    int who_said; //who said
    int kind;// 0：句型1或2; 1:句型3
    int time; //0:day, 1:night
    int person; //person: 0-4
    int has_not; //not: 0, 1
    int id; //0-3, 3:lying
};
const int MAX_L = 50+5;
line lines[MAX_L];
int cur_l;
//结论
int found;
int result[MAX_P];
int r_time;

void dicide()
{
    for(int i=0; i<cur_p; i++) {//对所有出现的
        switch(person[i]) {
            case 0: lying[i] = 0; break;//diving不会说谎
            case 2: lying[i] = 1; break;//evil必说谎
            case 1: lying[i] = time;//人则按天气定
        }
    }
    int ok = 1;
    for(int i=0; i<cur_l; i++) {//对每句台词分析
        int flag = 1; //0：结论取反， 1：结论不需要取反
        if(lying[lines[i].who_said]) 
			flag = !flag; //如果说话人说谎，要取反
        if(lines[i].kind==0) { //句型1、2
            if(lines[i].has_not) 
				flag = !flag;  //如果原来语句含有not, 要取反
            if(lines[i].id != 3) {//判断自己or别人的角色
                if(flag && person[lines[i].person]!=lines[i].id) {//判断的角色与枚举此时既定的角色不一样
                    ok = 0; break;
                }
                if(!flag && person[lines[i].person]==lines[i].id) {
                    ok = 0; break;
                }
            } else { // X is lying.//某人说谎  可能是说自己or别人
                if(flag && !lying[lines[i].person]) {//判断说谎的对象人物是否真的在枚举情况时说谎？
                    ok = 0; break;
                }
                if(!flag && lying[lines[i].person]) {
                    ok = 0; break;
                }
            }
        } else { //句型3
            if(flag && time != lines[i].time) {//此时枚举的天气与说话中的天气不一样 且flag = 1
                ok = 0; break;
            }
            if(!flag && time == lines[i].time) {
                ok = 0; break;
            }
        }
    }
    if(ok) {
        if(!found) {
            memcpy(result, person, sizeof(person));//拷贝角色信息
            r_time = time;
            found = 1;
        } else {
            for(int i=0; i<cur_p; i++) {//以前枚举其他种角色时确定过角色信息  当前又有可能的角色信息 应取二者相同的部分
                if(person[i] != result[i]) {//有矛盾项目
                    result[i] = -1;
                }
            }
            if(r_time != time) r_time = -1;
        }
    }
}

void dfs(int cur)
{
    if(cur == cur_p) {//所有出现的人均赋予了某个身份
        time = 0;//按白天或黑夜枚举所有情况
        dicide();
        time = 1;
        dicide();
        return;
    }
    for(int i=0; i<3; i++) {
        person[cur] = i;
        dfs(cur+1);
    }
}

int insert_p(char n)
{
    for(int i=0; i<cur_p; i++) if(name[i] == n) {//已经出现过
        return i;
    }
    name[cur_p] = n;
    name_order[n-'A'] = cur_p;//第一次出现位置
    return cur_p++;

}
int main ()
{
    int T = 0;
    while(scanf("%d", &cur_l) == 1) {
        if(!cur_l) break;
        char buff[10];
        cur_p = 0;
        memset(name_order, -1, sizeof(name_order));
        for(int i=0; i<cur_l; i++) {
            scanf("%s", buff);
            lines[i].who_said = insert_p(buff[0]);
            scanf("%s", buff);
            if(buff[1] == 't') { //句型3
                lines[i].kind = 1;
                scanf("%s", buff); // is
                scanf("%s", buff); // day | night;
                if(buff[0] == 'd') lines[i].time = 0;
                else lines[i].time = 1;//记录时间
            } else { //句型1、2
                lines[i].kind = 0;
                if(buff[0] == 'I') {// i am....
                    lines[i].person = lines[i].who_said;//本人说
                } else {
                    lines[i].person = insert_p(buff[0]);//说别人  插入被说人
                }
                scanf("%s", buff);
                scanf("%s", buff);
                if(buff[0] == 'n') { // not
                    lines[i].has_not = 1;
                    scanf("%s", buff);
                }else {
                    lines[i].has_not = 0;
                }
                switch(buff[0]) {
                    case 'd': lines[i].id = 0; break; //divine
                    case 'h': lines[i].id = 1; break; //human
                    case 'e': lines[i].id = 2; break; //evil
                    case 'l': lines[i].id = 3; break; //lying
                }
            }
        }
        printf("Conversation #%d\n", ++T);
        found = false;
        dfs(0);
        int ok = 0;
        if(found) {
            for(int i=0; i<MAX_P; i++) {
                int order = name_order[i];//获取出现的顺序
                if(order != -1 && result[order] != -1){
                    ok = 1;
                    printf("%c is %s.\n", i+'A', kind[result[order]]);//此人角色已得到判断
                }
            }
            if(r_time != -1) {//天气得到判断
                ok = 1;
                printf("It is %s.\n", r_time?"night":"day");
            }
            if(!ok) printf("No facts are deducible.\n");
        } else {
            printf("This is impossible.\n");
        }
        printf("\n");
    }
    return 0;
}
