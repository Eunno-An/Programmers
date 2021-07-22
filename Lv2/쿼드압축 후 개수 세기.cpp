#include <string>
#include <vector>

using namespace std;
int arr[1024][1024];
vector<int> answer;
bool check_all_same(int y, int x, int size) {
    int first_num = arr[y][x];
    int zero_count = 0;
    int first_count = 0;
    bool flag = false;
    for (int i = y; i < y + size; i++) {
        for (int j = x; j < x + size; j++) {
            if (first_num != arr[i][j])
                return false;
            if (arr[i][j] == 1)
                first_count++;
            else
                zero_count++;
        }
    }
    answer[first_num] += 1;
    return true;
}
void quadTree(int y, int x, int size) {
    if (check_all_same(y, x, size)) {
        int first_num = arr[y][x];

        for (int i = y; i < y + size; i++) {
            for (int j = x; j < x + size; j++) {
                arr[i][j] = first_num;
            }
        }
        return;
    }
    quadTree(y, x, size / 2);
    quadTree(y + size / 2, x, size / 2);
    quadTree(y, x + size / 2, size / 2);
    quadTree(y + size / 2, x + size / 2, size / 2);
}
vector<int> solution(vector<vector<int>> vec_arr) {
    for (int i = 0; i < vec_arr.size(); i++) {
        for (int j = 0; j < vec_arr.size(); j++) {
            arr[i][j] = vec_arr[i][j];
        }
    }
    answer = { 0, 0 };

    quadTree(0, 0, vec_arr.size());

    return answer;
}
int main() {
    solution({ {1, 1, 0, 0},{1, 0, 0, 0},{1, 0, 0, 1},{1, 1, 1, 1} });
}
