//뻔한 유형.
//다만 생각해 봐야 할 것은, dfs로 무지성 탐색을 했을 때 나온 경로가 무조건 최소인 점이라는 것을 생각해 주어야 한다.
//이유는 1. 집이 무조건 오른쪽 아래에 존재하고, 2.오른쪽 또는 아래로 밖에 탐색을 못한다.
//즉, 중간에 길이 가로막혀 삥 둘러가는 경우는 존재하지 않는다.
#include <string>
#include <vector>
#include <iostream>
using namespace std;

int arr[101][101];
int cache[101][101];
bool visit[101][101];
int dy[2] = {0, 1};
int dx[2] = {1, 0};
int h, w;
int answer;
bool ok(int y, int x){
    return (y >=0 && y < h && x >=0 && x < w && arr[y][x] != -1) ? true : false;
}
void init(vector<vector<int>> puddles){
    for(int i=0; i<h; i++)
        for(int j=0; j<w; j++)
            cache[i][j] = -1;
    for(int i=0; i<puddles.size(); i++)
        arr[puddles[i][1]-1][puddles[i][0]-1] = -1;
}
//dfs(y, x) = (0,0)에서부터 (h-1, w-1)까지 가는 경우의 수

int dfs(int y, int x){
    if(visit[y][x])
        return 0;
    if(y == h-1 && x == w-1)
        return 1;
    int& ret = cache[y][x];
    if(ret != -1)
        return ret;
    ret = 0;
    visit[y][x] = true;
    for(int i=0; i<2; i++)
        if(ok(y + dy[i], x + dx[i])){
            ret += dfs(y + dy[i], x + dx[i]);
            ret %= 1000000007;
        }
    visit[y][x] = false;
    return ret;
}
int solution(int m, int n, vector<vector<int>> puddles) {
    h = n;
    w = m;
    init(puddles);
    dfs(0, 0);
    answer = cache[0][0];
    return answer;
}
int main(){
    solution(4, 3, {{2, 2}});
}
