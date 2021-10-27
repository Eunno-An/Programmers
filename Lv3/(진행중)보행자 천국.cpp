#include <vector>
#include <cstring>
using namespace std;

int MOD = 20170805;
int cache[501][501][2];
bool visit[501][501][2];

const int dy[2] = { 1, 0 };
const int dx[2] = { 0, 1 };
vector<vector<int>> global_city_map;
// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
bool ok(vector<vector<int>> city_map, int y, int x) {
    return (y >= 0 && y < city_map.size() && x >= 0 && x < city_map[0].size()) ? true : false;
}
int dfs(int y, int x, int dir) {
    if (y == global_city_map.size() - 1 && x == global_city_map[0].size() - 1)
        return 1;
    int& ret = cache[y][x][dir];
    if (ret != -1)
        return ret % MOD;
    ret = 0;
    visit[y][x][dir] = true;
    for (int i = 0; i < 2; i++) {
        int nextY = y + dy[i];
        int nextX = x + dx[i];
        if (ok(global_city_map, nextY, nextX) && global_city_map[nextY][nextX] != 1 && visit[nextY][nextX][i] == false) {
            if (global_city_map[y][x] == 2) {
                if (dir == i)
                    ret += dfs(nextY, nextX, dir) % MOD;
            }
            else
                ret += dfs(nextY, nextX, i) % MOD;
        }
    }
    visit[y][x][dir] = false;
    return ret % MOD;
}
int solution(int m, int n, vector<vector<int>> city_map) {
    memset(cache, -1, sizeof(cache));
    memset(visit, false, sizeof(visit));
    global_city_map = city_map;
    int answer = 0;
    answer += dfs(0, 0, 0);
    return answer;
}
int main() {
    solution(3, 6, { {0, 0, 0}, {0, 0, 0}, {0, 0, 0 } });
}
