#include <string>
#include <vector>
#include <string.h>
#include <iostream>
using namespace std;

// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
string solution(string sentence) {
    for (int i = 0; i < sentence.size(); i++) {
        if (sentence[i] == ' ')
            return "invalid";
    }
    string answer = "";
    //대문자 다음에 소문자 -> rule1
    //소문자 다음에 대문자 -> rule2
    //대문자 다음에 대문자 -> 이전 단어가 rule1, 그 다음 단어도 rule1
    //소문자 다음에 소문자 -> 이전 단어가 rule2, 그 다음 단어도 rule2
    vector<string> words;
    int rule = (islower(sentence[0]) ? 2 : 1); // 문자열 앞 글자가 대문자 : rule1, 소문자 : rule2 
    bool used[26];
    char nowUseLower = (rule == 1 ? '\0' : sentence[0]);
    memset(used, false, sizeof(used));

    while (!sentence.empty()) {
        if (rule == 1) {//문자열 앞 글자가 대문자로 시작
            //AA
            //AbA
            //Ab
            string word = string(1, sentence[0]);
            if (sentence.size() > 1)
                nowUseLower = sentence[1];
            else {//A하나만으로 이루어져 있는 경우
                words.push_back(word);
                sentence.erase(sentence.begin());
                continue;
            }

            if (isupper(nowUseLower)) {//aIa AM에서 AM같은 경우 A 와 M으로 볼 수 있음.
                words.push_back(string(1, sentence[0]));
                sentence.erase(sentence.begin());
                continue;
            }

            if (used[nowUseLower-97]) {//이미 사용한 단어이면 rule = 3;
                rule = 3;
                continue;
            }
            
            
            int end_idx = -1; // 단어의 끝 인덱스
            int upperCount = 1; // 연속된 대문자의 개수
            int lowerCount = 0;
            for (int i = 1; i < sentence.size(); i++) {
                if (islower(sentence[i]) && sentence[i] != nowUseLower) {
                    end_idx = i;
                    break;
                }
                else {
                    if (isupper(sentence[i])) {
                        if (upperCount == 1) {
                            end_idx = i;
                            break;
                        }
                        upperCount++;
                        lowerCount = 0;
                    }
                    else {
                        if (lowerCount == 1) {
                            return "invalid";
                        }
                        lowerCount++;
                        upperCount = 0;
                    }
                    word += sentence[i];
                }
            }
            words.push_back(word);
            if (end_idx == -1)//전 단어를 다 집어 넣은 경우
                break;
            sentence.erase(sentence.begin(), sentence.begin() + end_idx);

        }
        else if(rule == 2){//문자열 앞 글자가 소문자로 시작
            //aB
            //aBa
            //aBac
            //aBaC
            nowUseLower = sentence[0];
            
            if (sentence.size() == 1 || used[nowUseLower-97]) {//소문자 하나로만 이루어져 있는 경우, 또는 이미 사용한 소문자일 경우
                rule = 3;
                continue;
            }
            string word = string(1, nowUseLower);
            int end_idx = -1;
            for (int i = 1; i < sentence.size(); i++) {
                if (islower(sentence[i])) {
                    end_idx = i;
                    break;
                }
                else 
                    word += sentence[i];
            }
            
            if (end_idx == -1 || sentence[end_idx] != nowUseLower) {//aBBBBb 또는 aBBBBB
                rule = 3;
                continue;
            }
            
            word += nowUseLower;
            sentence.erase(sentence.begin(), sentence.begin() + end_idx + 1);
            words.push_back(word);
        }
        else //규칙에 맞지 않는 경우
            return "invalid";

        if (sentence.empty())
            break;
        
        rule = (islower(sentence[0]) ? 2 : 1);
        used[nowUseLower - 97] = 1;
    }
    for (int i = 0; i < words.size(); i++) {
        string temp = "";
        for (int j = 0; j < words[i].size(); j++) 
            if (isupper(words[i][j]))
                temp += words[i][j];
        answer += temp;
        answer += ' ';

    }
    answer.pop_back();
    return answer;
}
int main() {
    cout << solution("aIaAM") << endl;
}
