//fail
//실패 이유: 
//1. board의 표현 방법을 좀 더 단순하게 생각하지 못했음. 
//Point* matrix[100][100]으로 잡았었고, Point에는 각 좌표의 좌, 우, 위, 아래 별로 (보 또는 기둥)이 들어있는지를 표현. 
//근데 그럴 필요가 없이 board[y][x][paper or column] = y, x 좌표에 paper or column이 설치되어 있는지?로 표시하면 훨씬 간단해짐.


//2. 구조물의 삭제 조건을 단순화하지 못하였음.
//아래 코드에서는 일단 삭제를 한 뒤에, 영향력을 받는 곳만 검사. 영향력을 받는 곳만 검사하는 부분에 대해 조건이 맞는지만 보면 됨. 이는, 기존에 짰던 설치 조건 코드를 다시 이용할 수 있단 얘기.
//그러나 원래 코드에서는 빡구현을 하려고 했으므로, 머리도 안돌아갈뿐더러 조건도 틀렸었음.

//3. 구조물을 찾는 코드
//나는 BFS로 했으나, 사실 보드의 크기가 그리 크지 않기 때문에 전체 배열 탐색을 시도해도 이상이 없었음. board[y][x][st]가 true인 곳만 뽑아서 보면 됨.

//레벨이 높아질 수록 설계가 중요하다는 것을 느끼게 됨. 

#include <string>
#include <vector>
#include <algorithm>
using namespace std;

bool board[101][101][2];//board[y][x][0] = 기둥, board[y][x][1] = 보
int num = 0;
bool isColumnOk(int x, int y) {//기둥의 설치 조건
    bool cond1 = y == 0; //바닥에 있거나
    bool cond2 = board[x][y][1] || board[x - 1][y][1];//보의 한쪽 끝 부분에 있거나
    bool cond3 = board[x][y - 1][0];//다른 기둥 위에 있거나
    return cond1 || cond2 || cond3;
}

bool isPaperOk(int x, int y) {
    bool cond1 = (board[x][y - 1][0] || board[x + 1][y - 1][0]);//한쪽 끝 부분이 기둥 위에 있거나
    bool cond2 = (board[x - 1][y][1] && board[x + 1][y][1]);//양쪽 끝 부분이 다른 보와 동시에 연결
    return cond1 || cond2;
}

bool compare(vector<int> a, vector<int> b) {
    if (a[0] == b[0]) {
        if (a[1] == b[1])
            return a[2] < b[2];
        return a[1] < b[1];
    }
    return a[0] < b[0];
}


vector<vector<int>> solution(int n, vector<vector<int>> build_frame) {
    vector<vector<int>> answer;
    num = n;
    for (int i = 0; i < build_frame.size(); i++) {
        int x = build_frame[i][0];
        int y = build_frame[i][1];
        if (build_frame[i][3] == 0) {
            if (build_frame[i][2] == 0) {//기둥 삭제
                board[x][y][0] = false;
                if (board[x][y + 1][0] && !isColumnOk(x, y + 1)) {//현재 윗기둥이 존재하는데, 그게 모순일 때
                    board[x][y][0] = true;
                    continue;
                }
                if (board[x][y + 1][1] && !isPaperOk(x, y + 1)) {//현재 기둥의 윗부분을 왼쪽으로 하는 보가 존재하는데, 그게 모순일 때
                    board[x][y][0] = true;
                    continue;
                }
                if (board[x - 1][y + 1][1] && !isPaperOk(x - 1, y + 1)) {//현재 기둥의 윗부분을 오른쪽으로 하는 보가 존재하는데, 그게 모순일 때
                    board[x][y][0] = true;
                    continue;
                }

            }
            else {//보 삭제
                board[x][y][1] = false;
                if (board[x][y][0] && !isColumnOk(x, y)) {//보의 왼쪽 위 기둥이 있는데 그게 모순일 때
                    board[x][y][1] = true;
                    continue;
                }
                if (board[x + 1][y][0] && !isColumnOk(x + 1, y)) {//보의 오른쪽 위 기둥이 있는데 그게 모순일 때
                    board[x][y][1] = true;
                    continue;
                }
                if (board[x - 1][y][1] && !isPaperOk(x - 1, y)) {//보의 왼쪽 보 존재가 모순일 때
                    board[x][y][1] = true;
                    continue;
                }
                if (board[x + 1][y][1] && !isPaperOk(x + 1, y)) {//보의 오른쪽 보 존재가 모순일 때
                    board[x][y][1] = true;
                    continue;
                }
            }
        }
        else {
            if (build_frame[i][2] == 0) {//기둥 설치
                board[x][y][0] = true;
                if (!isColumnOk(x, y)) {
                    board[x][y][0] = false;
                    continue;
                }
            }
            else {//보 설치
                board[x][y][1] = true;
                if (!isPaperOk(x, y)) {
                    board[x][y][1] = false;
                    continue;
                }
            }
        }
    }
    vector<int> temp;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            for (int k = 0; k < 2; k++) {
                if (board[i][j][k] == true) {
                    temp = { i, j, k };
                    answer.push_back(temp);
                }
            }
        }
    }
    sort(answer.begin(), answer.end(), compare);

    return answer;
}
int main() {
    solution(5, { {1, 0, 0, 1}, {1, 1, 1, 1}, {2, 1, 0, 1}, {2, 2, 1, 1}, {5, 0, 0, 1}, {5, 1, 0, 1}, {4, 2, 1, 1}, {3, 2, 1, 1} });
}
