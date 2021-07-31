#include <string>
#include <vector>
#include <map>
#include <iostream>
using namespace std;

vector<int> solution(string msg) {
    vector<int> answer;
    
    map<string, int> dictionary;
    for(int i=65; i<91; i++){
        string word = string(1, (char)i);
        dictionary.insert(make_pair(word, i-64));
    }
    
    int maxIdxCount = 26;
    for(int i=0; i<msg.size(); i++){
        string temp = string(1, msg[i]);
        while(dictionary.find(temp)!=dictionary.end()){
            if(i < msg.size())
                temp+=string(1, msg[++i]);
        }
        //w를 찾는다.
        string w = temp.substr(0, temp.size()-1);
        //w에 해당하는 사전의 색인 번호를 출력한다.
        answer.push_back(dictionary[w]);
        //입력에서 처리되지 않은 다음 글자가 남아있다면, w+c에 해당하는 단어 즉 temp를 사전에 등록한다.
        dictionary.insert(make_pair(temp, ++maxIdxCount));
        i--;
    }
    
    return answer;
}
