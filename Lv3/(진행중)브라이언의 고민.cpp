#include <string>
#include <iostream>
#include <stack>

using namespace std;

// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
// abba

// BaKDcDcBcA
// aBa
// aBBa
// 
string solution(string sentence) {
    string answer = "";
    //규칙 1: 대문자 사이 사이에 소문자
    //규칙 2: 소문자가 글자 앞 뒤에 존재함.
    int rule = (islower(sentence[0]) ? 2 : 1); // 문자열 앞 글자가 소문자 일 경우, 규칙 2일 가능성이 있고, 대문자면 규칙 1일 가능성이 있음. 
    bool used[26];
    char nowUseLower = '\0';
    
    memset(used, false, sizeof(used));
    while (!sentence.empty()) {
        rule = (islower(sentence[0]) ? 2 : 1);
        if (rule == 1) {
            
            string pair = "";
            if (sentence.size() >= 2) {//AxBxC에서 Ax
                pair = sentence.substr(0, 2);
                if (islower(pair[1])) {
                    
                    
                    if (nowUseLower == '\0') {
                        nowUseLower = pair[1];
                        while (sentence.size() >= 2 && isupper(sentence[0]) && islower(sentence[1])) {
                            if (nowUseLower != sentence[1])
                                break;
                            answer += sentence[0];
                            sentence.erase(sentence.begin(), sentence.begin() + 2);

                        }
                        if (sentence.size() >= 2 && nowUseLower != sentence[1]) {
                            answer += sentence[0];
                            sentence.erase(sentence.begin());
                        }
                    }
                    else {
                        if (used[nowUseLower - 97])
                            return answer = "invalid";
                        answer += pair[0];
                        if (nowUseLower == pair[1]) {
                            sentence.erase(sentence.begin(), sentence.begin() + 2);
                        }
                        else {//AxBxCoDFFDo 같은 경우
                            sentence.erase(sentence.begin());
                        }

                    }
                    used[nowUseLower - 97] = 1;
                }
                else {//AA같은 경우
                    
                }
            }
            else {//A혼자 남았을 때
                answer += to_string(pair[0]);
            }
        }
        else if (rule == 2) {
            nowUseLower = sentence[0];
            if (used[nowUseLower - 97]) // 이미 사용한 문자일 경우
                return answer = "invalid";
            int idxLower = -1;
            for (int i = 1; i < sentence.size(); i++) {
                if (sentence[i] == nowUseLower) {
                    idxLower = i;
                    break;
                }
            }
            if (idxLower == -1)//aBBBBBB로 끝날 경우
                return answer = "invalid";
            sentence.erase(sentence.begin());
            sentence.erase(sentence.begin() + idxLower-1);
            used[nowUseLower - 97] = 1;

            string temp = "";
            for (int i = 0; i < sentence.size(); i++) {
                if (isupper(sentence[i]))
                    temp += sentence[i];
            }
            if (temp.size() == sentence.size()) {
                answer += temp;
                sentence.clear();
            }
        }
    }


    return answer;
}
int main() {
    
    cout << solution("HaEaLaLaObWORLDb") << '\n';
    cout << solution("SpIpGpOpNpGJqOqA") << '\n';
    cout << solution("AxAxAxAoBoBoB") << '\n';
}
