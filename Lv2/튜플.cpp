//너무 귀찮은 예외처리가 많은 문제
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

bool compare(const vector<int>& a, const vector<int>& b){
    return a.size() < b.size();
}
int arr[100001];
vector<int> solution(string s) {
    vector<int> answer;
    vector<int> temp;
    vector<vector<int>> res;
    int number = 0;
    int size_number = 1;
    for(int i=0; i<s.size(); i++){
        if(s[i] == '{'){
            if(!temp.empty()){
                temp.clear();    
            }
        }
        else if(s[i] == '}'){
            if(number != 0){
                temp.push_back(number);
            }
            if(temp.size() != 0){
                number = 0;
                res.push_back(temp);
                temp.clear();
            }
        }
        else if(isdigit(s[i])){
            number *= size_number;
            number += s[i]-'0';
            size_number = 10;
        }
        else if(s[i] == ','){
            if(number != 0){
                temp.push_back(number);    
            }
            number = 0;
            size_number = 1;
        }
    }
    
    sort(res.begin(), res.end(), [](const vector<int> & a, const vector<int> & b){ return a.size() < b.size(); });
    arr[res[0][0]] = 1;
    answer.push_back(res[0][0]);
    for(int i=1; i<res.size(); i++){
        for(int j=0; j<res[i].size(); j++){
            if(arr[res[i][j]] == 0){
                arr[res[i][j]] = 1;
                answer.push_back(res[i][j]);
                break;
            }
        }
    }
    return answer;
}
