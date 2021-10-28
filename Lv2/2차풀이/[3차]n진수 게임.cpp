//time : 30분

//굉장히 나이브하게 구현한 방법. 
//최대 문자열의 개수는 m*t가 될 겻이라는 것이 중요. 
//Issue 1: string의 최대 길이
//Issue 2: 문자를 숫자로 바꿀 떄(int num = char -'0'), 숫자를 문자로 바꿀 떄(char c = num + '0')
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

const char over10[6] = {'A', 'B', 'C', 'D', 'E', 'F'};
//decimal을 n진법의 수로 변환
string decimal2N(int decimal, int n){
    string ret = "";
    
    while(decimal != 0){
        if(decimal % n >= 10)
            ret += string(1, over10[decimal%n - 10]);
        else
            ret += decimal % n + '0';
        decimal /= n;
    }
    reverse(ret.begin(), ret.end());
    return ret == "" ? "0" : ret;//decimal이 0일 경우 아무것도 반환하지 않기 때문에 반드시 0을 리턴해주어야 함.
}
string solution(int n, int t, int m, int p) {
    string answer = "";
    int maxStrLength = m * t;
    int strLength = 0;
    vector<string> numbers;
    string ret = "";
    for(int i=0; ; i++){
        string temp = decimal2N(i, n);
        numbers.push_back(temp);
        strLength+=temp.size();
        if(strLength >= m * t)
            break;
    }
    for(int i=0; i<numbers.size(); i++)
        ret += numbers[i];
    for(int i=0; i<t; i++)
        answer += string(1, ret[i*m+p-1]);
    return answer;
}
