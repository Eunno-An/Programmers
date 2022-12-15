#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
using namespace std;

int solution(vector<string> want, vector<int> number, vector<string> discount) {
    int answer = 0;
    unordered_map<string, int> bucket;
    unordered_map<string, int> target;
    for(int i=0; i<number.size(); i++)
        target[want[i]] = number[i];
    
    for(int i=0; i<discount.size(); i++){
        bucket[discount[i]]++;
        if(i < 9)
            continue;
        if(i == 9){
            if(bucket == target)
                answer++;
            continue;
        }
        if(bucket.count(discount[i-10]) > 0){
            bucket[discount[i-10]]--;
            if(bucket[discount[i-10]] == 0)
                bucket.erase(discount[i-10]);
        }
        
        
        if(bucket == target)
            answer++;
    }
    return answer;
}