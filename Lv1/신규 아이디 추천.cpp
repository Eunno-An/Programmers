#include <string>
#include <vector>

#include<iostream>
using namespace std;

string solv1(string new_id){
    for(int i=0; i<new_id.size(); i++){
        if(isupper(new_id[i])){ 
            new_id[i] = tolower(new_id[i]);
        }
    }
    return new_id;
}
string solv2(string new_id){
    string result = "";
    for(int i=0; i<new_id.size(); i++){
        if((islower(new_id[i])) || isdigit(new_id[i]) || new_id[i] == '_' ||new_id[i] == '-'|| new_id[i] == '.'){
            result += new_id[i];
        }
    }
    return result;
}
string solv3(string new_id){
    string result = "";
    bool flag = false;
    for(int i=0; i<new_id.size()-1; i++){
        if(new_id[i] == '.' && new_id[i+1] == '.'){
            result += '.';
            new_id.erase(new_id.begin() + i);
            i--;
            if(i == new_id.size()-2){
                flag = true;
            }
            continue;
        }
        result += new_id[i];
    }
    if(!flag){
        result += new_id[new_id.size()-1];
    }
    return new_id;
}
string solv4(string new_id){
    if(new_id[0] == '.'){
        new_id.erase(new_id.begin());
    }
    if(new_id[new_id.size()-1] == '.'){
        new_id.erase(new_id.begin() + new_id.size()-1);
    }
    return new_id;
}
string solv5(string new_id){
    if(new_id == ""){
        new_id +="a";
    }
    return new_id;
}
string solv6(string new_id){//예외처리 주
    string result = "";
    bool flag = false;
    if(new_id.size() >= 16){
        flag = true;
        for(int i=0; i<15; i++){
            result += new_id[i];
        }
        if(result[result.size()-1] == '.'){
             result.erase(result.begin() + result.size()-1);
        }
    }
    
    return flag ? result : new_id;
}
string solv7(string new_id){
    if(new_id.size() <= 2){
        char a = new_id[new_id.size()-1];
        while(new_id.size() != 3){
            new_id += a;
        }
    }
    return new_id;
}
string solution(string new_id) {
    string answer = "";
    new_id = solv1(new_id);
    cout << new_id << '\n';
    new_id = solv2(new_id);
    cout << new_id << '\n';
    new_id = solv3(new_id);
    cout << new_id << '\n';
    new_id = solv4(new_id);
    cout << new_id << '\n';
    new_id = solv5(new_id);
    cout << new_id << '\n';
    new_id = solv6(new_id);
    cout << new_id << '\n';
    new_id = solv7(new_id);
    cout << new_id << '\n';
    answer = new_id;
    return answer;
}
