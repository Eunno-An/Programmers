#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

bool compare(pair<double, int> a, pair<double, int> b){
    if(a.first == b.first)
        return a.second < b.second;
    return a.first > b.first;
}
vector<int> solution(int N, vector<int> stages) {
    vector<int> answer;
    
    vector<pair<double, int>> result;
    for(int i=1; i<=N; i++){
        int pass_count = 0;
        int now_count = 0;
        int nopass_count = 0;
        for(int j=0; j< stages.size(); j++){
            if(stages[j] > i){
                pass_count++;
            }
            else if(stages[j] == i){
                now_count++;
            }
            else if(stages[j] < i){
                nopass_count++;
            }
        }
        int below = pass_count + now_count; //분모(통과한 사람 + 시도하는 중인 사람)
        int above = now_count; //분자(시도하는 중인 사람)
        cout << "above: " << above << "\nbelow: " << below << '\n';
        double fail_prob;
        if(below == 0)
            fail_prob = 0;
        else
            fail_prob = (double)above / below;
        
        result.push_back(make_pair(fail_prob, i));
    }
    sort(result.begin(), result.end(), compare);
    for(int i=0; i<result.size(); i++){
        answer.push_back(result[i].second);
    }
    return answer;
}
