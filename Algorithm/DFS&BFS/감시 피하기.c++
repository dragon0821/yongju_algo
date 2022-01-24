#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
int n;
char NN[7][7];
char rent[7][7];
vector<pair<int, int>> obj;
vector<pair<int, int>> teacher;
string answer = "NO";
/*
    https://www.acmicpc.net/problem/18428
    연구소랑 굉장히 비슷! 대신 이거는 딱 한번만이라도 학생이 감시를 완전히 피할 수 있다면 
    바로 끝
*/
bool cctv()
{
	for (int i = 0; i < teacher.size(); i++)
	{
		int ty = teacher[i].first; int tx = teacher[i].second;
		for (int y = ty-1; y >=0; y--)
		{
			if (rent[y][tx] == 'S')
				return false;
			if (rent[y][tx] == 'O')
				break;
		}
		for (int y = ty + 1; y < n; y++)
		{
			if (rent[y][tx] == 'S')
				return false;
			if (rent[y][tx] == 'O')
				break;
		}
		for (int x = tx-1 ; x>=0;x--)
		{
			if (rent[ty][x] == 'S')
				return false;
			if (rent[ty][x] == 'O')
				break;
		}
		for (int x = tx + 1; x < n; x++)
		{
			if (rent[ty][x] == 'S')
				return false;
			if (rent[ty][x] == 'O')
				break;
		}
	}
	return true;
}
void reculsive()
{
	if (obj.size() == 3)
	{
		if (cctv() == true)
			answer = "YES";
		return;
	}
	for (int y = 0; y < n; y++)
	{
		for (int x = 0; x < n; x++)
		{
			if (rent[y][x] == 'X')
			{
				obj.push_back({ y,x });
				rent[y][x] = 'O';
				reculsive();
				rent[obj.back().first][obj.back().second] = 'X';
				obj.pop_back();
				for (pair<int, int> o : obj)
				{
					rent[o.first][o.second] = 'O';
				}
			}
		}
	}
}
int main()
{
	scanf("%d", &n);
	for (int y = 0; y < n; y++)
	{
		for (int x = 0; x < n; x++)
		{
			cin >> NN[y][x];
			rent[y][x] = NN[y][x];
			if (NN[y][x] == 'T')
				teacher.push_back({ y,x });
		}
	}
	reculsive();
	cout << answer << "\n";
	return 0;
}