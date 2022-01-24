#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
using namespace std;
int n, m, k, x;
int visited[300001] = { 0 };
queue<int> q;
vector<int> answer;
/*
    https://www.acmicpc.net/problem/18352
    시작 도시에서 어떤 어떤 도시로 가는 최단 거리를 계산해야하니까 한번에 쭈우우욱 계산해서 visited에 답아둠
    특정 거리인(답이 되는) 도시들을 answer 배열에 담아 오름차순으로 출력
*/

void bfs(vector<vector<int>> v, int k)
{
	while (!q.empty())
	{
		int depart = q.front();
		q.pop();
		if (visited[depart] > k)
			return;
		if (visited[depart] == k)
		{
			answer.push_back(depart);
		}
		else if (visited[depart] < k)
		{
			for (int num : v[depart])
			{
				if (visited[num] != 0)
					continue;
				visited[num] = visited[depart] + 1;
				q.push(num);
			}
		}
	}
}
int main()
{
	scanf("%d %d %d %d", &n, &m, &k, &x);
	vector<vector<int>> v(n + 1);
	for (int i = 0; i < m; i++)
	{
		int d, l;
		scanf("%d %d", &d, &l);
		v[d].push_back(l);
	}
	visited[x] = 1;
	q.push(x);
	bfs(v, k+1);
	if (!answer.empty())
	{
		sort(answer.begin(), answer.end());
		for (int a : answer)
		{
			printf("%d\n", a);
		}
	}
	else
		printf("-1\n");
	return 0;
}