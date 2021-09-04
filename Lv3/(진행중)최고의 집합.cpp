#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

//자연수 n 개로 이루어진 중복 집합
//1. 각 원소의 합이 S. 즉 e1 + e2 + ... + en = S
//2. M이 최대인 것. e1 * e2 * ... * en = M.
//solve(int S, vector<int> list): 현재 자연수들의 합이 S이고, 그 목록이 list일 떄, 적절하게 자연수를 뽑아서, 원소의 합이 S를 만드는 경우를 리턴.
vector<vector<int>> ans;
void solve(int s, int n, int S, vector<int> list){
    if(S == s && list.size() == n){
        ans.push_back(list);
        return;
    }
    for(int i=1; i<=100000000; i++){
        if(S + i <= s && list.size() < n){
            list.push_back(i);
            solve(s, n, S+i, list);
            list.pop_back();
        }else{
            break;
        }
    }
}
vector<int> solution(int n, int s) {
    vector<int> answer;
    vector<int> error;
    error.push_back(-1);
    solve(s, n, 0, answer);
    
    if(ans.empty())
        return error;
    
    for(int i=0; i<ans.size(); i++)
        sort(ans[i].begin(), ans[i].end());
    sort(ans.begin() , ans.end());
    ans.erase(unique(ans.begin(),  ans.end()), ans.end());
    for(int i=0; i<ans.size(); i++){
        for(int j=0; j<ans[i].size(); j++)
            cout << ans[i][j] << ' ';
        cout << '\n';
    }
    return ans.back();
}
