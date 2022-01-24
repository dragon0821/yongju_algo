#include <iostream>
#include <vector>
using namespace std;
struct xy {
	int y, x;
};
int height, width;
int lab[9][9] = { 0 }; 
int rent[9][9] = { 0 };
vector<xy> empty_space;
vector<xy>block;
bool visited[9][9] = { 0 };
int dy[] = { 0,0,-1,1 };
int dx[] = { -1,1,0,0 };
int safe_zone = 0;
/*
    https://www.acmicpc.net/problem/14502
    reculsive를 통해 막을 벽을 3개를 임의로(컴비네이션 식으로) 막아두고
    해당 벽에 따라 바이러스가 퍼지게 함
*/
void virus(int y,int x)
{
	for (int i = 0; i < 4; i++)
	{
		if (y + dy[i] < 0 || y + dy[i] >= height || x + dx[i] < 0 || x + dx[i] >= width)
			continue;
		if (rent[y + dy[i]][x + dx[i]] == 0)
		{
			rent[y + dy[i]][x + dx[i]] = 2;
			virus(y + dy[i], x + dx[i]);
		}
	}
}
void reculsive(int cnt)
{
	if (cnt == 3)
	{
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				if (rent[y][x] == 2)
				{
					virus(y, x); //바이러스가 하나만 있어도 동서남북으로 퍼지게 하는 코드
				}
			}
		}
		int check = 0;
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				if (rent[y][x] == 0)
					check++; //안전지대의 수를 찾는다.
				rent[y][x] = lab[y][x]; //원래대로 돌려놓기
			}
		}
		safe_zone = safe_zone < check ? check : safe_zone; // 최종 최대값을 찾는다
		return;
	}
	for (int i = 0; i < empty_space.size(); i++)
	{
		if (rent[empty_space[i].y][empty_space[i].x] != 0)
			continue;
		rent[empty_space[i].y][empty_space[i].x] = 1;
		block.push_back({ empty_space[i].y ,empty_space[i].x });
		reculsive(cnt + 1);
		block.pop_back();
		rent[empty_space[i].y][empty_space[i].x] = 0;
		for(int b=0;b<block.size();b++) //cnt==3일때 rent가 초기 상태로 돌아가서 내가 재귀로 이전에 쌓아둔 값이 0으로 바뀌니까 1로 해줌
			rent[block[b].y][block[b].x] = 1;
	}
}
int main()
{
	cin >> height >> width;
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			cin >> lab[y][x];
			rent[y][x] = lab[y][x];
			if (lab[y][x] == 0)
				empty_space.push_back({ y,x });
		}
	}
	reculsive(0);
	cout << safe_zone << endl;
	return 0;
}