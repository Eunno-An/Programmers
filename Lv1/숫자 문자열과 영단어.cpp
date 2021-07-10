#include <string>
#include <vector>
#include <map>
#include <iostream>
using namespace std;

map<string, int> m;
int find(string s){
    return m[s];
}
int solution(string s) {
    m.insert(make_pair("zero", 10));
    m.insert(make_pair("one", 1));
    m.insert(make_pair("two", 2));
    m.insert(make_pair("three", 3));
    m.insert(make_pair("four", 4));
    m.insert(make_pair("five", 5));
    m.insert(make_pair("six", 6));
    m.insert(make_pair("seven", 7));
    m.insert(make_pair("eight", 8));
    m.insert(make_pair("nine", 9));
    int answer = 0;
    vector<int> temp_vec;
    for(int i=0; i<s.size(); i++){
        cout << s[i] << '\n';
        if(isdigit(s[i])){
            temp_vec.push_back(s[i]-'0');
            
        }else{
            string temp = "";
            while(i < s.size() && isalpha(s[i])){
                if(find(temp))
                    break;
                temp += s[i];
                i++;
            }
            if(temp == "zero")
                temp_vec.push_back(0);
            else
                temp_vec.push_back(find(temp));
            i--; // 이거 해줘야함.. 귀찮.
        }
    }
    for(int i=0; i<temp_vec.size(); i++){
        answer += temp_vec[i];
        answer *= 10;
    }
    answer /= 10;
    return answer;
}
