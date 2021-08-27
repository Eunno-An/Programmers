//queueSize==0일 때, queue들을 다 비워주기.
#include <string>
#include <vector>
#include <queue>
using namespace std;

vector<int> solution(vector<string> operations) {
    vector<int> answer;
    priority_queue<int, vector<int>, greater<int>> pq_min;//minHeap
    priority_queue<int, vector<int>, less<int>> pq_max;

    int queueSize = 0;
    for (int i = 0; i < operations.size(); i++) {
        if (operations[i] == "D 1") {//queue에서 최댓값 삭제
            if (queueSize != 0 && !pq_max.empty()) {
                pq_max.pop();
                if (!pq_min.empty() && pq_min.size() == 1)
                    pq_min.pop();
                queueSize--;
            }
        }
        else if (operations[i] == "D -1") {//queue에서 최솟값 삭세
            if (queueSize != 0 && !pq_min.empty()) {
                pq_min.pop();
                if (!pq_max.empty() && pq_max.size() == 1)
                    pq_max.pop();
                queueSize--;
            }
        }
        else {
            queueSize++;
            int number = stoi(operations[i].substr(2, operations[i].size() - 2));
            pq_max.push(number);
            pq_min.push(number);
        }

        if (queueSize == 0) {
            while (!pq_min.empty()) 
                pq_min.pop();
            
            while (!pq_max.empty()) 
                pq_max.pop();
            
        }
    }

    if (queueSize == 0) {
        answer.push_back(0);
        answer.push_back(0);
    }
    else {
        answer.push_back(pq_max.top());
        answer.push_back(pq_min.top());
    }


    return answer;
}
int main() {
    solution({ "I 4", "I 3", "I 2", "I 1", "D 1", "D 1", "D -1", "D -1", "I 5", "I 6" });
}
