#include <string>
#include <vector>
#include <map>
#include<iostream>
using namespace std;

string solution(vector<string> participant, vector<string> completion) {
    string answer = "";
    map<string, int> m;
    for(int i=0; i<participant.size(); i++){
        if(m.find(participant[i]) == m.end()){
            m.insert(make_pair(participant[i], 1));
        }
        else{
            m[participant[i]]++;
        }
    }
    for(int i=0; i<completion.size(); i++){
        m[completion[i]]--;
    }
    for(map<string, int>::iterator iter = m.begin(); iter != m.end(); iter++){
        if(iter->second == 1){
            answer = iter->first;
            break;
        }
    }
        
    
    return answer;
}
