//fail
//1. 플로이드 와샬로 푸는 방법
//2. 단순 구현 문제(dfs)
//푼 방법은 후자로 하였으며, 아이디어를 참고하였음(https://blog.naver.com/gmlwo308/222180287358)
//쉬운 문제였으나,, 접근 다 해놓고 생각을 좀 더 깊게 하지 못했음.
#include <string>
#include <vector>
#include <cstring>
using namespace std;

int dfs(vector<vector<int>> graph,vector<bool>& visit, int node, int n) {
    if (visit[node] == true)
        return 0;
    int ret = 0;
    visit[node] = true;
    for (int i = 1; i <= n; i++) {
        if (graph[node][i] == 1 && visit[i] == false) {//node랑 i랑 연결되어 있고 방문하지 않은 노드일 때
            ret++;
            ret += dfs(graph, visit, i, n);
        }
    }
    
    return ret;

}
int solution(int n, vector<vector<int>> results) {
    int answer = 0;
    
    vector<vector<int>> graphA, graphB;
    graphA.resize(101);
    graphB.resize(101);
    for (int i = 0; i < 101; i++) {
        for (int j = 0; j < 101; j++) {
            graphA[i].push_back(0);
            graphB[i].push_back(0);
        }
        
    }
    vector<bool> init;
    init.resize(101, false);
    vector<bool> visitA, visitB;
    visitA.resize(101, false);
    visitB.resize(101, false);
    
    for (int i = 0; i < results.size(); i++) {
        int winner = results[i][0];
        int loser = results[i][1];
        graphA[winner][loser] = 1;
        graphB[loser][winner] = 1;
    }
    for (int i = 1; i <= n; i++) {
        int a = dfs(graphA, visitA, i, n);
        int b = dfs(graphB, visitB, i, n);
        if (a + b == n - 1)
            answer++;
        visitA = init;
        visitB = init;
    }
        


    return answer;
}
int main() {
    solution(5, { {4, 3}, {4, 2}, {3, 2}, {1, 2}, {2, 5} });
}
