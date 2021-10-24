#include <vector>
#include <cstring>
#include <iostream>
using namespace std;

const int MOD = 20170805;
const int dy[2] = {1, 0};
const int dx[2] = {0, 1};

int cache[501][501];//(y, x)에서 (m-1, n-1)까지 가는 경로의 수
bool ok(int y, int x, int m, int n){
    if(y >=0 && y < m && x >=0 && x < n) return true;
    return false;
}
int function(vector<vector<int>> city_map, int y, int x, int dir){
    if(city_map.size() -1 == y && city_map[0].size()-1 == x)
        return 1;
    int& ret = cache[y][x];
    if(ret != -1)
        return ret;
    ret = 0;
    for(int i=0; i<2; i++){
        int next_y = y + dy[i];
        int next_x = x + dx[i];
        if(ok(next_y, next_x, city_map.size(), city_map[0].size()) && city_map[next_y][next_x] != 1){
            if(city_map[next_y][next_x] == 2 && dir != i)//2인 경우 보행자 안전을 위해 좌회전이나 우회전이 금지.
                continue;
            else
                ret += function(city_map, next_y, next_x, i) % MOD;
        }
    }
    return ret;
}
// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
int solution(int m, int n, vector<vector<int>> city_map) {
    int answer = 0;
    memset(cache, -1, sizeof(cache));
    answer += function(city_map, 0, 0, 0)% MOD;
    
    return cache[0][0];
}
