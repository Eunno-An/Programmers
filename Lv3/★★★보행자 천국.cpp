//fail
//경주로 건설 문제와 매우 유사. 같은 문제라도 봐도 무방
//BFS + DP
//ISSUE 참고하기.

//2021-10-28 코드 리팩토링
#include <vector>
#include <cstring>
#include <queue>
using namespace std;

const int MOD = 20170805;
const int dy[2] = {1, 0};
const int dx[2] = {0, 1};

class Car{
    public:
    int y, x, dir;
    Car(int y, int x, int dir){
        this->y = y;
        this->x = x;
        this->dir = dir;
    }
};
//cache[y][x][dir] =(y, x)까지 이동할 수 있는 경우의 수.(이전에 dir방향으로 온 것임)
int cache[501][501][2];
bool visit[501][501][2];
// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
bool ok(int y, int x, int m, int n){
    return (y >= m || x >= n) ? false : true;
}
int solution(int m, int n, vector<vector<int>> city_map) {
    memset(cache, 0, sizeof(cache));
    memset(visit, false, sizeof(visit));
    int answer = 0;
    cache[0][0][0] = 1;
    cache[0][0][1] = 1;
    visit[0][0][0] = true;
    visit[0][0][1] = true;
    queue<Car*> move;
    Car* start = new Car(0, 0, 0);
    move.push(start);
    
    while(!move.empty()){
        Car* tempCar = move.front(); move.pop();
        int y = tempCar->y;
        int x = tempCar->x;
        int before = tempCar->dir;
           
        for(int direction = 0; direction < 2; direction++){
            int nextY = y + dy[direction];
            int nextX = x + dx[direction];
            if(ok(nextY, nextX, m, n)){
                if(city_map[nextY][nextX] != 1){
                    if(city_map[y][x] == 0){//제한 없이 갈 수 있는 경우
                        if(visit[nextY][nextX][direction] == false){
                            visit[nextY][nextX][direction] = true;
                            Car* newCar = new Car(nextY, nextX, direction);
                            move.push(newCar);
                        }
                        cache[nextY][nextX][direction] += cache[y][x][before] % MOD;
                    }else{//city_map[nextY][nextX] == 2
                        if(before == direction){
                            if(visit[nextY][nextX][direction] == false){
                                visit[nextY][nextX][direction] = true;
                                Car* newCar = new Car(nextY, nextX, direction);
                                move.push(newCar);
                            }
                            cache[nextY][nextX][direction] += cache[y][x][direction] % MOD;
                        }
                    }
                }
            }
        }
    }
    
    return answer = (cache[m-1][n-1][0]%MOD + cache[m-1][n-1][1]%MOD) % MOD;
}
