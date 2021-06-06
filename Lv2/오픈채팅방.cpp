#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <queue>
#include <iostream>
using namespace std;

vector<string> solution(vector<string> record) {
    //스트링 토크나이즈 하는 방법!
    //sstream 헤더파일 include 하고, getline을 이용하기.
    //1 <= record.size() <= 십만
    vector<string> answer;
    map<string, string> room;
    queue<pair<string, string>> queue_info; // pair first = uid, pair second = in or out
    for(int i=0; i<record.size(); i++){
      
        vector<string> result_tokenize;
        string token;
        stringstream ss(record[i]);
        while(getline(ss, token, ' ')){
            result_tokenize.push_back(token);
        }
        if(result_tokenize[0] == "Enter"){
            if(room.find(result_tokenize[1]) != room.end()){
                room[result_tokenize[1]] = result_tokenize[2];
            }else{
                room.insert(make_pair(result_tokenize[1], result_tokenize[2]));
            }
            queue_info.push(make_pair(result_tokenize[1], "in"));
        }else if(result_tokenize[0] == "Leave"){
            queue_info.push(make_pair(result_tokenize[1], "out"));
        }else {//"Change"
            room[result_tokenize[1]] = result_tokenize[2];
        }
    }
    while(!queue_info.empty()){
        string uid = queue_info.front().first;
        string in_or_out = queue_info.front().second;
        if(in_or_out == "in"){
            answer.push_back(room[uid] + "님이 들어왔습니다.");
        }else{
            answer.push_back(room[uid]+"님이 나갔습니다.");
        }
        queue_info.pop();
    }
    return answer;
}
