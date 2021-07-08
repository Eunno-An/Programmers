#include <string>
#include <vector>

using namespace std;

bool solution(string s) {
    bool answer = true;
    bool isAllDigit = true;
    for(int i=0; i<s.size(); i++){
        if(!isdigit(s[i])){
            isAllDigit = false;
            break;
        }
    }
    return ((s.size() == 4 || s.size() == 6)&& isAllDigit);
}
