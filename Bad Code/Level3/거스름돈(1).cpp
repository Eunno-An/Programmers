//내가 생각한 방식 DP(top-down). 시간초과. O(n^3)이 됨.
#include <string>
#include <vector>
#include <cstring>
using namespace std;
const int MOD = 1000000007;
//흔한 동전 거슬러주기 문제
//완전탐색: 거슬러 줘야 하는 금액 n과 Finn이 현재 보유하고 있는 돈의 종류가 주어질 때, Finn이 n원을 거슬러 줄 방법의 수를 return 하도록 하여라.

int cache[100001][101];
int bruteForce(int n, vector<int> money, int moneyIdx) {
    if (n == 0)
        return 1;
    int& ret = cache[n][moneyIdx];
    if (ret)
        return ret;
    for (int i = moneyIdx; i < money.size(); i++)
        if (n - money[i] >= 0)
            ret += bruteForce(n - money[i], money, i) % MOD;

    return ret;
}
int solution(int n, vector<int> money) {
    memset(cache, 0, sizeof(cache));
    int answer = bruteForce(n, money, 0);
    return answer;
}


int main() {
	solution(5, { 1, 2, 5 });
}
