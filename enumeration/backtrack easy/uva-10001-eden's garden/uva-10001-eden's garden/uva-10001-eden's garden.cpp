// uva-10001-eden's garden.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
// Garden of Eden （伊甸园）
// PC/UVa IDs: 110806/10001, Popularity: B, Success rate: average Level: 2
// Verdict: Accepted
// Submission Date: 2011-08-11
// UVa Run Time: 0.660s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// 该题可使用回溯法寻找给定状态的前驱，若能找到前驱，则为可达，若无法找到前驱，则为伊甸园状态。
// identifier 对应的规则 从0-255  即规则只有8位 每位对应000-111

#include <iostream>
#include <vector>
#include <string>
using namespace std;

#define CODESIZE 8

bool finished;
bool is_garden;

// 根据当前细胞和左右两个细胞的状态获得对应的变换规则码即规则索引。
int indexer(int a, int b, int c)//000-111中的某个值
{
	return (a << 2) + (b << 1) + c;
}

void evolution(vector <int> &a, vector <int> &b, int automaton[])//a->b
{
	int last = a.size() - 1;

	b[0] = automaton[indexer(a[last], a[0], a[1])];
	for (int i = 1; i < last; i++)
		b[i] = automaton[indexer(a[i - 1], a[i], a[i + 1])];
	b[last] = automaton[indexer(a[last - 1], a[last], a[0])];
}

// 比较两个状态是否相同。
bool equal(vector <int> &a, vector <int> &b)
{
	for (int i = 0; i < a.size(); i++)
		if (a[i] != b[i])
			return false;
	return true;
}

// 回溯寻找前驱。
void backtrack(vector <int> &ancestor, vector <int> &target,
        int automaton[], int current)//0--current+1已经分解逆推  当前开始判断cur+2位
{
	if (current == (ancestor.size() - 2))
	{
		vector <int> now(ancestor.size());
		
		evolution(ancestor, now, automaton);
		
		if (equal(now, target))
		{
			finished = true;
			is_garden = false;
		}
	}
	else
	{
		for (int i = 0; i <= 1; i++)//由于上一轮根据tar[cur]计算出ans[cur]和ans[cur+1]，此时根据tar[cur+1]只需计ans[cur+2]，按0,1两种分支展开
		{
			int index = indexer(ancestor[current], ancestor[current + 1], i);//按0 1和前2个值得到规则码
			if (automaton[index] == target[current + 1])
			{
				ancestor[current + 2] = i;
				backtrack(ancestor, target, automaton, current + 1);
			
				if (finished)
					return;
			}
		}
	}
}

// 判断是否有前驱存在。
bool no_ancestor(vector <int> &target, int automaton[])
{
	int cells = target.size();
	vector <int> ancestor(cells);

	for (int i = 0; i < CODESIZE; i++)
		if (automaton[i] == target[0])//某个规则码等于某位状态
		{	
			ancestor[cells - 1] = ((i & 4) >> 2);//改变对应位的状态 i为0-111中某个值 将i分解出左中右三个值
			ancestor[0] = ((i & 2) >> 1);
			ancestor[1] = (i & 1);
			
			finished = false;
			is_garden = true;

			backtrack(ancestor, target, automaton, 0);

			if (is_garden == false)
				return false;
		}

	return true;
}

// 判定给定的条件是否为伊甸园状态。
bool is_garden_of_eden(int identifier, int cells, string state)
{
	// 判断一些特殊的细胞自动机。
	if (identifier == 204)//规则：等于自己
		return false;
	
	// 当自动机编号为 0 时，有非 0 格则为伊甸园。
	if (identifier == 0)//规则： 任意值均取0
	{
		for (int i = 0; i < state.length(); i++)
			if (state[i] != '0')
				return true;
		return false;
	}
	
	// 当自动机编号为 255 时，有非 1 格则为伊甸园。
	if (identifier == 255)//规则：任意值取1
	{
		for (int i = 0; i < state.length(); i++)
			if (state[i] != '1')
				return true;
		return false;
	}
	
	// 获取最初状态，自动机对应的编码变换规则。
	vector <int> ancestor(cells);
	for (int i = 0; i < cells; i++)
		ancestor[i] = (state[i] - '0');
		
	int automaton[CODESIZE];
	for (int i = 0; i < CODESIZE; i++)//取8位规则码 每位对应000-111的某个值
	{
		automaton[i] = identifier % 2;
		identifier /= 2;
	}
	
	return no_ancestor(ancestor, automaton);
}

int main(int ac, char *av[])
{
	int identifier, cells;
	string state;

	// 读入数据。
	while (cin >> identifier >> cells >> state)
	{
		bool result = is_garden_of_eden(identifier, cells, state);
		cout << (result ? "GARDEN OF EDEN" : "REACHABLE") << endl;
	}

	return 0;
}

