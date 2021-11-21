//fail
//간단한데 풀지 못했다. 이 문제는 유형이 중요하다. 쉽지만 대표적인 DP 문제.
//BAD code에 추가 첨부하겠음.
#include <string>
#include <vector>
#include <cstring>
using namespace std;
const int MOD = 1000000007;
int cache[100001];
int solution(int n, vector<int> money) {
    memset(cache, 0, sizeof(cache));
    cache[0] = 1;
    for(int i=0; i<money.size(); i++){
        int m = money[i];
        for(int j=1; j<=n; j++){
            if(m > j) continue;
            cache[j] = (cache[j] % MOD + cache[j-m]%MOD)%MOD;
        }
    }
    return cache[n];
}
