//끝에 공백이 포함되어있는 경우
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>
using namespace std;

string solution(string s) {
    string answer = "";
    
    stringstream ss(s);
    string t;
    vector<string> words;
    while(getline(ss, t, ' '))
        words.push_back(t);
    bool flag = true;
    if(s.back() == ' ')
        flag = false;
    for(int i=0; i<words.size(); i++){
        if(isalpha(words[i][0]) && islower(words[i][0]))
            words[i][0] = toupper(words[i][0]);
        
        
        for(int j=1; j<words[i].size(); j++){
            //cout << temp[j] << ' ';
            if(isalpha(words[i][j]) && isupper(words[i][j]))
                words[i][j] = tolower(words[i][j]);
        }
    }
    cout << words.size() << endl;
    for(int i=0; i<words.size(); i++){
        //cout << words[i] << endl;
        answer += words[i];
        answer += " ";
    }
   // cout << answer << endl;
    answer.pop_back();
    if(!flag)
        answer.push_back(' ');
    return answer;
}
