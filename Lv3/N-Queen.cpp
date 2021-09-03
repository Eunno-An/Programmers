#include <string>
#include <vector>
#include <iostream>
using namespace std;
bool ok(int n, int y, int x, vector<int> list) {
    if (list.size() == n)
        return true;
    else
        return false;
}
int solve(int n, int y, int x, vector<int> list) {
    if (x == n+1) 
        return ok(n, y, x, list);
    
    int ret = 0;
    for (int i = 1; i <= n; i++) {
        bool flag = true;
        //세로 x번에 있는 요소가 무엇이 되려는지 확인하기.
        //기존에 있는 y들과 같거나,
        //현재 y번 위치 - (x-j)가 i와 같거나, y + (x-j)가 i와 같으면?
        //대각선에 존재하는 것임.
        for (int j = 1; j <= list.size(); j++) { 
            if (i == list[j-1] || i == list[j-1] - (x - j) || i == list[j-1] + (x - j)) {
                flag = false;
                break;
            }
        }
        if (flag) {
            list.push_back(i);
            ret += solve(n, i, x + 1, list);
            list.pop_back();
        }
    }
    return ret;
}
int solution(int n) {
    int answer = 0;
    if (n == 1)
        return 1;
    vector<int> list;
    for (int i = 1; i <= n; i++) {
        list.push_back(i);
        answer += solve(n, i, 2, list);
        list.pop_back();
    }
    return answer;
}
int main() {
    solution(4);
}
