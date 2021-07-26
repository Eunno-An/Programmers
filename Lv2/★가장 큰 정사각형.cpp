#include <iostream>
#include<vector>
#include<queue>
using namespace std;
//오른쪽, 오른쪽 아래, 아래
int dy[3] = { 0, 1, 1 };
int dx[3] = { 1, 1, 0 };

int arr[1001][1001];
int row, col;

/*
DP의 느낌으로..풀었던 문제.
              (y2, x2)

(y1, x1)      (y1, x2)

배열 탐색만 1000*1000 잡아먹고, 그럼 1초가 제한이라면, 더 쓸 수 있는건 100밖에 없음.
잘 생각해보면, (y1,x2) 의 정사각형 최대 넓이는
(y1, x2)와 왼쪽, 위, 왼쪽 대각선에 있는 세 수들의 min값이 됨. 왜냐? 붙어있으니까!
그래서 O(3)번을 추가로 탐색하게 되고, 시간을 먹지 않는다.
시간을 생각 안하고 풀어서 많이 헤맸던 문제.
*/
int possible[1001][1001];
bool ok(int y1, int x1, int y2, int x2) {
    return (y1 >= 0 && y1 < row&& x1 >= 0 && x1 < col&& y2 >= 0 && y2 < row&& x2 >= 0 && x2 < col) ? true : false;
}
int solve(int y1, int x1, int y2, int x2) {

    if(ok(y1-1, x1, y2, x2-1) && arr[y1-1][x2-1]){
        
    }
    if (ok(y1 + 1, x1, y2, x2 + 1) && arr[y1 ][x2 ] > 1) {
        
        return solve(y1 + 1, x1, y2, x2 + 1);
    }
    for (int i = x1; i <= x2; i++) {
        if (arr[y1][i] == 0) {
            arr[y1 - 1][x2 - 1] = (y2 - y1) * (y2 - y1);
            return (y2 - y1) * (y2 - y1);
        }
    }
    for (int i = y2; i <= y1; i++) {
        if (arr[i][x2] == 0) {
            arr[y1 - 1][x2 - 1] = (y2 - y1) * (y2 - y1);
            return (y2 - y1) * (y2 - y1);
        }
    }
    arr[y1][x2]= (y1-y2+1)*(y1-y2+1);
    if (ok(y1 + 1, x1, y2, x2 + 1)) {
        return solve(y1 + 1, x1, y2, x2 + 1);
    }
    else {
        return arr[y1][x2];
    }

}
int solution(vector<vector<int>> board)
{
    int answer = 1234;
    row = board.size();
    col = board[0].size();
    // [실행] 버튼을 누르면 출력 값을 볼 수 있습니다.
    cout << "Hello Cpp" << endl;
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            arr[i][j] = board[i][j];
        }
    }
    int max_square = -1;
    for (int i = 1; i < board.size(); i++) {
        for (int j = 1; j < board[i].size(); j++) {
            if (arr[i][j] >= 1) {
                int length = min(min(arr[i-1][j-1], arr[i][j-1]), arr[i-1][j]);
                arr[i][j] = length+1;
                if(max_square < arr[i][j]){
                    max_square = arr[i][j];
                }
            }
        }
    }
    
    for(int i=0; i<board.size(); i++){
        for(int j=0; j<board[i].size(); j++){
            if(max_square < arr[i][j]){
                max_square = arr[i][j];
            }
        }
    }
    if (max_square == -1) {//test_8번: 전체가 0일 때
        answer = 0;
    }
    else {
        answer = max_square * max_square;
    }

    return answer;
}
int main() {
    solution({ {0,1,1,1},{1,1,1,1 },{1,1,1,1} , {0,0,1,0} });
}
