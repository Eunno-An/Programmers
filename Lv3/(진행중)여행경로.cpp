#include <string>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;
vector<vector<int>> global_adj_list;
vector<vector<int>> all_path;
/*
ICN
|   \
SFO ㅡ ATL

*/

void dfs(int here, int use_ticket, int ticket_num, vector<int> path) {
    if (use_ticket == ticket_num ) {
        all_path.push_back(path);
        return;
    }

    for (int there = 0; there < global_adj_list[here].size(); there++) {
        int next = global_adj_list[here][there];
        path.push_back(next);
        dfs(next, use_ticket + 1, ticket_num, path);
        path.pop_back();
    }
    return;
}
vector<string> solution(vector<vector<string>> tickets) {
    vector<string> answer;

    map<string, int> idx_airports;
    map<int, string> str_airports;
    int ticket_num = tickets.size();
    int idx = 0;
    for (int i = 0; i < tickets.size(); i++) {
        string start = tickets[i][0];
        string end = tickets[i][1];
        if (idx_airports.find(start) == idx_airports.end()) {
            idx_airports.insert(make_pair(start, idx));
            str_airports.insert(make_pair(idx, start));
            idx++;
        }
        if (idx_airports.find(end) == idx_airports.end()) {
            idx_airports.insert(make_pair(end, idx));
            str_airports.insert(make_pair(idx, end));
            idx++;
        }
    }

    int num_airport = idx_airports.size();

    //인접 리스트 생성
    vector<vector<int>> adj_list(num_airport, vector<int>());

    for (int i = 0; i < tickets.size(); i++) {
        string start = tickets[i][0];
        string end = tickets[i][1];
        int idx_start = idx_airports[start];
        int idx_end = idx_airports[end];
        adj_list[idx_start].push_back(idx_end);
    }

    global_adj_list = adj_list;
    vector<int> path;
    path.push_back(0);
    dfs(idx_airports["ICN"], 0, ticket_num, path);

    vector<vector<string>> all_path_str;
    for (int i = 0; i < all_path.size(); i++) {
        vector<int> path_int = all_path[i];
        vector<string> path_str;
        for (int j = 0; j < path_int.size(); j++)
            path_str.push_back(str_airports[path_int[j]]);
        vector<string> temp = path_str;
        sort(temp.begin(), temp.end());
        temp.erase(unique(temp.begin(), temp.end()), temp.end());
        if (temp.size() == num_airport)
            all_path_str.push_back(path_str);
    }
    sort(all_path_str.begin(), all_path_str.end());
    answer = all_path_str[0];
    return answer;
}
int main() {
//    solution({ {"ICN", "JFK"}, {"HND", "IAD"}, {"JFK", "HND"} });
    solution({ {"ICN", "SFO"}, {"ICN", "ATL"}, {"SFO", "ATL"}, {"ATL", "ICN"}, {"ATL","SFO"} });
}
