//fail
//생각보다 간단한 문젠데.. 배보다 배꼽이 더 크게 풀었네...
//풀다가 안되면 원초적인 방법. 쉬운 방법 부터 생각해보자.
#include <string>
#include <vector>
#include <cstring>
#include <iostream>
using namespace std;
int cnt;
void printMatrix(int matrix[70][70], int lockSize) {
    for (int i = 20; i < 20 + lockSize; i++) {
        for (int j = 20; j < 20 + lockSize; j++)
            cout << matrix[i][j];
        cout << '\n';
    }
}
bool canUnlock(int matrix[70][70], vector<vector<int>> lock) {
    //printMatrix(matrix, lock.size());
    for (int i = 20; i < 20 + lock.size(); i++)
        for (int j = 20; j < 20 + lock.size(); j++)
            if (matrix[i][j] != 1)
                return false;


    return true;
}

void initMatrix(int matrix[70][70], vector<vector<int>> lock) {
    for (int i = 20; i < 20 + lock.size(); i++)
        for (int j = 20; j < 20 + lock[0].size(); j++)
            matrix[i][j] = lock[i - 20][j - 20];
}
vector<vector<int>> rotateKey(vector<vector<int>> key) {
    int ySize = key.size(), xSize = key.size();
    vector<vector<int>> ret;
    ret.resize(xSize);
    for (int i = 0; i < ret.size(); i++)
        ret[i].resize(ySize);
    int newX_idx = 0;
    for (int i = ySize - 1; i >= 0; i--) {
        vector<int> line = key[i];
        for (int j = 0; j < xSize; j++)
            ret[j][newX_idx] = line[j];
        newX_idx++;
    }
    return ret;
}

bool solution(vector<vector<int>> key, vector<vector<int>> lock) {
    bool answer = false;
    int matrix[70][70];
    memset(matrix, 0, sizeof(matrix));
    initMatrix(matrix, lock);
    int count = 3;
    for(int rotate_count=0; rotate_count < 4; rotate_count++){
        for (int i = 0; i < 20 + lock.size(); i++) {
            for (int j = 0; j < 20 + lock.size(); j++) {
                for (int k = i; k < i + key.size(); k++)
                    for (int l = j; l < j + key.size(); l++)
                        matrix[k][l] += key[k - i][l - j];
                if (canUnlock(matrix, lock))
                    return answer=true;
                initMatrix(matrix, lock);
            }
        }
        key = rotateKey(key);
    }


    return answer;
}
int main() {
    solution({ {0, 0, 0}, {1, 0, 0}, {0, 1, 1} }, { {1, 1, 1}, {1,1,0}, {1, 0, 1} });
}
