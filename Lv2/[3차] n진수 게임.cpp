#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
char afterTen[6] = {'A','B','C','D','E','F'};
string solution(int n, int t, int m, int p) {
    string answer = "";
    //걱정했던것: 문자열의 길이 초과
    //16번째줄의 for문에서, 직접 어떤 수 i의 비트를 구하는 과정에서, i가 int의 범위를 초과하면 어쩌지 라는 생각.
    //근데 직접 계산기 두드려보면서 생각해보니까, 2진수가 문자열을 가장 많이 잡아먹을 거라고 생각함. 1000이라는 십진수를 표현하기 위해서는 10자리의 비트가 필요. 충분함.
    //그럼 16진수는?.. 1억이라는 수가7자리의 16진수 자릿수가 필요함. 5만이라는 십진수는 4자리 16진수. 5만 * 4를 해도 20만이 넘어감.
    //이말은 즉, int 형 시뮬레이션을 돌려도, 오버플로우는 신경 안써도 됨.
    //신경써야 할 것은, 시간인데, 시간 초과날 줄 알았는데 안나서 다행.
    
    int strLength = 0;
    string ret = "0";
    vector<string> temp_number;
    
    for(int i=0; ; i++){
        int temp = i;
        string temp_ret = "";
        while(temp!=0){
             
            int newInt = temp %n;
            char newChar;
            if(newInt < 10)
                newChar = newInt + '0';
            else
                newChar = afterTen[newInt-10];
            temp_ret += string(1, newChar);
            temp /= n;
            strLength++;
            if(strLength == m*t)
                break;
        }
        reverse(temp_ret.begin(), temp_ret.end());
        temp_number.push_back(temp_ret);
        if(strLength == m*t)
            break;
        
    }
    for(int i=0; i<temp_number.size(); i++){
        ret += temp_number[i];
    }
    cout << ret;
    for(int i=0; i<t; i++){
        answer += string(1, ret[i*m + p - 1]);
    }

    return answer;
}
