#include <string>
using namespace std;
int board[11][11];
//7->8 으로 갈때
bool ok(int y, int x) {
    return (y >= 0 && y < 11 && x >= 0 && x < 11) == true ? true : false;
}

int solution(string dirs) {
    int answer = 0;
    //시작점
    board[5][5] = true;
    int now_y = 5;
    int now_x = 5;
    for (int i = 0; i < dirs.size(); i++) {
        if (dirs[i] == 'U') {
            if (ok(now_y - 1, now_x)) {
                if (board[now_y - 1][now_x] < 2 || board[now_y][now_x] < 2) {
                    answer++;
                }
                now_y -= 1;
                board[now_y][now_x] += 1;
            }
        }
        else if (dirs[i] == 'D') {
            if (ok(now_y + 1, now_x)) {
                if (board[now_y + 1][now_x] < 2 || board[now_y][now_x] < 2)
                    answer++;
                now_y += 1;
                board[now_y][now_x] += 1;
            }
        }
        else if (dirs[i] == 'R') {
            if (ok(now_y, now_x + 1)) {
                if (board[now_y][now_x + 1] < 2 || board[now_y][now_x] < 2)
                    answer++;
                now_x += 1;
                board[now_y][now_x] += 1;
            }
        }
        else if (dirs[i] == 'L') {
            if (ok(now_y, now_x - 1)) {
                if (board[now_y][now_x - 1] < 2 || board[now_y][now_x] < 2)
                    answer++;
                now_x -= 1;
                board[now_y][now_x] += 1;
            }
        }
    }
    return answer;
}
