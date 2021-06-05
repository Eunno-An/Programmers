#include <string>
#include <vector>
#include <queue>
#include <functional>
using namespace std;

//queue
int solution(vector<int> scoville, int K) {
    int answer = 0;
    priority_queue<int, vector<int>, greater<int>> pq;
    for(int i=0; i<scoville.size(); i++){//백만 * 로그 백만
        pq.push(scoville[i]);
    }
    while(pq.top() < K && !pq.empty() && pq.size() >= 2){//백만
        int scoville_val1 = pq.top();//로그 1
        pq.pop();//로그 백만
        int scoville_val2 = pq.top();
        pq.pop();
        pq.push(scoville_val1 + scoville_val2 * 2);
        answer++;
    }
    if(!pq.empty()){
        if(pq.top() < K){
            answer = -1;
        }
    }
    if(answer == 0)
        answer = -1;
    return answer;
}
