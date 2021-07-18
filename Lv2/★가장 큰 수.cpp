//아이디어가 너무 좋은 문제.

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
char first;
bool compare(string a, string b){
    return (a+b > b+a);
}
string solution(vector<int> numbers) {
    string answer = "";
    vector<string> vec;
    
    for(int i=0; i<numbers.size(); i++)
        vec.push_back(to_string(numbers[i]));
    
    
    
    sort(vec.begin(), vec.end(), compare);
    
    for(int i=0; i<vec.size(); i++)
        answer += vec[i];
    
    int count = 0;
    
    if(answer[0] == '0'){
        while(count != answer.size()-1 && answer[count] == '0'){
            count++;
        }
    }
    
    answer = answer.substr(count, answer.size()-count);
    return answer;
}
