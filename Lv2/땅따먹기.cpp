//downStair은 fail, downStair2는 success
#include <iostream>
#include <vector>
#include <string.h>
using namespace std;
int cache[100001][4];
//재귀적 dp. 시간 fail. why??
int downStair(vector<vector<int>> land, int stair, int col, int endRow){
    if(stair == endRow-1)
        return land[stair][col];
    int& ret = cache[stair][col];
    if(ret != -1)   return ret;
    ret = 0;
    for(int i=0; i<4; i++)
        if(i != col)
            ret = max(ret, land[stair][col] + downStair(land, stair+1, i, endRow));
    
    return ret;
    
}

//sliding window & 반복적 DP
int downStair2(vector<vector<int>> land, int stair, int endRow){
    int cache[2][4];
    for(int i=0; i<4; i++){
        cache[0][i] = land[0][i];
        cache[1][i] = land[1][i];
    }
    for(int i=0; i<endRow-2; i++){
        for(int j=0; j<4; j++){
            int max_val = -1;
            for(int k=0; k<4; k++){
                if(k != j){
                    max_val = max(max_val, cache[1][j] + cache[0][k]);
                }
            }
            cache[1][j] = max_val;
        }
        for(int j=0; j<4; j++){
            cache[0][j] = cache[1][j];
            cache[1][j] = land[i+2][j];
        }
    }
    for(int j=0; j<4; j++){
            int max_val = -1;
            for(int k=0; k<4; k++){
                if(k != j){
                    max_val = max(max_val, cache[1][j] + cache[0][k]);
                }
            }
            cache[1][j] = max_val;
    }
    return max(cache[1][0], max(cache[1][1], max(cache[1][2], cache[1][3])));
}
int solution(vector<vector<int> > land)
{
    int answer = 0;
    memset(cache, -1, sizeof(cache));
    
    // [실행] 버튼을 누르면 출력 값을 볼 수 있습니다.
    cout << "Hello Cpp" << endl;
    //downStair(i, land.size()) = 맨 윗행(0번째 행)부터 i번째 행 까지 내려왔을 때, 얻을 수 있는 점수의 최대값
    answer = downStair2(land, 0, land.size());
    return answer;
}
