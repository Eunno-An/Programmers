#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>
using namespace std;

int solution(int k, vector<int> t) {
    int answer = 0;
    map<int, int> bucket;
    for(int i=0; i<t.size(); i++)
        bucket[t[i]]+=1;
    vector<pair<int, int>> temp;
    for(auto p : bucket){
        temp.push_back({p.second, p.first});
    }
    sort(temp.begin(), temp.end(), greater<>());
    for(int i=0; i<temp.size(); i++){
        if(k <= 0)
            break;
        k -= temp[i].first;
        answer++;
    }
    return answer == 0 ? 1 : answer;
}