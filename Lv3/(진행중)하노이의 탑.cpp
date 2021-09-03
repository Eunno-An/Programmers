#include <string>
#include <stack>
#include <vector>
#include <iostream>
using namespace std;

//최적화 문제의 방법을 묻는 문제. 따른 배열을 통해 기록하는 것이 베스트임.
//hanoi(int n, int start, int end) = n개의 원판 하노이 탑을 start탑에서 end탑으로 옮기는 최소 방법을 return 한다.
int count = 0;
void hanoi(int n, int start, int end){
    if(n == 1){
        count++;
        return;
    }
        
    if(end == start+1){
        hanoi(n-1, start, start-1);
        hanoi(1, start, end);
        hanoi(n-1, start-1, end);
    }
    else{
        hanoi(n-1, start, start+1);//위의 n-1개를 오른쪽으로 옮긴다.
        hanoi(1, start, end);//아래층 한개를 end로 옮긴다.
        hanoi(n-1, start+1, end);//start+1에 있는 전부를 end로 옮긴다.
    }
}
vector<vector<int>> solution(int n) {
    vector<vector<int>> answer;
    hanoi(n, 1, 3);
    cout << count << endl;
    return answer;
}
