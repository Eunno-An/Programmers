#include <string>
#include <vector>
#include <iostream>
using namespace std;
//incoming edge의 개수와 out edge의 개수를 저장
vector<int> num_income, num_out;
vector<int> visit;
//유향그래프를 인접 행렬로 표현
int matrix[101][101];
void init(vector<vector<int>> results, int n) {
    num_income.resize(n + 1, 0);
    num_out.resize(n + 1, 0);
    visit.resize(n + 1, 0);
    for (int i = 0; i < results.size(); i++) {
        int winner = results[i][0];
        int loser = results[i][1];
        matrix[winner][loser] = 1;
        num_out[winner]++;
        num_income[loser]++;
    }
    return;
}
//node의 최대 income+out 엣지 개수가 n-1이 아니라면
//-1을 반환.
pair<int, int> findCertainNode(int n) {
    pair<int, int> ret;
    ret.first = -1;//maxEdge_node
    ret.second = -1;//maxEdge;

    int max_count = 0;//순위가 중복되는게 있으면 안됨.
    for (int i = 1; i <= n; i++) {
        if (visit[i])
            continue;
        int num_edge = num_income[i] + num_out[i];
        if (ret.second < num_edge) {
            max_count = 1;
            ret.second = num_edge;
            ret.first = i;
        }
        else if(ret.second == num_edge){
            max_count++;
        }
        else {
            max_count = 0;
        }
    }
    

    return ret.second == n - 1  && max_count <= 1? ret : make_pair(-1, -1);
}
int solution(int n, vector<vector<int>> results) {
    int answer = 0;
    init(results, n);
    pair<int, int> node = findCertainNode(n);
    while (node.first != -1) {
        answer++;
        //2한테 이긴 노드들에게서, 2와의 관계를 지움.
        for (int i = 1; i <= n; i++) {
            if (matrix[i][node.first] == 1)
                matrix[i][node.first] = 0;
        }
        //2가 이긴 노드들에게는 기존의 상하 관계를 지정.
        for (int i = 1; i <= n; i++) {
            if (matrix[node.first][i]) {//i는 2한테 진 노드들
                num_income[i] += num_income[node.first];
                matrix[node.first][i] = 0;
            }
        }
        visit[node.first] = 1;
        num_income[node.first] = 0;
        num_out[node.first] = 0;
        node = findCertainNode(n);
    }

    return answer;
}
int main() {
    cout << solution(5, { {4, 3},{4, 2},{3, 2}, {1, 2}, {2, 5 } }) << endl;
}
