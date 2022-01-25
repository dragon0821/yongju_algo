#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;
/*
    https://www.acmicpc.net/problem/10825
    endl->"\n"
    cin->scanf의 사용을 권장하는 문제였음
    평범한 sort 사용문제
*/
struct info {
	string name;
	int korea, english, math;
};
bool compare(info a, info b)
{
	if (a.korea == b.korea){
		if (a.english == b.english){
			if (a.math == b.math){
				return a.name < b.name;
			}
			else return a.math > b.math;
		}
		else return a.english < b.english;
	}
	else return a.korea > b.korea;
}
int main(void)
{
	int n;
	scanf("%d", &n);
	vector<info> information(n);

	for (int i = 0; i < n; i++)
	{
		cin >> information[i].name >> information[i].korea >> information[i].english >> information[i].math;
	}
	sort(information.begin(), information.end(), compare);
	for (int i=0;i<n;i++)
	{
		cout << information[i].name <<"\n";
	}
	return 0;
}