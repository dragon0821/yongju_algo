#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
struct state {
	int kind, y, x;
};
int virus[201][201] = { 0 };
int visited[201][201] = { 0 };
vector<state> v;
int dy[] = { 0,0,-1,1 };
int dx[] = { -1,1,0,0 };
int n, k;
queue<pair<int, int>> q;
/*
    https://www.acmicpc.net/problem/18405
    번호가 낮은 종류의 바이러스부터 증식하기 때문에 v의 번호를 정렬함
    그래서 정렬된 벡터를 이용해 처음부터 쭉 퍼트림 
    위의 특징을 가지고 있기 때문에 다른 문제에 비해 rent 배열이 필요없음
*/
bool compare(state a, state b)
{
	return a.kind > b.kind;
}
void bfs(int s)
{
	while (!q.empty())
	{
		int y = q.front().first; int x = q.front().second;
		q.pop();
		v.pop_back();
		if (visited[y][x] >= s )
			return;
		for (int i = 0; i < 4; i++)
		{
			if (y + dy[i] < 0 || y + dy[i] >= n || x + dx[i] < 0 || x + dx[i] >= n)
				continue;
			if (virus[y + dy[i]][x + dx[i]] == 0)
			{
				visited[y + dy[i]][x + dx[i]] = visited[y][x] + 1;
				virus[y + dy[i]][x + dx[i]] = virus[y][x];
				v.push_back({ virus[y][x],y + dy[i],x + dx[i] });
				q.push({ y + dy[i],x + dx[i] });
			}
		}
	}

}
int main()
{
	scanf("%d %d", &n, &k);
	for (int y = 0; y < n; y++)
	{
		for (int x = 0; x < n; x++)
		{
			scanf("%d", &virus[y][x]);
			if (virus[y][x] != 0)
			{
				v.push_back({ virus[y][x],y,x });
			}
		}
	}
	int s, x, y;
	scanf("%d %d %d", &s, &y, &x);
	sort(v.begin(), v.end(), compare);
	auto iter = v.rbegin();
	while (iter != v.rend())
	{
		q.push({ iter->y,iter->x });
		iter++;
	}
	bfs(s);
	
	printf("%d\n", virus[y-1][x-1]);
	return 0;
}