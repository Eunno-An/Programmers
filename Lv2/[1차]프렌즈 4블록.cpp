#include <string>
#include <vector>

using namespace std;
char Board[31][31];
char tempBoard[31][31];
int y, x;
int answer = 0;
bool remove() {
    bool isRemoved = false;
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            tempBoard[i][j] = Board[i][j];
        }
    }
    for (int i = 0; i < y - 1; i++) {
        for (int j = 0; j < x - 1; j++) {
            char character = Board[i][j];
            if (character != '\0' && character == Board[i][j + 1] && character == Board[i + 1][j] && character == Board[i + 1][j + 1]) {
                isRemoved = true;
                tempBoard[i][j] = '\0';
                tempBoard[i][j + 1] = '\0';
                tempBoard[i + 1][j] = '\0';
                tempBoard[i + 1][j + 1] = '\0';
            }
        }
    }
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            Board[i][j] = tempBoard[i][j];
        }
    }
    return isRemoved;
};
void down() {
    for (int i = 0; i < x; i++) {
        for (int j = y - 2; j >= 0; j--) {
            if (Board[j][i] != '\0' && Board[j + 1][i] == '\0') {
                int row = j;
                //row가 y-1이면 종료
                //또는 Board[row+1][i]에 캐릭터가 있으면 종료
                while (row != y - 1 && Board[row + 1][i] == '\0') {
                    Board[row + 1][i] = Board[row][i];
                    Board[row][i] = '\0';
                    row++;
                }
            }
        }
    }
    return;
};
int solution(int m, int n, vector<string> board) {

    //m=세로, n=가로
    y = m, x = n;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            Board[i][j] = board[i][j];
        }
    }
    while (remove()) {
        down();
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (Board[i][j] == '\0')
                answer++;
        }
    }
    return answer;
}

int main() {
    vector<string> board;
    board = { "CCBDE", "AAADE", "AAABF", "CCBBF" };
    solution(4, 5, board);
}
