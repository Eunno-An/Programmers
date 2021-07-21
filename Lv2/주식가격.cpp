#include <string>
#include <vector>
#include <stack>
using namespace std;
int arr[100001];
vector<int> solution(vector<int> prices) {
    vector<int> answer;
    stack<pair<int, int>> info;//(인덱스, 가격)

    for (int i = 0; i < prices.size()-1; i++) {
        if (info.empty()) {
            info.push(make_pair(i, prices[i])); 
        }
        else {
            if (info.top().second > prices[i]) {
                while (!info.empty() && info.top().second > prices[i]) {
                    arr[info.top().first] = i - info.top().first;
                    info.pop();
                }
            }
            info.push(make_pair(i, prices[i]));
        }
    }
    //stack에 남아있는 것들을 비워준다.
    while (!info.empty()) {
        arr[info.top().first] = (prices.size() - 1 - info.top().first);
        info.pop();
    }
    for (int i = 0; i < prices.size()-1; i++) {
        answer.push_back(arr[i]);
    }
    answer.push_back(0);//마지막은 무조건 0
    return answer;
}
int main() {
    solution({ 1, 2, 3, 2, 3 });
}
