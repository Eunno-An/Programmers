//그리디 문제.
//못풀어서 베낌.
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
vector<int> temp;
int solution(vector<int> people, int limit) {
    int answer = 0;
    sort(people.begin(), people.end());
    
    int idx = 0;
    while (people.size() > idx) {
        int back = people.back(); people.pop_back();
        if (people[idx] + back <= limit) {
            answer++;
            idx++;
        }
        else answer++;
    }
    return answer;
}

int main() {
    solution({40, 50, 50, 50, 50, 60}, 100);
}

//
//#include <string>
//#include <vector>
//#include <algorithm>
//using namespace std;
//vector<int> temp;
//int solution(vector<int> people, int limit) {
//    int answer = 0;
//    sort(people.begin(), people.end());
//    temp.push_back(people[0]);
//    for (int i = 1; i < people.size(); i++) {
//        if (people[i] + people[0] > limit) {
//            answer++;
//        }
//        else {
//            temp.push_back(people[i]);
//        }
//    }
//    //temp에 있는 것들끼리 구명보트를 최대한 적게 사용하여 모든 사람을 구출하면 됨.
//    //적절한 방법으로, 두명씩 짝지었을 때, 짝의 개수를 줄이면 됨.
//    //temp의 길이가 홀수라면, 한명은 반드시 혼자 타야함.
//    //temp의 길이가 짝수라면, ? 이건 또 모름.
//
//    //최적화 문제를 푸는 방법
//    //모든 경우에 대해 생각해야 한다.
//    //그럼 N^2이 걸리는데, 그럼 안되고, 어떤 무게 W를 골랐을 때, limit >= W + Choice
//    //즉, limit-W와 가장 가까운 같거나 작은 값을 이분탐색으로 골라야 한다.
//    //만약 해당 식을 만족하는 Choice가 있으면 W와 Choice는 선택에서 제외되고, 구명보트 개수는 ++.
//    //그렇지 않다면 +=2
//
//
//
//    while (!temp.empty()) {
//        if (temp.size() == 1) {
//            answer++;
//            break;
//        }
//        int W = temp[0];
//        int idx = lower_bound(temp.begin() + 1, temp.end(), limit - W) - temp.begin();
//        if (idx == temp.size()) {//limit-W 이상인게 없을 때
//            temp.pop_back();
//            temp.erase(temp.begin());
//            answer++;
//        }
//        else {
//            if (temp[idx] + W <= limit) {
//                answer++;
//            }
//            else {
//                answer += 2;
//            }
//            temp.erase(temp.begin() + idx);
//            temp.erase(temp.begin());
//        }
//    }
//    return answer;
//}
//
//int main() {
//    solution({ 10, 20, 30, 30, 40, 60, 20 }, 60);
//}
