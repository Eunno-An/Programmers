//흠.... 이게 진짜 말도 안되.......!
#include <string>
#include <vector>
#include <stack>
#include <deque>
using namespace std;

int arr[1000001];
string solution(int n, int k, vector<string> cmd) {
    string answer = "";
    stack<int> stack_erase;
    deque<int> chart;
    int now_idx = k;

    for (int i = 0; i < n; i++)
        chart.push_back(i);

    for (int i = 0; i < cmd.size(); i++) {
        if (cmd[i][0] == 'U') {
            int X = stoi(cmd[i].substr(2, cmd[i].size() - 2));
            k -= X;
            if (k < 0)
                k = 0;
        }
        else if (cmd[i][0] == 'D') {
            int X = stoi(cmd[i].substr(2, cmd[i].size() - 2));
            k += X;
            if (k > chart.size() - 1)
                k = chart.size() - 1;
        }
        else if (cmd[i] == "C") {
            if (chart.empty())
                continue;
            int temp_k = k;
            if (k == chart.size() - 1)//삭제된 행이 가장 마지막 행인 경우
                k--;
            stack_erase.push(chart[temp_k]);
            chart.erase(chart.begin() + temp_k);
            
        }
        else {
            int redo = stack_erase.top();
            stack_erase.pop();
            auto idx = lower_bound(chart.begin(), chart.end(), redo);
            deque<int>::iterator it = chart.begin() + k;
            if (idx <= it)
                k++;
            chart.insert(idx, redo);
        }
    }

    while (!stack_erase.empty()) {
        arr[stack_erase.top()] = 1;
        stack_erase.pop();
    }
    for (int i = 0; i < n; i++)
        if (arr[i] == 1)
            answer.push_back('X');
        else
            answer.push_back('O');


    return answer;
}
int main() {
    solution(8, 2, { "D 2", "C", "U 3", "C", "D 4", "C", "U 2", "Z", "Z" });
}
