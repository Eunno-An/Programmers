#include <string>
#include <vector>
#include <iostream>
#include <queue>
using namespace std;

//어떤 정해진 노드에서부터, 다른 노드들의 최소 경로를 구하는 문제는
//dfs보다 bfs로 구하는게 시간초과가 안난다.
//func은 dfs방식, func2는 bfs방식
//func으로 할 때는 만약 시간초과가 안나려면 min_Route를 사전에 INT_MAX로 초기화해야 한다.

int min_Route[20001];
bool visit[20001];
vector<vector<int>> adj;

void func(int node, int distance) {
    if (visit[node])
        return;
    visit[node] = true;
    if (min_Route[node] > distance ){
        min_Route[node] = distance;
    }
    for (int i = 0; i < adj[node].size(); i++) {
        func(adj[node][i], distance + 1);
    }
    visit[node] = false;
}
void func2(int node){
    queue<int> wait;
    wait.push(node);
    while(!wait.empty()){
        int top_wait = wait.front(); wait.pop();
        visit[top_wait]=true;
        for(int i=0; i<adj[top_wait].size(); i++){
            if(visit[adj[top_wait][i]] == false){
                visit[adj[top_wait][i]] = true;
                min_Route[adj[top_wait][i]]= min_Route[top_wait]+1;
                wait.push(adj[top_wait][i]);
            }
        }
    }
}
int solution(int n, vector<vector<int>> edge) {
    int answer = 0;
    adj.resize(n+1);
    for (int i = 0; i < edge.size(); i++) {
        adj[edge[i][0]].push_back(edge[i][1]);
        adj[edge[i][1]].push_back(edge[i][0]);
    }
    for (int i = 0; i < n + 1; i++)
        min_Route[i] = 1000000000;
    func2(1);
    int max_val = -1;
    for (int i = 1; i <= n; i++) 
        if (max_val < min_Route[i])
            max_val = min_Route[i];
    
    for (int i = 1; i <= n; i++)
        if (max_val == min_Route[i])
            answer++;
    
    return answer;
}
int main() {
    solution(6, { {3, 6},{4, 3},{3, 2},{1, 3},{1, 2},{2, 4}, {5, 2} });
}
