#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>
using namespace std;
//N^2으로 풀지 말고, 다른 해시 아이디어를 잘 생각해보자..
bool solution(vector<string> phone_book) {
    bool answer = true;
    map<string, int> asd;
    sort(phone_book.begin(), phone_book.end(), [](const string & a, const string & b){ return a.size() < b.size(); });
    vector<int> num_size(21);
    for(int i=0; i<phone_book.size(); i++){
        num_size[phone_book[i].size()]++;
    }
    for(int i=0; i<num_size.size(); i++){
        cout << num_size[i] << ' ' ;
    }
    int count = 0;
    vector<string> temp;
    for(int i=0; i<num_size.size(); i++){
        if(num_size[i] != 0){ // 현재 i라는 사이즈를 갖는 phone_number가 있는 것임.
            for(int j=count; j<count+num_size[i]; j++)//현재 count 번째부터 count+num_size[i] - 1까지는 접두사 후보에 들어갈 애들이기 때문에 map에다가 넣어준다. 
                asd.insert(make_pair(phone_book[j], 1));
            for(int j = count + num_size[i]; j<phone_book.size(); j++){
              //그리고 count + num_size[i]부터 끝까지, 이 문자열들의 앞에서 count 개수만큼의 접두사가 현재 앞에서 있었는지 확인한다!
                if(asd.find(phone_book[j].substr(0, phone_book[count].size())) != asd.end()){
                    return !answer;
                }
            }
            count+=num_size[i];
            
        }
        asd.clear();
    }
    
    
       
    
    
    return answer;
}
