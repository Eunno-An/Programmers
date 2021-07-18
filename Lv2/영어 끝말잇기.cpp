#include <string>
#include <vector>
#include <iostream>
#include <map>
using namespace std;

vector<int> solution(int n, vector<string> words) {
    vector<int> answer;
    
    // [실행] 버튼을 누르면 출력 값을 볼 수 있습니다. 
    cout << "Hello Cpp" << endl;
    map<string, bool> already_use;
    char end_char_before_word = words[0].front();
    for(int i=0; i<words.size(); i++){
        if(already_use.find(words[i]) == already_use.end()){
            if(end_char_before_word == words[i][0]){
                already_use.insert(make_pair(words[i], 1));
                end_char_before_word = words[i].back();
            }
                
            else{
                answer.push_back(i % n + 1);//번호
                answer.push_back(i / n + 1);//차례
                break;
            }
        }
            
        else{
            answer.push_back(i % n + 1);//번호
            answer.push_back(i / n + 1);//차례
            break;
        }
            
    }
    if(answer.empty()){
        answer.push_back(0);
        answer.push_back(0);
    }
    return answer;
}
