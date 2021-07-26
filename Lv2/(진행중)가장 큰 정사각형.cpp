//효율성 문제 해결중
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
1    1  .   .   (y2, x2)
1    1
.
.
(y1, x1)        (y1, x2)
(y1,x1)부터 (y1, x2)까지 1인지 확인
(y2, x2)부터 (y1-1, x2)까지 1인지 확인
solve(y1, x1, y2, x2, k) -> 현재 사각형의 왼쪽 하단, 오른쪽 상단의 좌표가 주어지고, 길이 k가 주어질 때, 사각형의 최대 넓이
=이걸 좀 더 최적화 시키면?
solve(int y1, int x1) = y1, x1을 오른쪽 아래 꼭짓점 으로 갖는 정사각형의 최대 넓이
=
*/
int possible[1001][1001];
bool ok(int y1, int x1, int y2, int x2) {
    return (y1 >= 0 && y1 < row&& x1 >= 0 && x1 < col&& y2 >= 0 && y2 < row&& x2 >= 0 && x2 < col) ? true : false;
}
int solve(int y1, int x1, int y2, int x2) {

    if (ok(y1 + 1, x1, y2, x2 + 1) && arr[y1 + 1][x2 + 1] > 1) {
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
    if (ok(y1 + 1, x1, y2, x2 + 1)) {
        return solve(y1 + 1, x1, y2, x2 + 1);
    }
    else {
        return arr[y1][x2] = (y1-y2 + 1)*(y1-y2+1);
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
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            if (arr[i][j] >= 1) {
                int area = solve(i, j, i, j);
                if (max_square < area)
                    max_square = area;
            }
        }
    }
    if (max_square == -1) {//test_8번: 전체가 0일 때
        answer = 0;
    }
    else {
        answer = max_square;
    }

    return answer;
}
int main() {
    solution({ {0,1,1,1},{1,1,1,1 },{1,1,1,1} , {0,0,1,0} });
}
