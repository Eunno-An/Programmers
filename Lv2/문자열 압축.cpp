#include <string>
#include <vector>
#include <iostream>
using namespace std;

int solution(string s) {
    int answer = 1000000000;
    for(int i=1; i<=s.size(); i++){
        string res = "";
        string temp = s.substr(0, i);
        int count = 1;
        for(int j=i; j<s.size(); j+=i){
            if(temp != s.substr(j, i)){
                if(count != 1){
                    res += to_string(count);
                }
                res += temp;
                temp = s.substr(j, i);
                count = 1;
            }
            else{
                count++;
            }
        //cout << res << '\n';    
        }
        if(count != 1){//마지막에 남은 것들도 해줘야 함.
            res += to_string(count);
        }        
        res += temp;
        if(answer > res.size()){
            answer = res.size();
        }
    }
    return answer;
}
