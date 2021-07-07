#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
using namespace std;

string solution(string s) {
    string answer = "";
    vector<char> vec_upper;
    vector<char> vec_lower;
    for(int i=0; i<s.size(); i++){
        if(islower(s[i])){
            vec_lower.push_back(s[i]);
        }else{
            vec_upper.push_back(s[i]);
        }
    }
    sort(vec_upper.begin(), vec_upper.end(), greater<>());
    sort(vec_lower.begin(), vec_lower.end(), greater<>());
    
    for(int i=0;i<vec_lower.size(); i++){
        answer+=vec_lower[i];
    }
    for(int i=0;i<vec_upper.size(); i++){
        answer+=vec_upper[i];
    }
    return answer;
}
