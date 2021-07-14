#include <string>
#include <vector>
#include <deque>
#include <stack>
using namespace std;
bool check_correct(deque<char> temp){
    stack<char> s;
    for(int i=0; i<temp.size(); i++){
        if(s.empty())
            s.push(temp[i]);
        else{
            if((s.top() == '(' && temp[i] == ')') ||  (s.top() == '{' && temp[i] == '}') ||  (s.top() == '[' && temp[i] == ']'))
                s.pop();
            else
                s.push(temp[i]);
        }
    }
    return (s.empty() ? true : false);
}
int solution(string s) {
    int answer = 0;
    deque<char> container;
    for(int i=0; i<s.size(); i++){
        container.push_back(s[i]);
    }
    deque<char> original = container;
    for(int i=0; i<s.size(); i++){
        if(check_correct(container)){
            answer++;
        }
        char c = container.front();
        container.pop_front();
        container.push_back(c);
    }
    return answer;
}
