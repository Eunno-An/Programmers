#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int solution(vector<int> d, int budget) {
    //d: 신청한 금액 부서별로
    //budget: 예산
    //answer: 최대 몇 개의 부서에 물품을 지원할 수 있을까?
    int answer = 0;
    sort(d.begin(), d.end());
    for(int i=0; i<d.size(); i++){
        budget -= d[i];
        answer++;
        if(budget < 0){
            answer--;
            break;
        }
        
    }
    return answer;
}
