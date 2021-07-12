#include <string>
#include <vector>
#include <queue>
#include <iostream>
using namespace std;

int solution(vector<int> priorities, int location) {
    int answer = 0;
    priority_queue<pair<int, int>> pq;
    queue<pair<int ,int >> q;
    for(int i=0; i<priorities.size(); i++){
        pq.push(make_pair(priorities[i], i)); // 중요도, 인덱스
        q.push(make_pair(priorities[i], i));
    }
    //(2, 0), (1, 1), (3, 2), (2, 3)
    int count = 0;
    while(1){
        
        int prior = q.front().first;
        int idx = q.front().second;
        cout << prior << ' ' << idx << ' '<< count << '\n';
        if(prior == pq.top().first){
            count++;
            pq.pop();
            q.pop();
            if(location == idx){
                answer = count;
                break;
            }
        }else{
            q.pop();
            q.push(make_pair(prior,idx));
        }
        
    }
    return answer;
}
