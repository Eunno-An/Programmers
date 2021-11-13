//fail
//문제 설명: 모든 노드의 값을 0으로 만드는 것. BFS 방식으로 짬.
//실패 원인: if (num_adj_nodes[next] == 1) waits.push(next);
//BFS방식까지도 이해를 했고, 자료형까지도 이해 했으며, leafNode부터 탐색해야 한다는 것 까지는 알아챘음.

//놓친 부분은, 리프노드처럼 "현재 갈 수 있는 곳이 한 군데만 있는 곳"부터 노드 간 연산을 수행해야 하는데, 이 부분에 대한 생각을 하지 못했음.
//아래 코드에서는 num_adj_nodes[i] = i라는 노드에서 갈 수 있으며, 이전에 방문하지 않은 노드의 개수. 
//라는 변수를 지정하여, num_adj_nodes[i] == 1인 노드만 queue에 넣었음.

#include <string>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;
long long weights[300001];
bool visit[300001];
int num_adj_nodes[300001];
long long solution(vector<int> a, vector<vector<int>> edges) {
    for(int i=0; i<a.size(); i++)
        weights[i] = a[i];
    memset(visit, false, sizeof(visit));
    memset(num_adj_nodes, 0, sizeof(num_adj_nodes));
    long long answer = 0;
    vector<vector<int>> adj_list(a.size(), vector<int>());
    for (int i = 0; i < edges.size(); i++) {
        int node1 = edges[i][0];
        int node2 = edges[i][1];
        adj_list[node1].push_back(node2);
        adj_list[node2].push_back(node1);
    }
    queue<int> waits;//leaf 노드 삽입
    for (int i = 0; i < adj_list.size(); i++) {
        if (adj_list[i].size() == 1)
            waits.push(i);
        num_adj_nodes[i] = adj_list[i].size();
    }


    while (!waits.empty()) {
        int here = waits.front(); waits.pop();
        if (visit[here]) continue;
        visit[here] = true;
        for (int i = 0; i < adj_list[here].size(); i++) {
            int next = adj_list[here][i];
            if (visit[next]) continue;
            long long& w_here = weights[here];
            long long& w_next = weights[next];
            answer += abs(w_here);
            w_next += w_here;
            w_here = 0;
            num_adj_nodes[next]--;
            if (num_adj_nodes[next] == 1)
                waits.push(next);
        }
    }
    for (int i = 0; i < a.size(); i++)
        if (weights[i] != 0)
            return -1;
    return answer;
}
int main() {
    solution({ -5,0,2,1,2 }, { {0, 1}, {3, 4}, {2, 3}, {0, 3} });
}
