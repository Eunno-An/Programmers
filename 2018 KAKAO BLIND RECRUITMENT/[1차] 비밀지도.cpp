#include <string>
#include <vector>

using namespace std;

//문자열을 앞에다 더하는거니까, 단순히 result += temp, 또는 result.push_back(temp)로 하지 말기
string return_Row(int n, int x){
    string result = "";
    while(x != 0){
        string temp = "";
        if(x % 2 == 0){
            temp = "0";
            result = temp + result;
        }else{
            temp = "1";
            result = temp + result;
        }
        x /= 2;
    }
    if(result.size() != n){
        string temp = "";
        for(int i=0; i<n-result.size(); i++){
            temp += '0';
        }
        result = temp + result;
    }
    return result;
}
vector<string> solution(int n, vector<int> arr1, vector<int> arr2) {
    vector<string> answer;
    for(int i=0; i<n; i++){
        string row1 = return_Row(n, arr1[i]);
        string row2 = return_Row(n, arr2[i]);
        string row = "";
        for(int j=0; j<n; j++){
            if(row1[j] == '1' || row2[j] == '1'){
                row += "#";
            }
            else{
                row += " ";
            }
        }
        answer.push_back(row);
    }
    return answer;
}
