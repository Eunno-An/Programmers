//최대한 각 요소를, s/n에 맞춰야 하는 문제.
//시간복잡도가 답도 안나와서, 그리디하게 풀었고,
//마지막 요소들을 다시 평균치로 조절하는 과정만 진행 해주면 됨.

//1. avg를 floor((double)s/n + 0.5)로 정하면 안되는 이유
//n = 6, s = 21일 때 4 4 4 4 4 1 처럼 마지막 수가 확 떨어지는 수가 있음.

#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;
bool compare(int a, int b){
    return a < b;
}
vector<int> solution(int n, int s) {
    vector<int> answer;
    if(n > s){
        vector<int> error;
        error.push_back(-1);
        return error;
    }
    int avg = s/n;
    int sum = 0;
    
    //n = 6, s = 20
    //3 3 3 3 3 5 = 243 * 5 = 1215
    //3 3 3 3 4 4 = 81 * 4 * 4 = 324 * 4 = 1296
    
    //n = 6, s = 21
    //4 4 4 4 4 1 = 256 * 4 = 1024
    //3 3 3 3 3 6 = 243 * 6 = 1452
    //3 3 3 3 4 5 = 81 * 20 = 1620
    //3 3 3 4 4 4 = 27 * 64 = 1728
    
    for(int i=0; i<n-1; i++){
        answer.push_back(avg);
        sum += avg;
    }
    answer.push_back(s - sum);
    if(s-sum == avg) // 이미 모든게 평균일 경우.
        return answer;
    int idx = answer.size()-2;
    while(answer.back() != avg + 1 && idx > 0 ){
        answer[answer.size()-1]--;
        answer[idx--]++;
    }
    return answer;
}
