#include <string>
#include <vector>
#include <queue>
using namespace std;

int solution(int n, int k, vector<int> enemy) {
    
    priority_queue<int, vector<int>, greater<int>> pq;
    int sum = 0;
    for(int i=0; i<enemy.size(); i++){
        if(pq.size() < k){
            pq.push(enemy[i]);
        }else{
            pq.push(enemy[i]);
            if(n - pq.top() >= 0){
                n -= pq.top();
                pq.pop();
            }else{
                return i;
            }
        }
    }
    return enemy.size();
}