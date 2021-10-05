//단순 구현
#include <string>
#include <vector>
#include <cstring>
#include <map>
#include <cmath>
using namespace std;
//enroll = 각 판매원의 이름을 담은 배열 . size <= 10000. enroll 에 등장하는 이름은 조직에 참여한 순서에 따릅니다.
//referral = 각 판매원을 다단계 조직에 참여시킨 다른 판매원의 이름을 담은 배열.. = enroll size
//parent[enroll[i]]=referral[i];

//seller = 판매 집계 데이터. size <= 100,000 . 이게 질의임.
//amount = 수량. 각 원소는 100 이하 자연수

vector<int> solution(vector<string> enroll, vector<string> referral, vector<string> seller, vector<int> amount) {
    vector<int> answer(enroll.size() + 1, 0);
    int parent[10001];//판매원의 부모를 가리키는 배열. 0번째 값은 맨 위 "-"임.
    map<string, int> int_seller;//판매원의 string을 int값으로 저장한 사전
    memset(parent, -1, sizeof(parent));
    //parent[i] = -1인 경우, 부모가 현재 없음을 나타냄

    int_seller.insert(make_pair("-", 0)); //맨 부모 노드인 "-"는 int 0번 값임.
    for (int i = 0; i < enroll.size(); i++)
        int_seller.insert(make_pair(enroll[i], i + 1));

    for (int i = 0; i < referral.size(); i++)
        parent[i + 1] = int_seller[referral[i]];

    for (int i = 0; i < seller.size(); i++) {

        string sellerName = seller[i];
        int sellerInt = int_seller[sellerName];
        int sell_amount = amount[i];
        int price_total = sell_amount * 100;
        int commission = floor((double)(price_total / 10) + 0.5);
        while (sellerInt != 0 && price_total > 0) {
            answer[sellerInt] += (price_total - commission);
            sellerInt = parent[sellerInt];
            price_total = commission;
            commission = floor((double)(price_total / 10) + 0.5);
        }
    }
    answer.erase(answer.begin());
    return answer;
}
int main() {
    solution({ "john", "mary", "edward", "sam", "emily", "jaimie", "tod", "young" }, { "-", "-", "mary", "edward", "mary", "mary", "jaimie", "edward" }, { "young", "john", "tod", "emily", "mary" }, { 12, 4, 2, 5, 10 });
}
