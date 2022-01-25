#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <queue>
using namespace std;

/*
    https://www.acmicpc.net/problem/1715
    priority_queue를 통해서 연산의 작은 값들을 먼저 꺼내서 계산하면 되는 문제 priority_queue를 이용하면 자동 정렬됨
    그리고 카드가 한 묶음만 있다면 섞는 방법의 수는 0임
*/
int main()
{
	int n;
	scanf("%d", &n);

	priority_queue<long long> pq;

	for (int i = 0; i < n; i++)
	{
		int card;
		scanf("%d", &card);
		pq.push(card*(-1));
	}

	long long answer = 0;

	if (n >= 2)
	{
		int cnt = 0; long long two = 0;
		while (!pq.empty())
		{
			two += pq.top()*(-1);
			pq.pop();
			cnt++;
			if (cnt == 2)
			{
				answer += two;
				if (!pq.empty())
					pq.push(two*(-1));
				two = 0;
				cnt = 0;
			}
		}
	}
	else
		answer = 0;
	printf("%lld\n", answer);
	return 0;
}