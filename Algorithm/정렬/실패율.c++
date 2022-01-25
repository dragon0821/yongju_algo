#include <string>
#include <vector>
#include <algorithm>
using namespace std;
/*
    https://programmers.co.kr/learn/courses/30/lessons/42889
    (double)cnt[i]/total 이렇게 해야지만 double로 결과가 나옴.
    (double)(cnt[i]/total)이렇게 하면 int를 double화 하는걸로 됨 -> (cnt[i]/total)의 결과와 같아짐
    //계수 정렬을 이용하여 해당 stage에 있는 사람들의 수를 찾아 해당 값을 이용하여 풀이
*/

bool compare(pair<double,int> a, pair<double,int> b)
{
    if(a.first==b.first)
        return a.second < b.second;
    else
        return a.first > b.first;
}
vector<int> solution(int N, vector<int> stages) {
    vector<int> answer;
    vector<pair<double,int>> ans;
    vector<int> cnt(502);
    
    long long total=0;
    
    for(int stage : stages){
        total++;
        cnt[stage]++;
    }
    
    for(int i=1;i<=N;i++){
        if(total!=0)
        {
            ans.push_back({(double)cnt[i]/total,i});
            total-=cnt[i];
        }
        else
            ans.push_back({0,i});
    }
    sort(ans.begin(),ans.end(),compare);
    for(int i=0;i<ans.size();i++)
    {
        answer.push_back(ans[i].second);
    }
    return answer;
}