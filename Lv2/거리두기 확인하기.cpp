#include <string>
#include <vector>
#include <cmath>
using namespace std;
int arr[5][5];
int manhattenDistance(int r1, int c1, int r2, int c2) {
    return abs(r1 - r2) + abs(c1 - c2);
}
bool checkPartition(pair<int, int> p1, pair<int, int> p2) {
    if (p1.second == p2.second) {
        pair<int, int> down = p1.first < p2.first ? p2 : p1;
        pair<int, int> up = p1.first > p2.first ? p2 : p1;
        if (arr[down.first - 1][down.second] == -1) {
            return true;
        }
        else
            return false;
    }
    pair<int, int> pp1 = p1.second < p2.second ? p1 : p2;
    pair<int, int> pp2 = p1.second > p2.second ? p1 : p2;
    //pp1이 왼쪽, pp2가 오른쪽
    if (pp1.first == pp2.first) {
        if (arr[pp1.first][pp1.second + 1] == -1)
            return true;
        else
            return false;
    }

    if (pp1.first < pp2.first) {//왼쪽 위, 오른쪽 아래 존재할 경우
        if (arr[pp1.first][pp1.second + 1] == -1 && arr[pp1.first + 1][pp1.second] == -1) {
            return true;
        }
        else {
            return false;
        }
    }
    else {//왼쪽 아래, 오른쪽 위 존재할 경우
        if (arr[pp1.first - 1][pp1.second] == -1 && arr[pp1.first][pp1.second + 1] == -1) {
            return true;
        }
        else {
            return false;
        }
    }
}
vector<int> solution(vector<vector<string>> places) {
    vector<int> answer;

    for (int i = 0; i < 5; i++) {
        bool isOk = true;

        vector<pair<int, int>> vec_P;
        for (int j = 0; j < 5; j++) {
            for (int k = 0; k < 5; k++) {
                if (places[i][j][k] == 'P') {
                    arr[j][k] = 1;
                    vec_P.push_back(make_pair(j, k));
                }
                else if (places[i][j][k] == 'O') {
                    arr[j][k] = 0;
                }
                else {
                    arr[j][k] = -1;
                }
            }
        }

        for (int j = 0; j < vec_P.size(); j++) {
            for (int k = j + 1; k < vec_P.size(); k++) {
                int manDistance = manhattenDistance(vec_P[j].first, vec_P[j].second, vec_P[k].first, vec_P[k].second);
                if (manDistance == 1) {
                    isOk = false;
                    break;
                }
                else if (manDistance == 2) {//맨해튼 거리가 2일 경우, 파티션이 존재하는 지 확인하기.
                    if (!checkPartition(vec_P[j], vec_P[k])) {
                        isOk = false;
                        break;
                    }
                }
            }
            if (!isOk) {
                break;
            }
        }
        answer.push_back(isOk == true ? 1 : 0);


    }
    return answer;
}
int main() {
    vector<vector<string>> s = { {"POOOP", "OXXOX", "OPXPX", "OOXOX", "POXXP"},{"POOPX", "OXPXP", "PXXXO", "OXXXO", "OOOPP"},{"PXOPX", "OXOXP", "OXPOX", "OXXOP", "PXPOX"},{"OOOXX", "XOOOX", "OOOXX", "OXOOX", "OOOOO"},{"PXPXP", "XPXPX", "PXPXP", "XPXPX", "PXPXP"}};
    solution(s);
}
