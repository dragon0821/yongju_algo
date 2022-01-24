#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
int n;
int ope[4] = { 0 };
int rent[4] = { 0 };
vector<int> oo;
long long max_num = -9999999999;
long long min_num =  9999999999;
/*
    https://www.acmicpc.net/problem/14888
    개수가 각각 정해진 어떤것을 정렬하는 경우가 있을 때 생각하면 좋은 문제
    가끔 자주 풀어보기
*/
void calculate(vector<int> num)
{
	long long answer = num[0];
	for (int i = 0; i < oo.size(); i++)
	{
		if (oo[i] == 0)
			answer += num[i + 1];
		else if (oo[i] == 1)
			answer -= num[i + 1];
		else if (oo[i] == 2)
			answer *= num[i + 1];
		else
		{
			if (answer < 0)
				answer = (long long)(abs(answer) / num[i + 1])*(-1);
			else
				answer = (long long)(abs(answer) / num[i + 1]);
		}
	}
	max_num = answer > max_num ? answer : max_num;
	min_num = answer < min_num ? answer : min_num;
}
void reculsive(vector<int> num,int cnt)
{
	if (cnt == n - 1)
	{
		calculate(num);
		return;
	}
	for (int i = 0; i < 4; i++)
	{
		if (rent[i] == 0)
			continue;
		oo.push_back(i);
		rent[i]--;
		reculsive(num,cnt + 1);
		rent[i]++;
		oo.pop_back();
	}
}

int main()
{
	scanf("%d", &n);
	vector<int> num(n+1);
	for (int i = 0; i < n; i++)
		scanf("%d", &num[i]);
	for (int i = 0; i < 4; i++)
	{
		scanf("%d", &ope[i]);
		rent[i] = ope[i];
	}
	reculsive(num, 0);
	printf("%lld\n%lld\n", max_num, min_num);
	return 0;
}