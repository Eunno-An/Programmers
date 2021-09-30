#include <string>
#include <vector>
#include <set>
using namespace std;
//자료형, 자리(범위)
vector<int> solution(vector<int> enter, vector<int> leave) {
    vector<int> answer(enter.size(), 0);
    set<int> room;
    int enterIdx = 0;
    for (int i = 0; i < leave.size(); i++) {
        int leaveNext = leave[i];
        if (room.find(leaveNext) != room.end()) { //퇴실해야 하는 사람이 room에 있는 경우
            set<int>::iterator it = room.find(leaveNext);
            room.erase(it); // room에서 그 사람을 지운다.
            for (it = room.begin(); it != room.end(); it++) {//leaveNext와 만난 사람들의 횟수를 늘린다.
                if (leaveNext != *it) {
                    answer[leaveNext - 1]++;
                    answer[(*it) - 1]++;
                }

            }
        }
        else {
            room.insert(enter[enterIdx]);
            i--;//leave 인덱스를 그대로 둔다.
            enterIdx++;//enter 인덱스를 늘려 다음것을 본다.
        }
    }
    return answer;
}
int main() {
    solution({ 1, 3, 2 }, { 1, 2, 3 });
}
