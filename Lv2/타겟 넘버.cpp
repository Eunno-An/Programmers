#include <string>
#include <vector>

using namespace std;
int total_sum(vector<int> numbers){
    int ret = 0;
    for(int i=0; i<numbers.size(); i++){
        ret += numbers[i];
    }
    return ret;
}
int solve(vector<int> numbers, vector<int> temp, int n, int target, int idx){
    if(temp.size() == n){
        int ret = 0;
        for(int i=0; i<temp.size(); i++){
            ret += temp[i];
        }
        return (ret == target ? 1 : 0);
    }
    int ret = 0;
    temp.push_back(numbers[idx]);
    ret += solve(numbers, temp, n, target, idx+1);
    temp.pop_back();
        
    temp.push_back(numbers[idx] * -1);
    ret += solve(numbers, temp, n, target, idx+1);
    return ret;    
    
}
int solution(vector<int> numbers, int target) {
    int answer = 0;
    vector<int> temp;
    answer = solve(numbers, temp, numbers.size(), target, 0);
    return answer;
}
