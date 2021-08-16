#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <queue>
using namespace std;

//종만북에서 나오는 greedy문제(전자렌지에 빵 데워 먹는 문제)와 다른 점:
//전자렌지 문제 또는 세탁기 문제는, 기계를 돌리고 난 직후에 바로 다음 작업물을 넣는다.
//이 문제는 기계를 돌린다고 해서 바로 다음 작업물을 넣는 것이 아니라
//넣는 시간 t1 이 정해져 있다.

//A수행 완료. 이때 A의 수행 시작 시간을 t0, 수행 끝 시간을 t1이라고 하자.
//그 다음 작업들은 무엇으로 선택해야 할까?
//1. 수행 시간이 작은 순? NO. 넣는 시간이 정해져 있어서 안됨.
//2. 요청부터 종료시간이 작은 순? 한번 해봄.
bool compare(pair<int, int> a, pair<int, int> b){
    return a.first < b.first;
}
bool compare2(pair<int ,int>a, pair<int, int> b){
    return a.second < b.second;
}
int solution(vector<vector<int>> jobs) {
    int answer = 0;
    
    int min_TurnaroundTime = 100000000;
    int firstJob = -1;
    vector<pair<int, int>> schedule;
    for(int jobNum = 0; jobNum < jobs.size(); jobNum++)
        schedule.push_back(make_pair(jobs[jobNum][1], jobNum));
    sort(schedule.begin(), schedule.end(), compare);
   
    
    //schedule에는 (작업이 요청으로 들어온 시간부터 작업을 다 수행하기까지 걸린 시간, 작업 번호)가 들어가 있다.
    //우린 첫 작업의 시작 지점과 끝 지점을 기억한다.
    while(!schedule.empty()){
        int jobEndTime = schedule[0].first;//작업이 요청으로 들어온 시간 부터 작업을 다 수행하기까지 걸린 시간
        answer += jobEndTime;
        schedule.erase(schedule.begin());
        int count = 0;
        for(int i=0; i<schedule.size(); i++){//밀려있는 작업들 순회
            int nextJobNum = schedule[i].second;//그 다음 작업의 번호
            int nextJob_StartTime = jobs[nextJobNum][0];//다음 작업이 원래 스케쥴에서 들어온 시간
            if(nextJob_StartTime < jobEndTime){//대기시간이 있을 경우, (jobEndTime - nextJob_StartTime) 만큼 더해준다.
                schedule[i].first += (jobEndTime - nextJob_StartTime);
                count++;
            }
        }    
        if(count == 0) // 현재 하드디스크가 일을 안하는 경우
            sort(schedule.begin(), schedule.end(), compare2);
        else
            sort(schedule.begin(), schedule.end(), compare);
        
        
    }
    answer /= jobs.size();
    return answer;
}
