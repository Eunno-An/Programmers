#include <string>
#include <vector>
#include <algorithm>
using namespace std;
vector<vector<int>> adj;
vector<vector<int>> adj2;

int solution(int n, vector<vector<int>> results) {
    int answer = 0;
    adj.resize(n+1);
    adj2.resize(n+1);
    for(int i=0; i<results.size(); i++){
        adj[results[i][0]].push_back(results[i][1]);
        adj[results[i][1]].push_back(results[i][0]);
    }
    
    for(int i=1; i<=n; i++){
        //어떤 x사람이 패한 횟수 = num_lose
        int num_lose = adj2[i].size();
        int num_win = adj[i].size();
        if(num_lose + num_win == n-1)
            answer++;
        
    }
    return answer;
}
