#include <string>
#include <stack>
#include <vector>
#include <iostream>

#include <cmath>
using namespace std;

//최적화 문제의 방법을 묻는 문제. 따른 배열을 통해 기록하는 것이 베스트임.
//hanoi(int n, int start, int end) = n개의 원판 하노이 탑을 start탑에서 end탑으로 옮기는 최소 방법을 return 한다.
int count = 0;
vector<vector<int>> answer;
void move(int n, int start, int end){
    vector<int> ans;
    ans.push_back(start);
    ans.push_back(end);
    answer.push_back(ans);
}
void hanoi(int n, int start, int via, int end){
    if(n == 1){
        move(1, start, end);
        return;
    }
    hanoi(n-1, start, end, via);
    move(n, start, end);
    hanoi(n-1, via, start, end);
}
vector<vector<int>> solution(int n) {
    hanoi(n, 1, 2, 3);
    return answer;
}
