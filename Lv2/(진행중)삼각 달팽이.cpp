#include <string>
#include <vector>

using namespace std;
int arr[500501];
vector<int> solution(int n) {
    vector<int> answer;

    int before_idx = 0;
    arr[0] = 0;
    /*
    인덱스 값(바깥에)
    1   1
    2   2
    4   3
    7   4
    11  5

    인덱스, 값(안에)
    5, 16
    8, 17
    12, 18
    */
    int triangleSize = n * (n + 1) / 2;
    int startIdx = 1;
    int max_num = 0;
    while (n >= 1) {
        //왼쪽 변
        for (int i = startIdx; i < startIdx + n; i++) {
            if (i == startIdx) {
                arr[startIdx] = arr[before_idx] + 1;
                before_idx=startIdx;
                continue;
            }
            if (arr[before_idx + arr[before_idx]] != 0) {
                break;
            }
            arr[before_idx + arr[before_idx]] = i;
            before_idx = before_idx + arr[before_idx];
        }
        //밑 변
        int now_idx = before_idx + 1;
        for (int i = now_idx; i < now_idx - 1 + n; i++) {
            if (arr[i] != 0)
                break;
            arr[i] = arr[i - 1] + 1;
            before_idx++;
        }
        //오른쪽 변
        int temp_n = n;
        for (int i = 1; i <= n - 2; i++) {
            if (arr[before_idx - temp_n] != 0) {
                break;
            }
            arr[before_idx - temp_n] = arr[before_idx] + 1;
            before_idx -= temp_n;
            temp_n--;
        }
        max_num = arr[before_idx];
        startIdx = before_idx;
        startIdx += 2;
        n -= 3;
        
    }
    


    return answer;
}
int main() {
    solution(6);
}
