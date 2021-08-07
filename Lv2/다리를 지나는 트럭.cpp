#include <string>
#include <vector>
#include <deque>
using namespace std;
//bridge_length = 다리에 올라갈 수 있는 트럭 수
//weight = 다리가 견딜 수 있는 무게
//truck_weights = 트럭 별 무게
int solution(int bridge_length, int weight, vector<int> truck_weights) {
    int answer = 1;
    deque<pair<int, int>> wait, bridge, already;
    for (int i = 0; i < truck_weights.size(); i++)
        wait.push_back(make_pair(truck_weights[i], 0));

    int now_weight = 0;
    for (; already.size() != truck_weights.size(); answer++) {
        for (int i = 0; i < bridge.size(); i++)
            bridge[i].second++;
        if (!bridge.empty()) {
            if (bridge.front().second == bridge_length) {
                already.push_back(make_pair(bridge.front().first, 1));
                now_weight -= bridge.front().first;
                bridge.pop_front();
            }

        }
        if (!wait.empty() && bridge_length > bridge.size() && now_weight + wait.front().first <= weight) {
            now_weight += wait.front().first;
            bridge.push_back(make_pair(wait.front().first, 0));
            wait.pop_front();
        }

    }
    return answer-1;


}
int main() {
    solution(2, 10, { 7, 4, 5, 6 });
}
