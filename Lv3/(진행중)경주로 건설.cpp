#include <string>
#include <vector>
#include <cstring>
using namespace std;
const int dy[4] = { 0, 1, 0, -1 };
const int dx[4] = { 1, 0, -1, 0 };
int dp[26][26][4];
bool ok(int y, int x, int n) {
    return (y >= 0 && y < n&& x >= 0 && x < n) ? true : false;
}
int dfs(vector<vector<int>> board, vector<vector<bool>> visit, pair<int, int> goal, pair<int, int> now, int cost, int direction) {
    if (goal == now)
        return cost;
    visit[now.first][now.second] = true;
    int& ret = dp[now.first][now.second][direction];
    if (ret != 987654321)
        if (cost >= ret)
            return ret;
    for (int i = 0; i < 4; i++) {
        pair<int, int> next;
        next.first = now.first + dy[i];
        next.second = now.second + dx[i];
        if (ok(next.first, next.second, board.size()) && board[next.first][next.second] != 1 && visit[next.first][next.second] != true) {
            if (direction != i)
                ret = min(ret, dfs(board, visit, goal, next, cost + 6, i));
            else
                ret = min(ret, dfs(board, visit, goal, next, cost + 1, direction));

        }
    }
    visit[now.first][now.second] = false;
    return ret;
}
int solution(vector<vector<int>> board) {
    int answer = 987654321;
    for (int i = 0; i < 26; i++)
        for (int j = 0; j < 26; j++)
            for (int k = 0; k < 4; k++)
                dp[i][j][k] = 987654321;
    vector<vector<bool>> visit(board.size());
    for (int i = 0; i < visit.size(); i++)
        visit[i].resize(board.size(), false);
    pair<int, int> goal;
    goal.first = board.size() - 1;
    goal.second = board.size() - 1;
    pair<int, int> now;
    now.first = 0;
    now.second = 0;
    
    for(int i=0; i<2; i++){
        int ret = dfs(board, visit, goal, now, 0, i);
        answer = min(answer, ret);
    }
    
    return answer * 100;
}
int main() {
    solution({ {0,0,0,0,0,0,0,1}, {0,0,0,0,0,0,0,0}, {0,0,0,0,0,1,0,0}, {0,0,0,0,1,0,0,0}, {0,0,0,1,0,0,0,1}, {0,0,1,0,0,0,1,0}, {0,1,0,0,0,1,0,0}, {1,0,0,0,0,0,0,0} });
}
