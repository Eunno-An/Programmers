//크루스칼 알고리즘 을 통한 최소 스패닝 트리 
//그리디 하게 하면 됨. 쉬움.
//간선들을 코스트로 오름차순하고,
//유니온 파인드를 통해 간선을 연결할 때 마다 사이클이 있는지 확인함.
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
//최소 스패닝 트리 만들기.
int parent[101];
bool chk;
int find(int u){
    if(u == parent[u])
        return u;
    return parent[u] = find(parent[u]);
}
void merge(int u, int v){
    chk = false;
    u = find(u);
    v = find(v);
    if(u == v)
        return;
    parent[u] = v;
    chk = true;
}
class Edge{
    public:
    int node1, node2;
    int cost;
    Edge(int node1, int node2, int cost){
        this->node1 = node1;
        this->node2 = node2;
        this->cost = cost;
    }
};
bool compare(Edge* a, Edge* b){
    return a->cost < b->cost;
}
int solution(int n, vector<vector<int>> costs) {
    int answer = 0;
    for(int i=1; i<=n; i++)
        parent[i] = i;
    vector<Edge*> edges;
    for(int i=0; i<costs.size(); i++){
        Edge* newEdge = new Edge(costs[i][0], costs[i][1], costs[i][2]);
        edges.push_back(newEdge);
    }
    sort(edges.begin(), edges.end(), compare);
    
    for(int i=0; i<costs.size(); i++){
        merge(edges[i]->node1, edges[i]->node2);
        if(chk)
            answer += edges[i]->cost;
    }
    return answer;
}
