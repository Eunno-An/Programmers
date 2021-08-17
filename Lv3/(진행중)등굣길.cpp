#include <string>
#include <vector>
#include <iostream>
using namespace std;

int arr[101][101];
bool visit[101][101];
int dy[2] = {0, 1};
int dx[2] = {1, 0};
int h, w;
int answer;
bool ok(int y, int x){
    return (y >=0 && y < h && x >=0 && x < w && arr[y][x] != -1) ? true : false;
}
void init(vector<vector<int>> puddles){
    for(int i=0; i<puddles.size(); i++)
        arr[puddles[i][1]-1][puddles[i][0]-1] = -1;
}
//최단거리는 무조건 (m-1) + (n-1)임.
//solve(y, x, dist) = (0, 0)에서 부터 (y, x)까지 가는데 거리가 dist인지 확인

void dfs(int y, int x, int dist){
    if(visit[y][x])
        return;
    if(y == h-1 && x == w-1){
        if(dist == (h-1 + w-1))
            answer++;
        return;
    }
    visit[y][x] = true;
    for(int i=0; i<2; i++){
        if(ok(y + dy[i], x + dx[i]))
            dfs(y + dy[i], x + dx[i], dist+1);
    }
    visit[y][x] = false;
}
int solution(int m, int n, vector<vector<int>> puddles) {
    
    h = n;
    w = m;
    init(puddles);
    dfs(0, 0, 0);
    return answer;
}
