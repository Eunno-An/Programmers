#include <string>
#include <vector>

using namespace std;
int arr[1001][1001];
vector<int> solution(int n) {
    
    vector<int> answer;
    int number = 1;
    int row = 0, col = 0;
    int temp_n = n;
    int temp_row = -1, temp_col = -1;
    while (temp_row != row && temp_col != col && arr[row][col] == 0) {
        temp_row = row, temp_col = col;
        for (; row < n; row++) {
            if (row < 0 || col < 0)
                break;
            if (arr[row][col])
                break;
            arr[row][col] = number++;
        }
            
        row--;
        col++;
        for (; col < n; col++) {
            if (row < 0 || col < 0)
                break;
            if (arr[row][col])
                break;
            arr[row][col] = number++;
        }
        col--;
        row--, col--;
        for (; row > 0; row--, col--) {
            if (row < 0 || col < 0)
                break;
            if (arr[row][col])
                break;
            arr[row][col] = number++;
        }
        row += 2;
        col += 1;
        n -= 1;
    }
    for (int i = 0; i < temp_n; i++) {
        for (int j = 0; j < temp_n; j++) {
            if (arr[i][j] == 0)
                break;
            answer.push_back(arr[i][j]);
        }
    }
    return answer;
}
int main() {
    solution(3);
}
