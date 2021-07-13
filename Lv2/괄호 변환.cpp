#include <string>
#include <vector>
#include <stack>
using namespace std;
bool check_empty(string s) {
    return (s.size() == 0 ? true : false);
}

bool check_Balanced(string s) {
    int left_pal_count = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '(')
            left_pal_count++;
    }
    return (left_pal_count == s.size() / 2 ? true : false);
}
bool check_Correct(string s) {
    stack<char> c;
    for (int i = 0; i < s.size(); i++) {
        if (c.empty())
            c.push(s[i]);
        else {
            if (c.top() == '(' && s[i] == ')')
                c.pop();
            else {
                c.push(s[i]);
            }
        }
    }
    return (c.empty() ? true : false);
}
pair<string, string> parse(string v) {
    string u = "";
    int u_size = 0;
    for (int i = 2; i <= v.size(); i += 2) {
        if (check_Balanced(v.substr(0, i))) {
            u = v.substr(0, i);
            u_size = i;
            break;
        }
    }
    string _v = v.substr(u_size, v.size() - u_size);
    return make_pair(u, _v);
}
string solve(string w) {
    string answer = "";
    if (w.size() == 0) { // p == 입력
        return "";
    }
    pair<string, string> p_u_v = parse(w);
    string u = p_u_v.first;
    string v = p_u_v.second;
    if (check_Correct(u)) {
        return u += solve(v);
    }
    else {
        answer += '(';
        answer += solve(v);
        answer += ')';
        u = u.substr(1, u.size() - 2);
        for (int i = 0; i < u.size(); i++) {
            if (u[i] == '(')
                u[i] = ')';
            else
                u[i] = '(';
        }
        answer += u;
        return answer;
    }
}
string solution(string p) {
    string answer = "";
    answer = solve(p);
    return answer;
}
int main() {
    solution("(()())()");
    solution(")(");
    solution("()))((()");
}
