#include <string>
#include <vector>
#include <algorithm>
using namespace std;
int count_removeZero;
void binaryChange(string& s) {
    int one_count = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '1')
            one_count++;
    }

    count_removeZero += (s.length() - one_count);
    string ret = "";
    while (one_count != 0) {
        if (one_count % 2 == 0)
            ret += '0';
        else ret += '1';
        one_count /= 2;
    }
    reverse(ret.begin(), ret.end());
    s = ret;
}
vector<int> solution(string s) {
    vector<int> answer;

    string temp = s;
    int count_Transform = 0;
    while (s != "1") {
        count_Transform++;
        binaryChange(s);
    }
    answer.push_back(count_Transform);
    answer.push_back(count_removeZero);
    return answer;
}
