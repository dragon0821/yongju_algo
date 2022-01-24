#include <string>
#include <vector>
#include <map>
#include <queue>
using namespace std;
struct machine {
    int y1, x1, y2, x2, state;
};
typedef pair<int,int> mm;
map<pair<mm,mm>,int> visited;

int dy[] = { 0,0,-1,1 };
int dx[] = { -1,1,0,0 };
int ddy[] = { -1,-1,0,  0,1,1  ,  -1,-1,0,  0,1,1 };
int ddx[] = { -1,0,-1, -1,-1,0 ,  0,1,1,    1,1,0 };
int answer = 0;
//가로->세로 0~5는 2번 기준 6~11는 1번 기준
//세로->가로 0~2는 2번 기준 3~5는 1번 기준 6~8는 2번기준 9~11는 1번기준

/*
    https://programmers.co.kr/learn/courses/30/lessons/60063
    이거는 notion 알고리즘에 적힌 map의 이용사항을 유의해야함 (typedef 이용하는거)
    map으로 해당 machine의 구도를 확인해야함
    bfs로 끝까지 가장 먼저 간 machine을 출력함
    각각의 위치를 고려해서 가능한 곳을 잘 확인해야함
*/
void bfs(vector<vector<int>> board);
int solution(vector<vector<int>> board) {

    bfs(board);

    return answer;
}
void bfs(vector<vector<int>> board)
{
    int n = board.size();
    queue<machine> q;
    q.push({ 0,0,0,1,1 });
    visited[{ {0, 0}, { 0, 1 } }] = 1;
    while (!q.empty())
    {
        int y1, x1, y2, x2, state;
        y1 = q.front().y1; x1 = q.front().x1; y2 = q.front().y2; x2 = q.front().x2; state = q.front().state;
        q.pop();
        if ((y1 == n - 1 && x1 == n - 1) || (y2 == n - 1 && x2 == n - 1))
        {
            answer = visited[{ {y1, x1}, { y2, x2 }}] - 1;
            break;
        }
        for (int dir = 0; dir < 4; dir++)
        {
            if (y1 + dy[dir] < 0 || y1 + dy[dir] >= n || y2 + dy[dir] < 0 || y2 + dy[dir] >= n ||
                x1 + dx[dir] < 0 || x1 + dx[dir] >= n || x2 + dx[dir] < 0 || x2 + dx[dir] >= n)
                continue;
            if (board[y1 + dy[dir]][x1 + dx[dir]] == 1 || board[y2 + dy[dir]][x2 + dx[dir]] == 1)
                continue;
            if (visited[{ {y1 + dy[dir], x1 + dx[dir]}, { y2 + dy[dir], x2 + dx[dir] }}] == 0)
            {
                visited[{ {y1 + dy[dir], x1 + dx[dir]}, { y2 + dy[dir], x2 + dx[dir] }}] = visited[{ {y1, x1}, { y2, x2 }}] + 1;
                q.push({ y1 + dy[dir],x1 + dx[dir],y2 + dy[dir],x2 + dx[dir],state });
            }
        }
        if (state == 2)
        {
            for (int dir = 0; dir < 12; dir += 3)
            {
                bool check = false;
                if (dir == 0 || dir == 6)
                {
                    for (int i = dir; i < dir + 3; i++)
                    {
                        if (y2 + ddy[i] < 0 || y2 + ddy[i] >= n || x2 + ddx[i] < 0 || x2 + ddx[i] >= n || board[y2 + ddy[i]][x2 + ddx[i]] == 1)
                        {
                            check = true;
                            break;
                        }
                    }
                }
                else if (dir == 3 || dir == 9)
                {
                    for (int i = dir; i < dir + 3; i++)
                    {
                        if (y1 + ddy[i] < 0 || y1 + ddy[i] >= n || x1 + ddx[i] < 0 || x1 + ddx[i] >= n || board[y1 + ddy[i]][x1 + ddx[i]] == 1)
                        {
                            check = true;
                            break;
                        }
                    }
                }
                if (check == true)
                    continue;
                if (dir == 0)
                {
                    if (visited[{ {y1 + 1, x1 - 1}, { y2, x2 }}] == 0)
                    {
                        visited[{ {y1 + 1, x1 - 1}, { y2, x2 }}] = visited[{ {y1, x1}, { y2, x2 }}] + 1;
                        q.push({ y1 + 1,x1 - 1,y2,x2,1 });
                    }
                }
                else if (dir == 3)
                {
                    if (visited[{ {y2 - 1, x2 - 1}, { y1, x1 }}] == 0)
                    {
                        visited[{ {y2 - 1, x2 - 1}, { y1, x1 }}] = visited[{ {y1, x1}, { y2, x2 }}] + 1;
                        q.push({ y2 - 1,x2 - 1,y1,x1,1 });
                    }
                }
                else if (dir == 6)
                {
                    if (visited[{ {y2, x2}, { y1 + 1, x1 + 1 }}] == 0)
                    {
                        visited[{ {y2, x2}, { y1 + 1, x1 + 1 }}] = visited[{ {y1, x1}, { y2, x2 }}] + 1;
                        q.push({ y2,x2,y1 + 1,x1 + 1,1 });
                    }
                }
                else if (dir == 9)
                {
                    if (visited[{ {y1, x1}, { y2 - 1, x2 + 1 }}] == 0)
                    {
                        visited[{ {y1, x1}, { y2 - 1, x2 + 1 }}] = visited[{ {y1, x1}, { y2, x2 }}] + 1;
                        q.push({ y1,x1,y2 - 1,x2 + 1,1 });
                    }
                }
            }
        }
        else
        {
            for (int dir = 0; dir < 12; dir += 3)
            {
                bool check = false;
                if (dir < 6)
                {
                    for (int i = dir; i < dir + 3; i++)
                    {
                        if (y2 + ddy[i] < 0 || y2 + ddy[i] >= n || x2 + ddx[i] < 0 || x2 + ddx[i] >= n || board[y2 + ddy[i]][x2 + ddx[i]] == 1)
                        {
                            check = true;
                            break;
                        }
                    }
                }
                else if (dir >= 6)
                {
                    for (int i = dir; i < dir + 3; i++)
                    {
                        if (y1 + ddy[i] < 0 || y1 + ddy[i] >= n || x1 + ddx[i] < 0 || x1 + ddx[i] >= n || board[y1 + ddy[i]][x1 + ddx[i]] == 1)
                        {
                            check = true;
                            break;
                        }
                    }
                }
                if (check == true)
                    continue;
                if (dir == 0)
                {
                    if (visited[{ {y2 - 1, x2}, { y2, x2 }}] == 0)
                    {
                        visited[{ {y2 - 1, x2}, { y2, x2 }}] = visited[{ {y1, x1}, { y2, x2 }}] + 1;
                        q.push({ y2 - 1,x2,y2,x2,2 });
                    }
                }
                else if (dir == 3)
                {
                    if (visited[{ {y2, x2}, { y2 + 1, x2 }}] == 0)
                    {
                        visited[{ {y2, x2}, { y2 + 1, x2 }}] = visited[{ {y1, x1}, { y2, x2 }}] + 1;
                        q.push({ y2,x2,y2 + 1,x2,2 });
                    }
                }
                else if (dir == 6)
                {
                    if (visited[{ {y1 - 1, x1}, { y1, x1 }}] == 0)
                    {
                        visited[{ {y1 - 1, x1}, { y1, x1 }}] = visited[{ {y1, x1}, { y2, x2 }}] + 1;
                        q.push({ y1 - 1,x1,y1,x1,2 });
                    }
                }
                else if (dir == 9)
                {
                    if (visited[{ {y1, x1}, { y1 + 1, x1 }}] == 0)
                    {
                        visited[{{y1, x1}, { y1 + 1, x1 }}] = visited[{ {y1, x1}, { y2, x2 }}] + 1;
                        q.push({ y1,x1,y1 + 1,x1,2 });
                    }
                }
            }
        }
    }
}