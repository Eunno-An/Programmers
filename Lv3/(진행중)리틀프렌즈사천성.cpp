//fail
//다음엔 BFS로 짜보자. DFS는 너무 헷갈려... 진짜로
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
//자료형, 자원, 자리

//짝을 맞추는 게임. 짝의 가짓수에는 여러가지가 있으며, 그중 사전순으로 앞서는
//답을 찾는 최적화 문제임->완전탐색

//1. board와 tile이 주어졌을 때, 짝을 찾아주는 함수. 그 위치를 반환한다.
//findPair_pos(vector<string> board, char tile, int y, int x, int directon, int turn)
vector<vector<bool>> visit;
vector<string> result;
int uppers[26];
int numUpper;
//아, 오, 위, 왼
int dy[4] = { 1, 0, -1, 0 };
int dx[4] = { 0, 1, 0, -1 };
void init_visit(vector<string> board) {
    visit.resize(board.size());
    for (int i = 0; i < board.size(); i++)
        visit[i].resize(board[i].size(), false);

}
bool ok(vector<string> board, int y, int x) {
    return (y >= 0 && y < board.size() && x >= 0 && x < board.size()) ? true : false;
}
bool ok2(vector<string> board, char tile, int y, int x) {
    return ((isupper(board[y][x]) && board[y][x] == tile) || board[y][x] == '.') ? true : false;
}
void checkUppers(vector<string> board) {
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            if (isupper(board[i][j]) && uppers[board[i][j] - 'A'] == 0) {
                uppers[board[i][j] - 'A']++;
            }
        }
    }
    for (int i = 0; i < 26; i++)
        if (uppers[i])
            numUpper++;
}
pair<int, int> findPair_pos(vector<string> board, char tile, int y, int x, int direction, int turn) {
    pair<int, int> ret = make_pair(-1, -1);
    if (visit[y][x])
        return ret;
    if (board[y][x] == tile)
        return make_pair(y, x);
    
    
    

    visit[y][x] = true;
    for (int i = 0; i < 4; i++) {
        int _y = y + dy[i];
        int _x = x + dx[i];
        //_y, _x의 범위가 보드 판 안에 있으며, (board[_y][_x]가 대문자이면서 tile과 같거나, 빈칸일 떄) 
        if (ok(board, _y, _x) && ok2(board, tile, _y, _x)) {
            if (direction != i && turn < 1)
                ret = max(ret, findPair_pos(board, tile, _y, _x, i, turn + 1));
            else if (direction == i && turn <= 1)
                ret = max(ret, findPair_pos(board, tile, _y, _x, direction, turn));
        }
    }
    visit[y][x] = false;
    return ret;
}
void function(vector<string> board, string ret) {
    if (ret.size() == numUpper) {
        result.push_back(ret);
        return;
    }
    
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            if (isupper(board[i][j]) ) {
                
                for (int k = 0; k < 4; k++) {
                    if (ok(board, i + dy[k], j + dx[k]) && ok2(board, board[i][j], i+dy[k], j+dx[k])) {
                        pair<int, int> other = findPair_pos(board, board[i][j], i + dy[k], j + dx[k], k, 0);
                        if (other.first != -1) {
                            char opposeTile = board[other.first][other.second];
                            if (other.first == i && other.second == j)
                                continue;
                            board[i][j] = '.';
                            board[other.first][other.second] = '.';
                            function(board, ret + opposeTile);
                            board[i][j] = opposeTile;
                            board[other.first][other.second] = opposeTile;
                            continue;

                        }
                    }

                }


            }
        }
    }
}
string solution(int m, int n, vector<string> board) {
    string answer = "";
    init_visit(board);
    checkUppers(board);
    function(board, "");
    vector<string> result2;
    for (int i = 0; i < result.size(); i++) {
        if (result[i].size() == numUpper)
            result2.push_back(result[i]);
    }
    sort(result2.begin(), result2.end());
    if (result.empty())
        answer = "IMPOSSIBLE";
    else
        answer = result2.front();
    return answer;
}

int main() {
    cout << solution(2, 4, { "NRYN", "ARYA" }) << endl;
    /*
    DBA
    C*A
    CDB
    */
}
