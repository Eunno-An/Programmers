#include <string>
#include <vector>

//문자열 덧셈 하는거 잘 봐..
using namespace std;

string solution(string s, int n) {
    string answer = "";
    for(int i=0; i<s.size(); i++){
        if(isupper(s[i])){//Large Case
            s[i] = char((int)s[i] + n);
            if(!isupper(s[i])){
                s[i] = char((int)s[i] - 26);
            }
        }
        else if(islower(s[i])){//Lower Case
            s[i] = char((int)s[i] + n);
            if(!islower(s[i])){
                s[i] = char((int)s[i] - 26 );
            }
        }
        answer += s[i];
    }
    return answer;
}
