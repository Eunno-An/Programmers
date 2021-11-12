#include <string>
#include <vector>
#include <queue>
#include <cmath>
#include <cstring>
using namespace std;
bool visit[300001];
long long weights[300001];
//모든 점들의 가중치를 0으로 만드는 최소 행동의 개수
class Node {
public:
    int nodeNum;
    long long weight;
    Node(int n, long long w) {
        nodeNum = n;
        weight = w;
    }
};
class Edge {
public:
    Node* node1;
    Node* node2;
    Edge(Node* n1, Node* n2) {
        node1 = n1;
        node2 = n2;
    }
};
int function(Node* node1, Node* node2) {
    int num_node1 = node1->nodeNum;
    int num_node2 = node2->nodeNum;
    long long w_node1 = node1->weight;
    long long w_node2 = node2->weight;

    if (w_node1 == 0)
        return 0;

    weights[num_node1] = 0;
    weights[num_node2] += w_node1;
    node1->weight = 0;
    node2->weight = weights[num_node2];
    return w_node1;
}
long long solution(vector<int> a, vector<vector<int>> edges) {
    long long answer = 0;

    vector<vector<Node*>> adj_list(a.size(), vector<Node*>());

    memset(visit, false, sizeof(visit));
    memset(weights, 0, sizeof(weights));
    for (int i = 0; i < a.size(); i++)
        weights[i] = a[i];
    for (int i = 0; i < edges.size(); i++) {
        Node* node1 = new Node(edges[i][0], a[edges[i][0]]);
        Node* node2 = new Node(edges[i][1], a[edges[i][1]]);
        adj_list[node1->nodeNum].push_back(node2);
        adj_list[node2->nodeNum].push_back(node1);
    }
    queue<Node*> waits;
    for (int i = 0; i < adj_list.size(); i++)
        if (adj_list[i].size() == 1) {//양 방향 그래프이므로, 리프노드의 인접한 노드 개수는 1일 수밖에 없음.
            Node* leafNode = new Node(i, a[i]);
            waits.push(leafNode);

        }

    while (!waits.empty()) {
        Node* here = waits.front(); waits.pop();

        int here_num = here->nodeNum;
        long long here_weight = here->weight;
        visit[here_num] = true;
        for (int i = 0; i < adj_list[here_num].size(); i++) {
            Node* next = adj_list[here_num][i];
            if (visit[next->nodeNum] == true)
                continue;

            answer += abs(function(here, next));

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
