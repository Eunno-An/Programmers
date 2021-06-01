#include <iostream>
#include<string>
#include<stack>
using namespace std;

int solution(string s)
{
    int answer = -1;

    // [실행] 버튼을 누르면 출력 값을 볼 수 있습니다.
    //cout << "Hello Cpp" << endl;
    stack<char> ss;
    for(int i=0;i <s.size(); i++){
        if(ss.empty()){
            ss.push(s[i]);
            continue;
        }
        if(ss.top() == s[i]){
            ss.pop();
        }else
            ss.push(s[i]);
    }
    if(ss.empty())
        answer = 1;
    else
        answer = 0;
    return answer;
}
