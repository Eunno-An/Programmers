#include <string>
#include <vector>
#include <iostream>
#include <map>
using namespace std;
const int dx[4] = { 1, 0, -1, 0 };
const int dy[4] = { 0, 1, 0, -1 };
int board_height, board_row;
int game_board[51][51];
int table[51][51];
bool visit_board[51][51];
bool visit_table[51][51];
void init(vector<vector<int>> g, vector<vector<int>> t) {
    board_height = g.size();
    board_row = g[0].size();
    for (int i = 0; i < board_height; i++) 
        for (int j = 0; j < board_row; j++) {
            visit_board[i][j] = false;
            visit_table[i][j] = false;
            game_board[i][j] = g[i][j];
            table[i][j] = t[i][j];
        }
    return;
}
void printBoardInfo() {
    for (int i = 0; i < board_height; i++) {
        for (int j = 0; j < board_row; j++)
            cout << game_board[i][j] << ' ';
        cout << '\n';
    }
}
void printTableInfo() {
    for (int i = 0; i < board_height; i++) {
        for (int j = 0; j < board_row; j++)
            cout << table[i][j] << ' ';
        cout << '\n';
    }
}


//0이 빈 칸, 1이 이미 채워진 칸
//1. game_board를 순회하면서, 빈칸을 발견하면
//1-1. 인접한 빈칸을 순회한다. 그러면서 빈칸의 좌표들을 벡터에 넣는다. 그리고 visit 처리 한다.
//1-2. 더 이상 탐색할 수 없다면, 그만 하고, 벡터의 사이즈와 벡터를 저장한다.

//game_board용
bool ok(int y, int x) {
    return (y >= 0 && y < board_height&& x >= 0 && x < board_row && game_board[y][x] == 0) ? true : false;
}
//table용
bool ok2(int y, int x) {
    return (y >= 0 && y < board_height&& x >= 0 && x < board_row&& table[y][x] == 1) ? true : false;
}

//game_board에서 빈칸의 상대 좌표들을 저장하는 '임시'벡터
vector<pair<int, int>> empty_pos_of_blocks;
//table에서 block들의 상대 좌표들을 저장하는 '임시'벡터
vector<pair<int, int>> pos_of_blocks;

map<int, vector<vector<pair<int, int>>>> blanks_gameBoard;
map<int, vector<vector<pair<int, int>>>> blocks_table;

void print_blanks_gameBoard() {
    for (auto it : blanks_gameBoard) {
        cout << "emptySize is : " << it.first << endl;
        for (int i = 0; i < it.second.size(); i++) {
            for (int j = 0; j < it.second[i].size(); j++)
                cout << it.second[i][j].first << ',' << it.second[i][j].second << ' ';
            cout << endl;
        }
    }
}
void dfs_board(int y, int x) {
    if (visit_board[y][x])
        return;
    empty_pos_of_blocks.push_back(make_pair(y, x));
    visit_board[y][x] = true;
    for (int dir = 0; dir < 4; dir++) {
        if (ok(y + dy[dir], x + dx[dir])) {
            dfs_board(y + dy[dir], x + dx[dir]);
        }
    }
    
    return;
}
void dfs_table(int y, int x) {
    if (visit_table[y][x])
        return;
    pos_of_blocks.push_back(make_pair(y, x));
    visit_table[y][x] = true;
    for (int dir = 0; dir < 4; dir++) {
        if (ok2(y + dy[dir], x + dx[dir])) {
            dfs_table(y + dy[dir], x + dx[dir]);
        }
    }

    return;
}
int solution(vector<vector<int>> g, vector<vector<int>> t) {
    int answer = -1;
    init(g, t);
    for (int i = 0; i < board_height; i++) {
        for (int j = 0; j < board_row; j++) {
            if(ok(i, j) && visit_board[i][j] == false){
                dfs_board(i, j);
                int emptySize = empty_pos_of_blocks.size();
                vector<vector<pair<int, int>>> temp;
                if (blanks_gameBoard.find(emptySize) == blanks_gameBoard.end()) {
                    blanks_gameBoard.insert(make_pair(emptySize, temp));
                    blanks_gameBoard[emptySize].push_back(empty_pos_of_blocks);
                }
                else
                    blanks_gameBoard[emptySize].push_back(empty_pos_of_blocks);
                empty_pos_of_blocks.clear();
            }
        }
    }

    for (int i = 0; i < board_height; i++) {
        for (int j = 0; j < board_row; j++) {
            if (ok2(i, j) && visit_table[i][j] == false) {
                dfs_table(i, j);
                int blockSize = pos_of_blocks.size();
                vector<vector<pair<int, int>>> temp;
                if (blocks_table.find(blockSize) == blocks_table.end()) {
                    blocks_table.insert(make_pair(blockSize, temp));
                    blocks_table[blockSize].push_back(pos_of_blocks);
                }
                else
                    blocks_table[blockSize].push_back(pos_of_blocks);
                pos_of_blocks.clear();
            }
        }
    }
    
    return answer;
}
int main() {
    solution({ {0,0,0},{1,1,0},{1,1,1} }, { {1,1,1},{1,0,0},{0,0,0} });
}
