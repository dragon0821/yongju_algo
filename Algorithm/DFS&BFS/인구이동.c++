#include <iostream>
#include <queue>
#include <vector>
using namespace std;
struct yx {
	int y, x, sum;
};
int N_size; int Min_diff; int Max_diff; int answer = 0;
int dy[] = { 0,0,-1,1 };
int dx[] = { -1,1,0,0 };
int country[51][51] = { 0 }; //나라의 인구수 배열
int boundary[51][51] = { 0 }; //원하는 차이값 안에 드는 나라들 경계 선 그을 배열
vector<yx> union_num[2502]; // 경계가 같은 나라들의 위치, 그들의 인구 수 합 구하는 vector <- 나라의 수 만큼 배열의 크기가 필요했음(50으로 했다가 러타임 에러(out of bound)
queue <yx> q;
/*
	https://www.acmicpc.net/problem/16234
    계속 확인하면서 인구의 이동이 필요없는 경우까지 하는 것임
*/
void Union()
{
	int count = 0;
	for (int y = 0; y < N_size; y++)
	{
		for (int x = 0; x < N_size; x++)
		{
			int SUM = 0;
			if (boundary[y][x] == 0)
				continue;
			if (!union_num[boundary[y][x]].empty()) //union_num에 해당 boundary 숫자가 이미 있었던 경우
				SUM = union_num[boundary[y][x]].back().sum; // 가장 최근에 push한 값의 sum값을 가져옴
			union_num[boundary[y][x]].push_back({ y,x ,SUM += country[y][x] }); //같은 경계에 있는 나라의 위치, 해당 나라들의 합을 저장
			count = count < boundary[y][x] ? boundary[y][x] : count;
		}
	}
	for (int i = 0; i <= count; i++)
	{
		if (!union_num[i].empty())
		{
			int average = union_num[i].back().sum / union_num[i].size(); //평균 구해서
			while (!union_num[i].empty())
			{
				country[union_num[i].back().y][union_num[i].back().x] = average; //바꿔줌
				union_num[i].pop_back(); // 계속 boundary의 숫자를 0부터 쓸거라서 비워줘야함
			}
		}
	}
}
void solution()
{
	// 최대한 원하는 차이값에 들어가는 모든 나라들에 같은 경계임을 알 수 있게 boundary배열을 같은 수로 채워줌
	while (!q.empty())
	{
		int nowy = q.front().y; int nowx = q.front().x; int nowcnt = boundary[nowy][nowx];
		q.pop();

		for (int i = 0; i < 4; i++)
		{
			if (nowy + dy[i] < 0 || nowy + dy[i] >= N_size || nowx + dx[i] < 0 || nowx + dx[i] >= N_size)
				continue;
			if (boundary[nowy + dy[i]][nowx + dx[i]] == nowcnt)
				continue;
			int check = abs(country[nowy][nowx] - country[nowy + dy[i]][nowx + dx[i]]);
			if (check >= Min_diff && check <= Max_diff)
			{
				q.push({ nowy + dy[i],nowx + dx[i],0 });
				boundary[nowy + dy[i]][nowx + dx[i]] = nowcnt;
			}
		}
	}
}
int main()
{
	cin >> N_size >> Min_diff >> Max_diff;
	for (int y = 0; y < N_size; y++)
		for (int x = 0; x < N_size; x++)
			cin >> country[y][x];
	while (1)
	{
		//아래 for문은 지금 현재 나라들 중에서 우리가 원하는 차이 값 안에 드는 나라들이 있는지 확인
		bool check = true;
		for (int y = 0; y < N_size; y++)
		{
			for (int x = 0; x < N_size; x++)
			{
				boundary[y][x] = 0; 
				//무조건 boundary 값을 초기화해줘야 해서 check=false가 되는 상황이어도 그냥 끝까지 감
				for (int i = 0; i < 4; i++)
				{
					if (y + dy[i] < 0 || y + dy[i] >= N_size || x + dx[i] < 0 || x + dx[i] >= N_size)
						continue;
					if (abs(country[y][x] - country[y + dy[i]][x + dx[i]]) >= Min_diff && abs(country[y][x] - country[y + dy[i]][x + dx[i]]) <= Max_diff)
					{
						//우리가 통합해야할 상황이 있는 경우
						check = false;
						break;
					}
				}
			}
		}
		if (check) //통합할 수 있는 나라가 없는 경우 모든 것을 멈춤
			break;
		answer++;//하루가 지나감
		int bc = 0;
		for (int y = 0; y < N_size; y++)
		{
			for (int x = 0; x < N_size; x++)
			{
				if (boundary[y][x] == 0)
				{
					boundary[y][x] = ++bc; // 경계를 그을 수
					q.push({ y,x,0 });
					solution();
				}
			}
		}
		//경계들을 다아아 찾고
		Union(); //경계가 그어진 나라들의 평균으로 그들의 값을 바꿔줌
	}
	cout << answer << endl;
	return 0;
}