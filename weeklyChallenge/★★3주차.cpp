//fail...
//왜냐하면 rotate를 구현하는데 아이디어를 ... 못떠올림.
#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <algorithm>
//https://giiro.tistory.com/entry/%ED%94%84%EB%A1%9C%EA%B7%B8%EB%9E%98%EB%A8%B8%EC%8A%A4-%EC%9C%84%ED%81%B4%EB%A6%AC-%EC%B1%8C%EB%A6%B0%EC%A7%80-3%EC%A3%BC%EC%B0%A8-%ED%8D%BC%EC%A6%90-%EC%A1%B0%EA%B0%81-%EC%B1%84%EC%9A%B0%EA%B8%B0
using namespace std;
const int dx[4] = { 1, 0, -1, 0 };
const int dy[4] = { 0, 1, 0, -1 };
int board_height, board_row;
int game_board[51][51];
int table[51][51];
bool visit_board[51][51];
bool visit_table[51][51];
bool usedPuzzle[2501];
int blockNum, emptyNum;
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
    return (y >= 0 && y < board_height&& x >= 0 && x < board_row&& game_board[y][x] == 0) ? true : false;
}
//table용
bool ok2(int y, int x) {
    return (y >= 0 && y < board_height&& x >= 0 && x < board_row&& table[y][x] == 1) ? true : false;
}

//game_board에서 빈칸의 상대 좌표들을 저장하는 '임시'벡터
vector<pair<int, int>> empty_pos_of_blocks;
//table에서 block들의 상대 좌표들을 저장하는 '임시'벡터
vector<pair<int, int>> pos_of_blocks;

map<int, vector<pair<int, int>>> blanks_gameBoard;
map<int, vector<pair<int, int>>> blocks_table;

void print_blanks_gameBoard() {
    for (auto it : blanks_gameBoard) {
        cout << "emptyNum is : " << it.first << endl;
        for (int i = 0; i < it.second.size(); i++)
            cout << it.second[i].first << ',' << it.second[i].second << ' ';
        cout << endl;
    }
}
void print_blocks_gameBoard() {
    for (auto it : blocks_table) {
        cout << "emptyNum is : " << it.first << endl;
        for (int i = 0; i < it.second.size(); i++)
            cout << it.second[i].first << ',' << it.second[i].second << ' ';
        cout << endl;
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

void findEmptyPlaces_Board() {
    for (int i = 0; i < board_height; i++) {
        for (int j = 0; j < board_row; j++) {
            if (ok(i, j) && visit_board[i][j] == false) {
                dfs_board(i, j);
                int emptySize = empty_pos_of_blocks.size();
                int minY = 123, minX = 123;
                for (int k = 0; k < empty_pos_of_blocks.size(); k++) {
                    minY = min(minY, empty_pos_of_blocks[k].first);
                    minX = min(minX, empty_pos_of_blocks[k].second);
                }
                for (int k = 0; k < empty_pos_of_blocks.size(); k++) {
                    empty_pos_of_blocks[k].first -= minY;
                    empty_pos_of_blocks[k].second -= minX;
                }
                blanks_gameBoard.insert(make_pair(emptyNum++, empty_pos_of_blocks));

                empty_pos_of_blocks.clear();
            }
        }
    }
}
void findBlocks_Table() {
    for (int i = 0; i < board_height; i++) {
        for (int j = 0; j < board_row; j++) {
            if (ok2(i, j) && visit_table[i][j] == false) {
                dfs_table(i, j);
                int blockSize = pos_of_blocks.size();
                int minY = 123, minX = 123;
                for (int k = 0; k < pos_of_blocks.size(); k++) {
                    minY = min(minY, pos_of_blocks[k].first);
                    minX = min(minX, pos_of_blocks[k].second);
                }
                for (int k = 0; k < pos_of_blocks.size(); k++) {
                    pos_of_blocks[k].first -= minY;
                    pos_of_blocks[k].second -= minX;
                }

                blocks_table.insert(make_pair(blockNum++, pos_of_blocks));

                pos_of_blocks.clear();
            }
        }
    }
}

void rotate90(vector<pair<int, int>>& blockData) {
    int offsetX = 123, offsetY = 123;
    for (auto& p : blockData) {
        swap(p.first, p.second); p.second *= -1;
        offsetX = min(offsetX, p.first);
        offsetY = min(offsetY, p.second);
    }
    for (auto& p : blockData) {
        p.first -= offsetX;
        p.second -= offsetY;
    }
}
bool canMatch(int i, int j) {
    if (blanks_gameBoard[i].size() != blocks_table[j].size()) return 0;
    int emptyCount = blanks_gameBoard[i].size();
    vector <pair<int, int>> targetPuzzleSet = blocks_table[j];
    for (int rt = 0; rt < 4; rt++) {
        rotate90(targetPuzzleSet);
        int matchCount = 0;
        for (auto& p : blanks_gameBoard[i]) {
            for (auto& p2 : targetPuzzleSet) {
                if (p.first == p2.first && p.second == p2.second) {
                    matchCount++;
                    break;
                }
            }

        }
        if (matchCount == emptyCount) return 1;
    }
    return 0;
}
int solution(vector<vector<int>> g, vector<vector<int>> t) {
    int answer = 0;
    init(g, t);
    findEmptyPlaces_Board();
    findBlocks_Table();



    for (int i = 0; i < blanks_gameBoard.size(); i++) {
        for (int j = 0; j < blocks_table.size(); j++) {
            if (usedPuzzle[j]) continue;
            if (canMatch(i, j)) {
                usedPuzzle[j] = 1;
                answer += blocks_table[j].size();
                break;
            }
        }
    }


    
    return answer;
}
