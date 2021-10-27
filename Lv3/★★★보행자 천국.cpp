//fail
//경주로 건설 문제와 매우 유사. 같은 문제라도 봐도 무방
//BFS + DP
//ISSUE 참고하기.
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

const int MOD = 20170805;
const int dy[2] = {0, 1};
const int dx[2] = {1, 0};
int cache[501][501][2];
bool visit[501][501][2];
// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
class Car{
    public:
    int y, x, dir;
    Car(int y, int x, int dir){
        this->y = y;
        this->x = x;
        this->dir = dir;
    }
};
bool ok(int y, int x, int m, int n){
    return (y >=0 && y < m && x >= 0 && x < n) ? true : false;
}
int solution(int m, int n, vector<vector<int>> city_map) {
    int answer = 0;
    memset(cache, 0, sizeof(cache));   
    memset(visit, false, sizeof(visit));
    cache[0][0][0] = 1;
    cache[0][0][1] = 1;
    visit[0][0][0] = true;
    visit[0][0][1] = true;
    queue<Car*> move;
    Car* car = new Car(0, 0, 0);
    
    move.push(car);
    
    while(!move.empty()){
        Car* tempCar = move.front(); move.pop();
        
        for(int i=0; i<2; i++){
            int nextY = tempCar->y + dy[i];
            int nextX = tempCar->x + dx[i];
            if(nextY >= m || nextX >= n)
                continue;
            if(city_map[nextY][nextX] == 1)
                continue;
            if(city_map[tempCar->y][tempCar->x] == 2){
                int beforeDir = tempCar->dir;
                if(beforeDir == i){
                    if(!visit[nextY][nextX][i]){
                        Car* newCar = new Car(nextY, nextX, i);
                        move.push(newCar);
                        visit[nextY][nextX][i] = true;
                    }
                    cache[nextY][nextX][i] = (cache[nextY][nextX][i] % MOD + cache[tempCar->y][tempCar->x][i] % MOD) % MOD;
                }
            }
            else{
                    if(!visit[nextY][nextX][i]){
                        Car* newCar = new Car(nextY, nextX, i);
                         move.push(newCar);
                        visit[nextY][nextX][i] = true;
                    }
                    cache[nextY][nextX][i] = (cache[nextY][nextX][i] % MOD + cache[tempCar->y][tempCar->x][tempCar->dir] % MOD) %MOD;
                        
            }
        }
    }
    return answer = (cache[m-1][n-1][0] % MOD + cache[m-1][n-1][1] % MOD) % MOD;
}
