#include <string>
#include <vector>
#include <stack>
#include <iostream>
using namespace std;
string answer = "";
string mun = "";
bool re_v=false;
/*
    https://programmers.co.kr/learn/courses/30/lessons/60058
    그냥 시키는 대로 하면 되는 거임!
    string str="~~~";
    str.substr(a,b); -> a에서부터 b개의 개수만큼을 자름 str.substr(c); -> c에서 부터 끝까지임
    ex) string str ="0123456";
    string a = str.substr(2,3); -> a = {2,3,4};
    string b = str.substr(4); -> b = {4,5,6};
*/
bool check(string p);
int separate(string uv);
void reculsive(string uv);
string solution(string p) {
    
    if(check(p))
        answer+=p;
    else
    {
        reculsive(p);
    }
    return answer;
}

void reculsive(string uv)
{
    int se = separate(uv);
    string u=""; string v="";
    u = uv.substr(0,se+1); 
    if(se!=uv.length())
        v=uv.substr(se+1);
    if(check(u))
    {
        answer+=u;
        if(v != "")
            reculsive(v);
    }
    else if(!check(u))
    {
        answer+="(";
        if(v != "")
            reculsive(v);
        answer+=")";
        for(int j=1;j<u.length()-1;j++)
        {
            if(u[j]=='(')
                answer+=')';
            else
                answer+='(';
        }
    }
}

int separate(string uv)
{
    int o_cnt=0; int c_cnt=0;
    for(int i=0;i<uv.length();i++)
    {
        if(uv[i]=='(')
            o_cnt++;
        else if(uv[i]==')')
            c_cnt++;
        if(o_cnt-c_cnt==0)
            return i;
    }
}
bool check(string p)
{
    stack<int> s;
    for(int i=0;i<p.length();i++)
    {
        if(p[i]=='(')
            s.push(i);
        else if(p[i]==')'&&!s.empty())
            s.pop();
    }
    if(!s.empty())
        return false;
    else
        return true;
}