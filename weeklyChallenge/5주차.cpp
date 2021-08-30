#include <string>
#include <vector>

using namespace std;
//A, AA, AAA, AAAA, AAAAA, AAAAE, AAAAI, AAAAO, AAAAU
//AAAE, AAAEA, AAAEE, AAAEI, AAAEO, AAAEU
vector<string> words;
const char uppers[5] = { 'A', 'E', 'I', 'O', 'U' };
bool flag = false;
void makeWord(string word, string goal) { 
    words.push_back(word);
    if (word == goal) {
        flag = true;
        return;
    }
    if (word.size() == 5) 
        return;
    for (int i = 0; i < 5; i++) {
        makeWord(word + uppers[i], goal);
        if (flag)
            break;
    }
    return;
}
int solution(string word) {
    int answer = 0;
    string start = "A";
    for (int i = 0; i < 5; i++) {
        start = uppers[i];
        makeWord(start, word);
        if (flag)
            break;
    }
    
    answer = words.size();
    return answer;
}
int main() {
    solution("I");
}
