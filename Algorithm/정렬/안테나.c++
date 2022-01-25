#define _CRT_SECURE_NO_WARNINGS
#include <algorithm>
#include <stdio.h>
#include <vector>
using namespace std;
/*
    https://www.acmicpc.net/problem/18310
    정렬 한후에 중간에 있는 값이 가장 차이가 덜 날 수 밖에 없는 거였음
*/
int main()
{
	int house;
	scanf("%d", &house);
    vector<int> loc(house);
	for (int i = 0; i < house; i++)
	{
		scanf("%d", &loc[i]);
	}
    house--;
	sort(loc.begin(),loc.end());
    printf("%d\n",loc[(int)(house/2)]);
	return 0;
}