//fail? 반은 맞고 반은 틀렸다고 하자..
//https://blog.naver.com/jms8732/221750426953

//처음엔 무지성 DFS로 짰었는데
//짜다보니 너무 중복도 많음. 그러자고 DP로 풀기에는 너무 갑갑했음.

//위의 링크 아이디어를 참고했음.
//1. 탐색 구간 줄이기: 어떤 기준점 (y, x)를 기준으로 어디만 탐색하면 될까? 
//이게 무슨말이냐면, 대문자를 한 번 발견할 때 마다 전체 맵을 다 볼 필요가 없이, 기준점 아래, 아래왼쪽, 아래오른쪽, 오른쪽만 보면 됨.
//이는 종만북에서 나온 (탐색의 순서를 강제하기)와 같은 맥락임.

//2. 모든 순서를 다 구하지말고, 그리디하게 탐색하기
//보드판에 나온 대문자들이 ABCD라면, A먼저 찾고, A를 찾으면 queue에서 제거.
//A를 못찾으면 queue의 뒤에 삽입.

//만약 B를 못찾으면 또 다시 B를 queue의 뒤에 삽입한다.
//만약 C를 찾으면 C를 queue에서 지운다. 이 때, 나머지 queue에 있는 요소들을 정렬!해야 한다.
//왜냐하면 우리는 사전순으로 가장 빠른 탐색 순서를 찾을 것이기 때문이다.
#include <string>
#include <cstring>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
#include <iostream>
using namespace std;

// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
//https://blog.naver.com/jms8732/221750426953

bool find_right_straight(vector<string>& board, int y, int x) {
    for (int i = x+1; i < board[0].size(); i++) {
        if (board[y][i] == '.')//빈 칸을 만난 경우
            continue;
        if (board[y][i] == board[y][x]) {//같은 타일을 만난 경우
            board[y][i] = '.';
            return true;
        }
        return false;//벽이나, 다른 대문자 타일을 만난 경우
    }
    return false;//그냥 쭉 빈칸인 경우
}
bool find_down_straight(vector<string>& board, int y, int x) {
    for (int i = y + 1; i < board.size(); i++) {
        if (board[i][x] == '.')
            continue;
        if (board[i][x] == board[y][x]) {
            board[i][x] = '.';
            return true;
        }
        return false;
    }
    return false;
}
bool find_down_left(vector<string>& board, int y, int x) {
    for (int i = y + 1; i < board.size(); i++) {
        if (board[i][x] != '.' && board[i][x] != board[y][x])//아얘 첨부터 내려가질 못하는 경우
            return false;
        for (int j = x; j >= 0; j--) {
            if (board[i][j] == '.')
                continue;
            if (board[i][j] == board[y][x]) {
                board[i][j] = '.';
                return true;
            }
            break;
        }
    }
    return false;
}
bool find_down_right(vector<string>& board, int y, int x) {
    for (int i = y + 1; i < board.size(); i++) {
        if (board[i][x] != '.' && board[i][x] != board[y][x])
            return false;
        for (int j = x ; j < board[0].size(); j++) {
            if (board[i][j] == '.')
                continue;
            if (board[i][j] == board[y][x]) {
                board[i][j] = '.';
                return true;
            }
            break;
        }
    }
    return false;
}
bool find_left_down(vector<string>& board, int y, int x) {
    for (int i = x - 1; i >= 0; i--) {
        if (board[y][i] != '.' && board[y][i] != board[y][x])
            return false;
        for (int j = y; j < board.size(); j++) {
            if (board[j][i] == '.')
                continue;
            if (board[j][i] == board[y][x]) {
                board[j][i] = '.';
                return true;
            }
            break;
        }
    }
    return false;
}
bool find_right_down(vector<string>& board, int y, int x) {
    for (int i = x + 1; i < board[0].size(); i++) {
        if (board[y][i] != '.' && board[y][i] != board[y][x])
            return false;
        for (int j = y; j < board.size(); j++) {
            if (board[j][i] == '.')
                continue;
            if (board[j][i] == board[y][x]) {
                board[j][i] = '.';
                return true;
            }
            break;
        }
    }
    return false;
    
}
string gamePlaying(vector<string>& board, deque<char> queue_uppers) {
    string ret = "";
    int count_loop = 0;
    while (!queue_uppers.empty()) {
        char firstUpper = queue_uppers.front(); queue_uppers.pop_front();
        bool check = false;
        bool find = false;
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[i].size(); j++) {
                if (board[i][j] == firstUpper) {
                    check = true;
                    if (find_right_straight(board, i, j) || find_down_straight(board, i, j) || find_down_left(board, i, j) || find_down_right(board, i, j)
                        || find_right_down(board, i, j) || find_left_down(board, i, j)) {
                        find = true;
                        board[i][j] = '.';
                        ret += firstUpper;
                       
                        count_loop = 0;
                        sort(queue_uppers.begin(), queue_uppers.end());
                        
                    }
                    break;
                    
                }
                
            }
            if (check)
                break;
        }
        if(!find) {//못 찾은 경우
            count_loop++;
            queue_uppers.push_back(firstUpper);
        }

        if (count_loop > queue_uppers.size()) {
            return "IMPOSSIBLE";
        }
        
    }
    return ret;
}

string solution(int m, int n, vector<string> board) {
    string answer = "";
    deque<char> queue_uppers;

    int uppers[26];
    memset(uppers, 0, sizeof(uppers));

    for (int i = 0; i < board.size(); i++) 
        for (int j = 0; j < board[i].size(); j++) 
            if (isupper(board[i][j]) && uppers[board[i][j] - 'A'] == 0) 
                uppers[board[i][j] - 'A']++;
            
        
  
    for (int i = 0; i < 26; i++)
        if (uppers[i])
            queue_uppers.push_back('A' + i);
    answer = gamePlaying(board, queue_uppers);
    return answer;
}
int main() {
    cout << solution(3, 3, { "DBA", "C*A", "CDB" }) << endl;
    cout << solution(2, 4, { "NRYN", "ARYA" }) << endl;
    cout << solution(4, 4, { ".ZI.", "M.**", "MZU.", ".IU." }) << endl;
    cout << solution(2, 2, { "AB", "BA" }) << endl;
}
