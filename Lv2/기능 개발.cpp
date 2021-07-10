#include <string>
#include <vector>
#include <deque>

using namespace std;

vector<int> solution(vector<int> progresses, vector<int> speeds) {
    //progresses: 먼저 배포되어야 하는 순서대로 작업의 진도가 적힌 정수 배열
    //speeds: 각 작업의 개발 속도
    //뒤에 있는 작업은 앞에 있는 잡업이 배포될 때 함께 배포 된다.
    //각 배포마다 몇 개의 기능이 배포되는지를 return 하라.
    vector<int> answer;
    int count = progresses.size();
    deque<pair<int, int>> job;
    
    for(int i=0; i<progresses.size(); i++){
        job.push_back(make_pair(progresses[i], speeds[i]));
    }
    while(!job.empty()){
        for(int i=0; i<job.size(); i++){
            if(job[i].first < 100){
                job[i].first += job[i].second;
            }
        }
        int count = 0;
        while(job.front().first >= 100){
            count++;
            job.pop_front();
        }
        if(count != 0){
            answer.push_back(count);    
        }
        
    }
    
    return answer;
}
