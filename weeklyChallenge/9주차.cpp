//Level 3의 순위와 상당히 유사한 문제.
//a노드가 속한 집합의 개수를 DFS로 찾는 문제임.
#include <string>
#include <vector>
#include <cstring>
#include <cmath>
using namespace std;

int findSetSize(int nodeNum, int n, bool tree[101][101], bool visit[101]){
    if(visit[nodeNum])
        return 0;
    int ret = 1;
    visit[nodeNum]=true;
    for(int i=1; i<=n; i++){
        if(tree[nodeNum][i] && !visit[i])
            ret += findSetSize(i, n, tree, visit);
    }
    return ret;
}
int solution(int n, vector<vector<int>> wires) {
    int answer = 101;
    bool tree[101][101];
    bool visit[101];
    memset(tree, 0, sizeof(tree));
    memset(visit, false, sizeof(visit));
    for(int i=0;i<wires.size(); i++){
        int node1 = wires[i][0];
        int node2 = wires[i][1];
        tree[node1][node2]=true;
        tree[node2][node1]=true;
    }
    for(int i=0; i<wires.size(); i++){
        int node1 = wires[i][0];
        int node2 = wires[i][1];
        tree[node1][node2]=false;
        tree[node2][node1]=false;
        int setSize1 = findSetSize(node1, n, tree, visit);
        int setSize2 = findSetSize(node2, n, tree, visit);
        int diff_size = abs(setSize1 - setSize2);
        if(answer > diff_size)
            answer = diff_size;
        tree[node1][node2]=true;
        tree[node2][node1]=true;
        memset(visit, false, sizeof(visit));
    }
    return answer;
}
