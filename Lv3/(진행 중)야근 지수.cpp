#include <string>
#include <vector>
#include <iostream>

using namespace std;
//야근 피로도 = 남은 일의 작업량을 제곱하여 더한 값
//N시간 동안 야근 피로도를 최소화 -> 최적화 문제
//Demi: 1시간 동안 작업량 1만큼을 처리할 수 있음.

long long solution(int n, vector<int> works) {
    long long answer = 0;
    //20000 * 50000 = 1000000000(십억)
    long long totalAmount_work = 0;
    long long avg_work = 0;
    for(int i=0; i<works.size(); i++)
        totalAmount_work += works[i];
    //남아있는 작업 양보다, 야근 시간이 더 긴 경우
    if(totalAmount_work <= n)
        return 0; 
    totalAmount_work -= n;
    avg_work = totalAmount_work / works.size();
    cout << totalAmount_work << '\n';
    cout << avg_work << '\n';
    int workAmount_avg = avg_work * works.size();
    for(int i=0; i<works.size(); i++)
        works[i] = avg_work;
    
    if(totalAmount_work > workAmount_avg){
        int remain = totalAmount_work - workAmount_avg;//더 해야하는 일의 양
        for(int i=0; i<remain; i++)
            works[i]++;
    }
    
    for(int i=0; i<works.size(); i++)
        answer += (long long)works[i] * works[i];
        
    
    
    
    return answer;
}
