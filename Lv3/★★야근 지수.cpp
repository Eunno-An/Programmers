//fail
//원인? 문제를 잘 읽지 않음.
//각 인덱스 마다 최대 일의 시간이 정해져 있음.
//예를 들어, 100, 2, 51 이라는 works가 있을 때, n은 2라고 가정하자.
//내가 기존에 했던 방식은 100 + 2 + 51 - n = 151
//151이 총 일해야 하는 양이였고, 이를 works.size()로 나누었다.
//이렇게 되면 문제점이, 151/3 = 50, 즉 두번째 일은 두시간 밖에 안걸리는데, 50시간을 투자해야하는 상황
//뭔가 문제에서 바라는 점이랑 맞지 않다.
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
    
    int workAmount_avg = avg_work * works.size();
    vector<int> workDB;
    for(int i=0; i<works.size(); i++){
        if(works[i] < avg_work){
            workDB.push_back(works[i]);
            totalAmount_work -= works[i];
        }
        else{
            workDB.push_back(avg_work);
            totalAmount_work -= avg_work;
        }
    }
    
    
    while(totalAmount_work > 0){
        for(int i=0; i<workDB.size(); i++){
            if(totalAmount_work == 0)break;
            if(workDB[i] + 1 > works[i]) continue; // 1씩 더한다 이소리같음.
            workDB[i]++;
            totalAmount_work--;
        }
    }
    //9 13 7, 3
    //totalAmount_work = 26
    //workAmount_avg = 24
    //remain = 2
    //works = 8 8 8
    //works = 9 9 8
    //works의 제곱의 합은 81 81 64 = 226.
    //10 8 8 = 100 64 64 = 228
    //avg = 41
    
    //total = 214
    //total - n = 209
    //41 41 41 41 41 = 205
    //remain = 4
    //42 42 42 42 41
    for(int i=0; i<works.size(); i++)
        answer += (long long)workDB[i] * workDB[i];
        
    
    
    
    return answer;
}


//#include <string>
//#include <vector>
//#include <iostream>

//using namespace std;
//야근 피로도 = 남은 일의 작업량을 제곱하여 더한 값
//N시간 동안 야근 피로도를 최소화 -> 최적화 문제
//Demi: 1시간 동안 작업량 1만큼을 처리할 수 있음.

//long long solution(int n, vector<int> works) {
//    long long answer = 0;
    //20000 * 50000 = 1000000000(십억)
//    long long totalAmount_work = 0;
//    long long avg_work = 0;
//    for(int i=0; i<works.size(); i++)
//        totalAmount_work += works[i];
    //남아있는 작업 양보다, 야근 시간이 더 긴 경우
//    if(totalAmount_work <= n)
//        return 0; 
//    totalAmount_work -= n;
//    avg_work = totalAmount_work / works.size();
//    cout << totalAmount_work << '\n';
//    cout << avg_work << '\n';
//    int workAmount_avg = avg_work * works.size();
//    for(int i=0; i<works.size(); i++)
//        works[i] = avg_work;
    
//    if(totalAmount_work > workAmount_avg){
//        int remain = totalAmount_work - workAmount_avg;//더 해야하는 일의 양
//        for(int i=0; i<remain; i++)
//            works[i]++;
//    }
    
//    for(int i=0; i<works.size(); i++)
//        answer += (long long)works[i] * works[i];
        
    
    
    
//    return answer;
//}
