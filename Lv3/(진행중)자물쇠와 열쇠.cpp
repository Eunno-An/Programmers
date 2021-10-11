#include <string>
#include <vector>
#include <set>
#include <iostream>
using namespace std;

//Lock에서 H들을 포함할 수 있는 가장 적은 직사각형을 만들어라
//10/11: 자물쇠 전체가 돌기일 경우 날 수 있는 segmentation 오류 발견 -> 34점에서 65점으로 정확도 향상.
vector<vector<int>> getMinSquare(vector<vector<int>> lock) {
    vector<vector<int>> ret;
    int minY = 21, minX = 21;
    int maxY = -1, maxX = -1;
    for (int i = 0; i < lock.size(); i++) {
        for (int j = 0; j < lock[i].size(); j++) {
            if (lock[i][j] == 0) {//홈
                if (minY > i)
                    minY = i;
                if (minX > j)
                    minX = j;
                if (maxY < i)
                    maxY = i;
                if (maxX < j)
                    maxX = j;
            }
        }
    }
    ret.resize(maxY - minY + 1);
    for (int i = minY; i <= maxY; i++)
        for (int j = minX; j <= maxX; j++)
            ret[i - minY].push_back(lock[i][j]);

    return ret;
}
vector<vector<int>> rotate_90(vector<vector<int>> square) {
    int ySize = square.size(), xSize = square[0].size();
    vector<vector<int>> ret;
    ret.resize(xSize);
    for (int i = 0; i < ret.size(); i++)
        ret[i].resize(ySize);
    int newX_idx = 0;
    for (int i = ySize - 1; i >= 0; i--) {
        vector<int> line = square[i];
        for (int j = 0; j < xSize; j++)
            ret[j][newX_idx] = line[j];
        newX_idx++;
    }
    return ret;
}
void FlipKey(vector<vector<int>>& key) {
    for (int i = 0; i < key.size(); i++)
        for (int j = 0; j < key[i].size(); j++)
            key[i][j] = !key[i][j];
}
bool checkSquare(vector<vector<int>> square, vector<vector<int>> key, int y, int x, int square_y, int square_x) {
    for (int i = 0; i < square_y; i++)
        for (int j = 0; j < square_x; j++) {
            if (square[i][j] != key[i + y][j + x])
                return false;
        }
    return true;
}
bool is_all_one(vector<vector<int>> lock) {
    for (int i = 0; i < lock.size(); i++)
        for (int j = 0; j < lock[i].size(); j++)
            if (lock[i][j])
                return false;
    return true;
}
bool is_key_available(set<vector<vector<int>>> squares, vector<vector<int>> key) {
    for (auto it : squares) {
        vector<vector<int>> square = it;
        int square_y = square.size();
        int square_x = square[0].size();
        if (square_y > key.size() || square_x > key[0].size())
            continue;
        for (int i = 0; i + square_y - 1 < key.size(); i++)
            for (int j = 0; j + square_x - 1 < key[i].size(); j++) {
                bool check = checkSquare(square, key, i, j, square_y, square_x);
                if (check)
                    return true;
            }
    }
    return false;
}
bool solution(vector<vector<int>> key, vector<vector<int>> lock) {
    FlipKey(key);//편의를 위해 key의 모든 요소들을 flip시킨다.
    bool answer = true;
    set<vector<vector<int>>> rotates;
    vector<vector<int>> square ;
    if (is_all_one(lock)) //자물쇠 전체가 돌기인 경우
        square = lock;
    else
        square = getMinSquare(lock);
    rotates.insert(square);
    for (int i = 0; i < 3; i++)
        rotates.insert(rotate_90(square));

    return answer = is_key_available(rotates, key);

}
int main() {
    cout << solution({ { 1, 1 }, { 1, 1 } }, { {0, 0}, {0, 0 } }) << endl;
    cout << solution({ { 1, 1, 0, 1}, { 0, 1, 1, 0 }, { 1, 0, 1, 1 }, {0, 1, 1, 1 } }, { {1, 0, 1, 0, 1}, {0, 1, 0 , 0, 1}, {1, 0, 1, 1, 0}, {0, 0, 0, 1, 1}, {0, 1, 0 , 0, 1} }) << endl;
}
