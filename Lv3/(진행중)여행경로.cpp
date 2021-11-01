#include <string>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
using namespace std;
vector<vector<int>> all_pathes;
void dfs(int here, vector<vector<int>>& adj_list, map<pair<int, int>, int>& useTicket, vector<int> path) {
    if (path.size() == useTicket.size() + 1) {
        all_pathes.push_back(path);
        return;
    }
    for (int there = 0; there < adj_list[here].size(); there++) {
        int next = adj_list[here][there];
        pair<int, int> flight = make_pair(here, next);
        if (useTicket[flight] == 1) {
            path.push_back(next);
            useTicket[flight]--;
            dfs(next, adj_list, useTicket, path);
            useTicket[flight]++;
            path.pop_back();
        }
    }
    return;
}
vector<string> solution(vector<vector<string>> tickets) {
    vector<string> answer;
    //현재 티켓의 사용 횟수
    map<pair<int, int>, int> useTicket;
    //공항의 str값으로 idx값을 얻어올 수 있음.
    map<string, int> str2Idx;
    int idx = 0;
    for (int i = 0; i < tickets.size(); i++) {
        string start = tickets[i][0];
        string end = tickets[i][1];
        if (str2Idx.find(start) == str2Idx.end())
            str2Idx.insert(make_pair(start, idx++));
        if (str2Idx.find(end) == str2Idx.end())
            str2Idx.insert(make_pair(end, idx++));
        useTicket.insert(make_pair(make_pair(str2Idx[start], str2Idx[end]), 1));
    }

    //공항의 idx값으로 str값을 얻어올 수 있음.
    vector<string> Idx2Str(str2Idx.size());
    for (auto it : str2Idx)
        Idx2Str[it.second] = it.first;

    //adj_list 만들기 (메모리 때문에 인접 행렬은안됨..)
    int num_airport = str2Idx.size();
    vector<vector<int>> adj_list(num_airport, vector<int>());
    for (int i = 0; i < tickets.size(); i++) {
        string str_start = tickets[i][0];
        string str_end = tickets[i][1];
        int int_start = str2Idx[str_start];
        int int_end = str2Idx[str_end];
        adj_list[int_start].push_back(int_end);
    }

    vector<int> path;
    path.push_back(str2Idx["ICN"]); // 테스트케이스 4번. 인천이 꼭 0번이라는 보장은 없지.
    dfs(str2Idx["ICN"], adj_list, useTicket, path);

    vector<vector<string>> str_all_pathes;
    for (int i = 0; i < all_pathes.size(); i++) {
        vector<int> temp = all_pathes[i];
        vector<string> str_temp;
        for (int j = 0; j < temp.size(); j++)
            str_temp.push_back(Idx2Str[temp[j]]);
        str_all_pathes.push_back(str_temp);
    }
    sort(str_all_pathes.begin(), str_all_pathes.end());
    return answer = str_all_pathes[0];
}
int main() {
    solution({ {"ICN", "SFO"}, {"ICN", "ATL"}, {"SFO", "ATL"}, {"ATL", "ICN"}, {"ATL","SFO"} });
}
