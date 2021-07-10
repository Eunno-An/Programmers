#include <iostream>
#include <string>

/*
 * [40] 프로그래머스 이상한 문자 만들기
 */

using namespace std;

string solution(string s) {
    int temp = 0;

    for(int i = 0; i < s.size(); i++){
        if(s[i] == ' ') {
            temp = 0;
            continue;
        }

        if(temp % 2 == 0) s[i] = toupper(s[i]);
        else s[i] = tolower(s[i]);
        temp++;
    }

    return s;
}

int main() {
    std::cout << solution("try hello world") << std::endl;
    return 0;
}
