//left가 아직 끝에 도달하지 않은 경우도 생각해 주어야 한다.(28번째 줄)
//signal이 없는 곳을 배열에 담는 코드.
#include <iostream>
#include <vector>
using namespace std;

int solution(int n, vector<int> stations, int w)
{
    int answer = 0;

    // [실행] 버튼을 누르면 출력 값을 볼 수 있습니다.
    cout << "Hello Cpp" << endl;

    vector<pair<int, int>> no_signal;

    int left = 1;
    for (int i = 0; i < stations.size(); i++) {
        pair<int, int> signal = { stations[i] - w, stations[i] + w };
        if (signal.first < 1) signal.first = 1;
        if (signal.second > n) signal.second = n;

        if (left >= signal.first) { // 기존에 신호가 안터지는 곳을 덮는 경우
            left = signal.second + 1;
            continue;
        }
        no_signal.push_back({ left, signal.first - 1 });
        left = signal.second + 1;
    }
    if (left <= n)
        no_signal.push_back({ left, n });
    for (int i = 0; i < no_signal.size(); i++) {
        int no_sig_range = no_signal[i].second - no_signal[i].first + 1;
        answer += no_sig_range / (2 * w + 1);
        if (no_sig_range % (2 * w + 1) != 0)
            answer += 1;
    }
    return answer;
}
int main() {
    solution(16, { 9 }, 2);
}
